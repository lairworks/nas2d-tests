#include "Test3State.h"

#include <GL/glew.h>

#include <sstream>
#include <string>


const int CAUSTICS_SPEED = 55;
const int TILE_SIZE = 256;


Test3State::Test3State() :
	mFont("fonts/opensans-bold.ttf", 25),
	mSmallFont("fonts/opensans.ttf", 14),
	mMud("mud.png"),
	mCaustics1("caustics_atlas.png"),
	mCaustics2("caustics_atlas_noalpha.png"),
	mCaustics3("caustics_atlas_2.png"),
	mCaustics4("caustics_atlas_2_noalpha.png"),
	mCurrentCaustics(&mCaustics1),
	mMultiply(false),
	mCausticsOnly(false)
{}


void Test3State::initialize()
{
	Utility<Renderer>::get().showSystemPointer(true);
	Utility<EventHandler>::get().keyDown().connect(this, &Test3State::onKeyDown);
}


State* Test3State::update()
{
	Renderer& r = Utility<Renderer>::get();

	static int counter = 0;

	if(mCausticsTimer.accumulator() > CAUSTICS_SPEED)
	{
		mCausticsTimer.reset();
		counter++;
		if(counter >= 16)
			counter = 0;
	}

	for(int col = 0; col < divideUp(r.height(), TILE_SIZE); col++)
	{
		for(int row = 0; row < divideUp(r.width(), TILE_SIZE); row++)
		{
			r.drawImage(mMud, row * 256, col * 256);
		}
	}

	if(mMultiply)
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	for(int col = 0; col < divideUp(r.height(), TILE_SIZE); col++)
	{
		for(int row = 0; row < divideUp(r.width(), TILE_SIZE); row++)
		{
			r.drawSubImage(*mCurrentCaustics, row * TILE_SIZE, col * TILE_SIZE, (counter % 4) * TILE_SIZE, ((counter % 16) / 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
	}
	if(mMultiply)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	r.drawText(mFont, "Blending Demo", 5, 5, 255, 255, 255);
	r.drawText(mSmallFont, "Press keys 1 - 6 to change blend modes.", 5, 5 + mFont.height(), 255, 255, 255);

	if(mMultiply)
		r.drawText(mSmallFont, "Multiply", r.width() - mSmallFont.width("Multiply") - 5, 5, 255, 255, 255);
	else if(mCausticsOnly)
		r.drawText(mSmallFont, "Caustics Only", r.width() - mSmallFont.width("Caustics Only") - 5, 5, 255, 255, 255);
	else
		r.drawText(mSmallFont, "Alpha", r.width() - mSmallFont.width("Alpha") - 5, 5, 255, 255, 255);

	r.drawText(mSmallFont, "FPS: " + std::to_string(mFps.fps()), r.width() - 65, r.height() - mSmallFont.height() - 5, 255, 255, 255);

	return this;
}


void Test3State::onKeyDown(EventHandler::KeyCode key, EventHandler::KeyModifier /*mod*/, bool repeat)
{
	if(repeat)
		return;

	if(key == EventHandler::KeyCode::KEY_ESCAPE)
		postQuitEvent();

	if(key == EventHandler::KeyCode::KEY_1)
	{
		mCurrentCaustics = &mCaustics1;
		mMultiply = false;
		mCausticsOnly = false;
	}
	if(key == EventHandler::KeyCode::KEY_2)
	{
		mCurrentCaustics = &mCaustics2;
		mMultiply = true;
		mCausticsOnly = false;
	}
	if(key == EventHandler::KeyCode::KEY_3)
	{
		mCurrentCaustics = &mCaustics2;
		mMultiply = false;
		mCausticsOnly = true;
	}
	if(key == EventHandler::KeyCode::KEY_4)
	{
		mCurrentCaustics = &mCaustics3;
		mMultiply = false;
		mCausticsOnly = false;
	}
	if(key == EventHandler::KeyCode::KEY_5)
	{
		mCurrentCaustics = &mCaustics4;
		mMultiply = true;
		mCausticsOnly = false;
	}
	if(key == EventHandler::KeyCode::KEY_6)
	{
		mCurrentCaustics = &mCaustics4;
		mMultiply = false;
		mCausticsOnly = true;
	}
}
