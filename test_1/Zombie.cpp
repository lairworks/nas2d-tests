#include "Zombie.h"


const auto BoundingBoxBody = NAS2D::Rectangle_2d(-10, -40, 14, 46);
const auto BoundingBoxHead = NAS2D::Rectangle_2d(-7, -50, 8, 8);
const auto BoundingBoxHealthMeter = NAS2D::Rectangle_2d(0, 0, 24, 4);
const std::string SPRITE_PATH = "zombie_0.xml";
const std::string IDLE_WEST = "WalkWest";


Zombie::Zombie(float x, float y, float speed) :
	mSprite(SPRITE_PATH),
	mPosition(x, y),
	mHealth(100),
	mMaxHealth(mHealth),
	mDirection(0.0f),
	mSpeed(speed),
	mBodyRect(BoundingBoxBody),
	mHeadRect(BoundingBoxHead)
{
	mSprite.play(IDLE_WEST);
}


bool Zombie::hit(const NAS2D::Point_2d& pt)
{
	return mBodyRect.contains(pt) || mHeadRect.contains(pt);
}


unsigned int Zombie::deadTime()
{
	if(!dead())
		return 0;

	return mTimer.accumulator();
}

void Zombie::update(int timeDelta, const NAS2D::Point_2df& playerPosition)
{
	mSprite.update(mPosition.x(), mPosition.y());

	if(dead())
		return;

	// Ultra basic bee-line AI
	mDirection = NAS2D::angleFromPoints(mPosition.x(), mPosition.y(), playerPosition.x(), playerPosition.y());
	doMove(timeDelta);

	// Update bounding boxes.
	mBodyRect.x() = mPosition.x() + BoundingBoxBody.x();
	mBodyRect.y() = mPosition.y() + BoundingBoxBody.y();
	mHeadRect.x() = mPosition.x() + BoundingBoxHead.x();
	mHeadRect.y() = mPosition.y() + BoundingBoxHead.y();

	// Health bar
	auto& r = NAS2D::Utility<NAS2D::Renderer>::get();

	int startX = mPosition.x() - BoundingBoxHealthMeter.width() / 2;
	int healthWidth = BoundingBoxHealthMeter.width() * (static_cast<float>(mHealth) / static_cast<float>(mMaxHealth));

	r.drawBoxFilled(startX, mHeadRect.y() - 5, BoundingBoxHealthMeter.width(), 2, 0, 0, 0);
	r.drawBoxFilled(startX, mHeadRect.y() - 5, healthWidth, 2, 255, 255, 0);

	r.drawBox(mHeadRect, 255, 255, 255);
	r.drawBox(mBodyRect, 255, 255, 255);
}


void Zombie::doMove(int timeDelta)
{
	auto dir = NAS2D::getDirectionVector(mDirection);

	mPosition.x() += (dir.x() * (timeDelta / 1000.0f)) * mSpeed;
	mPosition.y() += (dir.y() * (timeDelta / 1000.0f)) * mSpeed;
}


void Zombie::setAnimationState()
{}


void Zombie::damage(int d, const NAS2D::Point_2d& pt)
{
	if(dead())
		return;

	if(!dead())
	{
		if(mHeadRect.contains(pt))
		{
			mHealth = 0;
			mSprite.play("Dead2West");
			mTimer.reset();
			return;
		}
		else
		{
			mHealth -= d;
		}
	}

	if(mHealth <= 0)
	{
		mHealth = 0;
		mSprite.play("Dead1West");
		mTimer.reset(); // reset timer so we know how long it's been since the zombie died.
	}
}
