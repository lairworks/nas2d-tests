#include "GameState.h"

#include <functional>
#include <iostream>
#include <random>
#include <string>

using namespace NAS2D;


const int GUN_DELAY_TIME = 210;
const int GUN_JITTER = 6;

const unsigned int ZOMBIE_DEAD_TIMEOUT = 8000; // Time, in miliseconds, a dead zombie should continue to exist


std::mt19937 generator;
std::uniform_int_distribution<int> jitter_distribution(-GUN_JITTER, GUN_JITTER);

auto jitter = std::bind(jitter_distribution, generator);


GameState::GameState() :
	mZombieSpawnCount(5),
	mFont("fonts/opensans.ttf", 15),
	mAnnounceFont("fonts/opensans-bold.ttf", 50),
	mPlayerPosition(Utility<Renderer>::get().center_x(), Utility<Renderer>::get().center_y()),
	mPointer("pointer.png"),
	mBackground("grass_bg.png"),
	mBulletHole("bullet_hole.png"),
	mTent("tent.png"),
	mTentShadow("tent_shadow.png"),
	mBgMusic("music/clearside-shapeshifter.ogg"),
	mGunFire("sfx/machine_gun.wav"),
	mTimeDelta(0),
	mLeftButtonDown(false)
{
}


void GameState::initialize()
{
	spawnSwarm();

	auto& e = Utility<EventHandler>::get();
	e.keyUp().connect(this, &GameState::onKeyUp);
	e.keyDown().connect(this, &GameState::onKeyDown);
	e.mouseMotion().connect(this, &GameState::onMouseMove);
	e.mouseButtonUp().connect(this, &GameState::onMouseUp);
	e.mouseButtonDown().connect(this, &GameState::onMouseDown);
	e.quit().connect(this, &GameState::onQuit);

	Utility<Mixer>::get().playMusic(mBgMusic);
}


State* GameState::update()
{
	auto& r = Utility<Renderer>::get();
	r.clearScreen(50, 150, 200);
	r.drawImage(mBackground, 0, 0);

	updateTimer();
	updatePlayer();
	updateZombies();

	// Tent shadow and base
	r.drawImage(mTentShadow, mPlayerPosition.x() - 256, mPlayerPosition.y() - 100);
	r.drawSubImage(mTent, mPlayerPosition.x() - 128, mPlayerPosition.y() + 0, 0, 162, 256, 94);

	if (mLeftButtonDown)
		r.drawLine(mPlayerPosition.x(), mPlayerPosition.y(), mBulletPoint.x(), mBulletPoint.y(), Color::White, 1);

	// Tent top
	r.drawSubImage(mTent, mPlayerPosition.x() - 128, mPlayerPosition.y() - 70, 0, 0, 256, 139);

	r.drawImage(mPointer, mMouseCoords.x() - 7, mMouseCoords.y() - 7);

	r.drawText(mAnnounceFont, "Zombies are Coming!", r.center_x() - mAnnounceFont.width("Zombies are Coming!") / 2, 10, 255, 255, 255);
	r.drawText(mFont, "Defend Yourself!", r.center_x() - mFont.width("Defend Yourself!") / 2, 75, 255, 255, 255);
	r.drawText(mFont, "FPS: " + std::to_string(mFps.fps()), 10, 100, 255, 255, 255);
	r.drawText(mFont, "Zombies: " + std::to_string(mZombies.size()), 10, 120, 255, 255, 255);

	return this;
}


void GameState::doShoot()
{
	auto& r = Utility<Renderer>::get();

	mBulletPoint = {(mMouseCoords.x() - mBulletHole.width() / 2) + jitter(), (mMouseCoords.y() -  mBulletHole.height() / 2) + jitter()};

	Utility<Mixer>::get().playSound(mGunFire);

	for(size_t i = 0; i < mZombies.size(); i++)
	{
		if(mZombies[i].hit(mBulletPoint))
		{
			mZombies[i].damage(10, mBulletPoint);
			if(mZombies[i].dead())
			{
				mDeadZombies.push_back(mZombies[i]);
				mZombies.erase(mZombies.begin() + i);
			}
			return;
		}
	}

	r.drawImageToImage(mBulletHole, mBackground, mBulletPoint);
}


void GameState::updatePlayer()
{
	handlePlayerAction();
}


void GameState::handlePlayerAction()
{
	if(mLeftButtonDown)
	{
		while(mGunTimer.accumulator() >= GUN_DELAY_TIME)
		{
			mGunTimer.adjust_accumulator(GUN_DELAY_TIME);
			doShoot();
		}
	}
}


/**
 * Spawns a group of zombies around the player.
 */
void GameState::spawnSwarm()
{
	for(size_t i = 0; i < mZombieSpawnCount; i++)
		mZombies.push_back(Zombie{static_cast<float>(i) * 200, -20, 15});

	mZombieSpawnCount += 2;
}


void GameState::updateZombies()
{
	for(size_t i = 0; i < mDeadZombies.size(); i++)
	{
		mDeadZombies[i].update(0, mPlayerPosition);

		if(mDeadZombies[i].deadTime() >= ZOMBIE_DEAD_TIMEOUT)
			mDeadZombies.erase(mDeadZombies.begin() + i);
	}

	for(size_t i = 0; i < mZombies.size(); i++)
	{
		mZombies[i].update(mTimeDelta, mPlayerPosition);
	}
}


void GameState::onKeyDown(EventHandler::KeyCode /*key*/, EventHandler::KeyModifier /*mod*/, bool repeat)
{
	if(repeat)
		return;
}


void GameState::onKeyUp(EventHandler::KeyCode key, EventHandler::KeyModifier /*mod*/)
{
	if(key == EventHandler::KeyCode::KEY_ESCAPE)
		postQuitEvent();
}


void GameState::onMouseDown(EventHandler::MouseButton button, int /*x*/, int /*y*/)
{
	if(button == EventHandler::MouseButton::BUTTON_LEFT)
	{
		mGunTimer.reset();
		mLeftButtonDown = true;
		doShoot();
	}
}


void GameState::onMouseUp(EventHandler::MouseButton button, int /*x*/, int /*y*/)
{
	if(button == EventHandler::MouseButton::BUTTON_LEFT)
	{
		mLeftButtonDown = false;
	}
}


void GameState::onMouseMove(int x, int y, int /*relX*/, int /*relY*/)
{
	mMouseCoords = {x, y};
}


void GameState::updateTimer()
{
	mTimeDelta = mTimer.delta();
}


void GameState::onQuit()
{
	std::cout << "Toodles!" << std::endl;
}
