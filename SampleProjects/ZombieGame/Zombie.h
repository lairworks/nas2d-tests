#pragma once

#include "NAS2D/NAS2D.h"


class Zombie
{
public:
	Zombie(NAS2D::Point<float> position, float speed);

	void update(NAS2D::Duration timeDelta, NAS2D::Point<float> playerPosition);

	NAS2D::Point<float> position() const { return mPosition; }
	bool hit(NAS2D::Point<int> pt);

	void damage(int d, NAS2D::Point<int> pt);
	int health() const { return mHealth; }
	bool dead() const { return mHealth <= 0; }
	NAS2D::Duration deadTime();

private:
	NAS2D::Timer mDeadTimer; /**< Timer */
	NAS2D::Sprite mSprite; /**< Zombie Sprite. */
	NAS2D::Point<float> mPosition; /**< Zombie's position. */

	int mHealth; /**< Zombie's health. */
	int mMaxHealth; /**< Zombie's max health. */

	float mSpeed; /**< Zombie's speed in pixels per update. */

	NAS2D::Rectangle<int> mBodyRect; /**< Area of the Zombie. */
	NAS2D::Rectangle<int> mHeadRect; /**< Area of the Zombie. */
};
