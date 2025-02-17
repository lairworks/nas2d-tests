#pragma once

#include "NAS2D/NAS2D.h"

#include "Zombie.h"

#include <bitset>
#include <list>

class GameState: public NAS2D::State
{
public:
	GameState();

protected:
	void initialize() override;
	State* update() override;

	void onKeyUp(NAS2D::KeyCode key, NAS2D::KeyModifier mod);
	void onKeyDown(NAS2D::KeyCode key, NAS2D::KeyModifier mod, bool repeat);
	void onMouseMove(NAS2D::Point<int> position, NAS2D::Vector<int> change);
	void onMouseUp(NAS2D::MouseButton button, NAS2D::Point<int> position);
	void onMouseDown(NAS2D::MouseButton button, NAS2D::Point<int> position);

	void onQuit();

private:
	using ZombieList = std::list<Zombie>;

	void doShoot();

	void updateTimer();

	void updatePlayer();
	void handlePlayerAction();

	void spawnSwarm();
	void updateZombies();

	NAS2D::Timer mTimer; /**< */
	NAS2D::Timer mGunTimer; /**< */

	NAS2D::FpsCounter	mFps; /**< FPS Counter */

	ZombieList mZombies; /**< */
	ZombieList mDeadZombies; /**< */
	size_t mZombieSpawnCount;	/**< Number of zombies to spawn. */

	const NAS2D::Font mFont; /**< Font used for interface and information text. */
	const NAS2D::Font mAnnounceFont; /**< Font used for displaying the announcement. */

	NAS2D::Point<int> mPlayerPosition;	/**< Position of the 'player'. */

	NAS2D::Point<int> mMouseCoords; /**< Mouse coordinates. */
	NAS2D::Point<int> mBulletPoint; /**< */

	const NAS2D::Image mPointer; /**< Pointer image. */
	const NAS2D::Image mBackground; /**< Background buffer. */
	const NAS2D::Image mBulletHole; /**< Bullet hole. */
	const NAS2D::Image mTent; /**< Tent graphic. */
	const NAS2D::Image mTentShadow; /**< Tent shadow graphic. */

	const NAS2D::Music mBgMusic; /**< Background music track. */

	const NAS2D::Sound mGunFire; /**< Gun fire sound. */

	int mTimeDelta; /**< Delta time between the previous cycle and the current cycle. */

	bool mLeftButtonDown;	/**< Flag indicating that the left mouse button is down. */
};
