#pragma once

#ifndef __ZOMBIE__
#define __ZOMBIE__

#include "NAS2D/NAS2D.h"


class Zombie
{
public:
	Zombie(NAS2D::Point_2df position, float speed);

	void update(int timeDelta, NAS2D::Point_2df playerPosition);

	float rotation() const { return mSprite.rotation(); }
	NAS2D::Point_2df position() const { return mPosition; }
	bool hit(NAS2D::Point_2d pt);

	void damage(int d, NAS2D::Point_2d pt);
	int health() const { return mHealth; }
	bool dead() const { return mHealth <= 0; }
	unsigned int deadTime();

private:
	NAS2D::Timer mDeadTimer; /**< Timer */
	NAS2D::Sprite mSprite; /**< Zombie Sprite. */
	NAS2D::Point_2df mPosition; /**< Zombie's position. */

	int mHealth; /**< Zombie's health. */
	int mMaxHealth; /**< Zombie's max health. */

	float mDirection; /**< Zombie's facing direction. */
	float mSpeed; /**< Zombie's speed in pixels per update. */

	NAS2D::Rectangle_2d mBodyRect; /**< Area of the Zombie. */
	NAS2D::Rectangle_2d mHeadRect; /**< Area of the Zombie. */
};


#endif
