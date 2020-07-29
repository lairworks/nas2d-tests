#include "Zombie.h"


constexpr auto BodySize = NAS2D::Vector<int>{20, 26};
constexpr auto BodyOffset = NAS2D::Vector<int>{-10, -10};
constexpr auto HeadSize = NAS2D::Vector<int>{6, 6};
constexpr auto HeadOffset = NAS2D::Vector<int>{-3, -7};
constexpr auto HealthMeterSize = NAS2D::Vector<int>{24, 2};
constexpr auto HealthMeterOffset = NAS2D::Vector<int>{-HealthMeterSize.x / 2, -25};


Zombie::Zombie(NAS2D::Point<float> position, float speed) :
	mSprite("zombie.xml", "Walk"),
	mPosition(position),
	mHealth(100),
	mMaxHealth(mHealth),
	mSpeed(speed),
	mBodyRect(NAS2D::Rectangle<int>::Create(mPosition.to<int>() + BodyOffset, BodySize)),
	mHeadRect(NAS2D::Rectangle<int>::Create(mPosition.to<int>() + HeadOffset, HeadSize))
{
}


void Zombie::update(int timeDelta, NAS2D::Point<float> playerPosition)
{
	mSprite.update(mPosition);

	if (dead())
		return;

	// Ultra basic bee-line AI
	const auto direction = NAS2D::getAngle(playerPosition - mPosition);
	mPosition += NAS2D::getDirectionVector(direction) * (timeDelta * mSpeed);

	// Update bounding boxes.
	mBodyRect = NAS2D::Rectangle<int>::Create(mPosition.to<int>() + BodyOffset, BodySize);
	mHeadRect = NAS2D::Rectangle<int>::Create(mPosition.to<int>() + HeadOffset, HeadSize);

	auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();

	renderer.drawBoxFilled(NAS2D::Rectangle<float>::Create(mPosition + HealthMeterOffset, HealthMeterSize), NAS2D::Color::Black);
	renderer.drawBoxFilled(NAS2D::Rectangle<float>::Create(mPosition + HealthMeterOffset, NAS2D::Vector<int>{HealthMeterSize.x * mHealth / mMaxHealth, HealthMeterSize.y}), NAS2D::Color::Yellow);

	renderer.drawBox(mHeadRect, NAS2D::Color::White);
	renderer.drawBox(mBodyRect, NAS2D::Color::White);
}


bool Zombie::hit(NAS2D::Point<int> pt)
{
	return mBodyRect.contains(pt) || mHeadRect.contains(pt);
}


void Zombie::damage(int d, NAS2D::Point<int> pt)
{
	if (dead())
		return;

	if (mHeadRect.contains(pt))
	{
		mHealth = 0;
		mSprite.play("Dead");
		mDeadTimer.reset();
		return;
	}

	mHealth -= d;
	if (mHealth <= 0)
	{
		mHealth = 0;
		mSprite.play("Dead");
		mDeadTimer.reset();
	}
}


unsigned int Zombie::deadTime()
{
	if (!dead())
		return 0;

	return mDeadTimer.accumulator();
}
