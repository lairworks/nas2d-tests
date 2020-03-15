#include "NAS2D/NAS2D.h"

#include "Zombie.h"

#include <bitset>
#include <vector>

class GameState: public NAS2D::State
{
public:
	GameState();

protected:
	void initialize() override;
	State* update() override;

	void onKeyUp(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier mod);
	void onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier mod, bool repeat);
	void onMouseMove(int x, int y, int relX, int relY);
	void onMouseUp(NAS2D::EventHandler::MouseButton button, int x, int y);
	void onMouseDown(NAS2D::EventHandler::MouseButton button, int x, int y);

	void onQuit();

private:
	using ZombieList = std::vector<Zombie>;

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

	NAS2D::Font mFont; /**< Font used for interface and information text. */
	NAS2D::Font mAnnounceFont; /**< Font used for displaying the announcement. */

	NAS2D::Point_2d mPlayerPosition;	/**< Position of the 'player'. */

	NAS2D::Point_2d mMouseCoords; /**< Mouse coordinates. */
	NAS2D::Point_2d mBulletPoint; /**< */

	NAS2D::Image mPointer; /**< Pointer image. */
	NAS2D::Image mBackground; /**< Background buffer. */
	NAS2D::Image mBulletHole; /**< Bullet hole. */
	NAS2D::Image mTent; /**< Tent graphic. */
	NAS2D::Image mTentShadow; /**< Tent shadow graphic. */

	NAS2D::Music mBgMusic; /**< Background music track. */

	NAS2D::Sound mGunFire; /**< Gun fire sound. */

	int mTimeDelta; /**< Delta time between the previous cycle and the current cycle. */

	bool mLeftButtonDown;	/**< Flag indicating that the left mouse button is down. */
};
