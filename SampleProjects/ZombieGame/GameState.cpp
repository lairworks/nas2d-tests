#include "GameState.h"

#include <functional>
#include <iostream>
#include <random>
#include <string>


const int GunDelayTime = 210;
const int GunJitter = 6;
const unsigned int ZombieDeadTimeout = 8000; // Time, in miliseconds, a dead zombie should continue to exist

std::mt19937 generator;
std::uniform_int_distribution<int> jitter_distribution(-GunJitter, GunJitter);
auto jitter = std::bind(jitter_distribution, generator);


GameState::GameState() :
	mZombieSpawnCount(5),
	mFont("fonts/opensans.ttf", 15),
	mAnnounceFont("fonts/opensans-bold.ttf", 50),
	mPlayerPosition(NAS2D::Utility<NAS2D::Renderer>::get().center()),
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

	auto& e = NAS2D::Utility<NAS2D::EventHandler>::get();
	e.keyUp().connect(this, &GameState::onKeyUp);
	e.keyDown().connect(this, &GameState::onKeyDown);
	e.mouseMotion().connect(this, &GameState::onMouseMove);
	e.mouseButtonUp().connect(this, &GameState::onMouseUp);
	e.mouseButtonDown().connect(this, &GameState::onMouseDown);
	e.quit().connect(this, &GameState::onQuit);

	NAS2D::Utility<NAS2D::Mixer>::get().playMusic(mBgMusic);
}


NAS2D::State* GameState::update()
{
	auto& r = NAS2D::Utility<NAS2D::Renderer>::get();
	r.clearScreen(NAS2D::Color{50, 150, 200});
	r.drawImage(mBackground, NAS2D::Point<float>{0, 0});

	updateTimer();
	updatePlayer();
	updateZombies();

	// Tent shadow and base
	r.drawImage(mTentShadow, (mPlayerPosition - NAS2D::Vector<int>{256, 100}).to<float>());
	r.drawSubImage(mTent, (mPlayerPosition - NAS2D::Vector<int>{128, 0}).to<float>(), NAS2D::Rectangle{0, 162, 256, 94});

	if (mLeftButtonDown)
		r.drawLine(mPlayerPosition, mBulletPoint, NAS2D::Color::White, 1);

	// Tent top
	r.drawSubImage(mTent, (mPlayerPosition - NAS2D::Vector<int>{128, 70}).to<float>(), NAS2D::Rectangle{0, 0, 256, 139});

	r.drawImage(mPointer, (mMouseCoords - NAS2D::Vector<int>{7, 7}).to<float>());

	r.drawText(mAnnounceFont, "Zombies are Coming!", NAS2D::Point{r.center_x() - mAnnounceFont.width("Zombies are Coming!") / 2, 10}, NAS2D::Color::White);
	r.drawText(mFont, "Defend Yourself!", NAS2D::Point{r.center_x() - mFont.width("Defend Yourself!") / 2, 75}, NAS2D::Color::White);
	r.drawText(mFont, "FPS: " + std::to_string(mFps.fps()), NAS2D::Point<float>{10, 100}, NAS2D::Color::White);
	r.drawText(mFont, "Zombies: " + std::to_string(mZombies.size()), NAS2D::Point<float>{10, 120}, NAS2D::Color::White);

	return this;
}


void GameState::doShoot()
{
	mBulletPoint = mMouseCoords - mBulletHole.size() / 2 + NAS2D::Vector{jitter(), jitter()};

	NAS2D::Utility<NAS2D::Mixer>::get().playSound(mGunFire);

	for(size_t i = 0; i < mZombies.size(); i++)
	{
		if (mZombies[i].hit(mBulletPoint))
		{
			mZombies[i].damage(10, mBulletPoint);
			if (mZombies[i].dead())
			{
				mDeadZombies.push_back(mZombies[i]);
				mZombies.erase(mZombies.begin() + i);
			}
			return;
		}
	}

	auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();
	renderer.drawImageToImage(mBulletHole, mBackground, mBulletPoint);
}


void GameState::updatePlayer()
{
	handlePlayerAction();
}


void GameState::handlePlayerAction()
{
	if (mLeftButtonDown)
	{
		while(mGunTimer.accumulator() >= GunDelayTime)
		{
			mGunTimer.adjust_accumulator(GunDelayTime);
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
		mZombies.push_back(Zombie{NAS2D::Point<float>{static_cast<float>(i) * 200, 620}, 0.015f});

	mZombieSpawnCount += 2;
}


void GameState::updateZombies()
{
	for(size_t i = 0; i < mDeadZombies.size(); i++)
	{
		mDeadZombies[i].update(0, mPlayerPosition);

		if (mDeadZombies[i].deadTime() >= ZombieDeadTimeout)
			mDeadZombies.erase(mDeadZombies.begin() + i);
	}

	for(size_t i = 0; i < mZombies.size(); i++)
	{
		mZombies[i].update(mTimeDelta, mPlayerPosition);
	}
}


void GameState::onKeyDown(NAS2D::EventHandler::KeyCode /*key*/, NAS2D::EventHandler::KeyModifier /*mod*/, bool repeat)
{
	if (repeat)
		return;
}


void GameState::onKeyUp(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier /*mod*/)
{
	if (key == NAS2D::EventHandler::KeyCode::KEY_ESCAPE)
		NAS2D::postQuitEvent();
}


void GameState::onMouseDown(NAS2D::EventHandler::MouseButton button, int /*x*/, int /*y*/)
{
	if (button == NAS2D::EventHandler::MouseButton::BUTTON_LEFT)
	{
		mGunTimer.reset();
		mLeftButtonDown = true;
		doShoot();
	}
}


void GameState::onMouseUp(NAS2D::EventHandler::MouseButton button, int /*x*/, int /*y*/)
{
	if (button == NAS2D::EventHandler::MouseButton::BUTTON_LEFT)
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
