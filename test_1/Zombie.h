#ifndef __ZOMBIE__
#define __ZOMBIE__

#include "NAS2D/NAS2D.h"


class Zombie
{
public:
	Zombie(float x, float y, float speed);

	void update(int timeDelta, const NAS2D::Point_2df& playerPosition);

	int health() const { return mHealth; }
	void damage(int d, const NAS2D::Point_2d& pt);
	float rotation() const { return mSprite.rotation(); }

	const NAS2D::Point_2df& position() const { return mPosition; }

	bool dead() const { return mHealth <= 0; }

	bool hit(const NAS2D::Point_2d& pt);

	unsigned int deadTime();

private:

	void doMove(int timeDelta);

	void setAnimationState();

	NAS2D::Timer mTimer; /**< Timer */

	NAS2D::Sprite mSprite; /**< Zombie Sprite. */

	NAS2D::Point_2df mPosition; /**< Zombie's position. */

	int mHealth; /**< Zombie's health. */
	int mMaxHealth; /**< Zombie's max health. */

	float mDirection; /**< Zombie's facing direction. */

	float mSpeed; /**< Zombie's speed. */

	NAS2D::Rectangle_2d mBodyRect; /**< Area of the Zombie. */
	NAS2D::Rectangle_2d mHeadRect; /**< Area of the Zombie. */
};


#endif
