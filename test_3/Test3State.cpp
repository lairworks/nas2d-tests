#include "Test3State.h"

#include <GL/glew.h>

const int	CAUSTICS_SPEED		= 55;
const int	TILE_SIZE			= 256;


#include <sstream>

using namespace std;

Test3State::Test3State() :
	mFont("fonts/opensans-bold.ttf", 25),
	mSmallFont("fonts/opensans.ttf", 14),
	mMud("mud.png"),
	mCaustics("caustics_atlas.png"),
	mCaustics2("caustics_atlas_noalpha.png"),
	mCaustics3("caustics_atlas_2.png"),
	mCaustics4("caustics_atlas_2_noalpha.png"),
	mAlpha(true),
	mMultiply(false),
	mCausticsOnly(false),
	mAlpha2(false),
	mMultiply2(false),
	mCausticsOnly2(false)
{
}


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

	for(size_t col = 0; col < divideUp(r.height(), TILE_SIZE); col++)
	{
		for(size_t row = 0; row < divideUp(r.width(), TILE_SIZE); row++)
		{
			r.drawImage(mMud, row * 256, col * 256);
		}
	}

	if(mMultiply || mMultiply2)
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	for(size_t col = 0; col < divideUp(r.height(), TILE_SIZE); col++)
	{
		for(size_t row = 0; row < divideUp(r.width(), TILE_SIZE); row++)
		{
			if(mAlpha)
				r.drawSubImage(mCaustics, row * TILE_SIZE, col * TILE_SIZE, (counter % 4) * TILE_SIZE, ((counter % 16) / 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			else if(mMultiply || mCausticsOnly)
				r.drawSubImage(mCaustics2, row * TILE_SIZE, col * TILE_SIZE, (counter % 4) * TILE_SIZE, ((counter % 16) / 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			else if(mAlpha2)
				r.drawSubImage(mCaustics3, row * TILE_SIZE, col * TILE_SIZE, (counter % 4) * TILE_SIZE, ((counter % 16) / 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			else if(mMultiply2 || mCausticsOnly2)
				r.drawSubImage(mCaustics4, row * TILE_SIZE, col * TILE_SIZE, (counter % 4) * TILE_SIZE, ((counter % 16) / 4) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
	}
	if(mMultiply || mMultiply2)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	r.drawText(mFont, "Blending Demo", 5, 5, 255, 255, 255);
	r.drawText(mSmallFont, "Press keys 1 - 6 to change blend modes.", 5, 5 + mFont.height(), 255, 255, 255);

	if(mMultiply || mMultiply2)
		r.drawText(mSmallFont, "Multiply", r.width() - mSmallFont.width("Multiply") - 5, 5, 255, 255, 255);
	else if(mCausticsOnly || mCausticsOnly2)
		r.drawText(mSmallFont, "Caustics Only", r.width() - mSmallFont.width("Caustics Only") - 5, 5, 255, 255, 255);
	else
		r.drawText(mSmallFont, "Alpha", r.width() - mSmallFont.width("Alpha") - 5, 5, 255, 255, 255);

	r.drawText(mSmallFont, string_format("FPS: %i", mFps.fps()), r.width() - 65, r.height() - mSmallFont.height() - 5, 255, 255, 255);

	return this;
}



void Test3State::onKeyDown(EventHandler::KeyCode key, EventHandler::KeyModifier mod, bool repeat)
{
	if(repeat)
		return;

	if(key == EventHandler::KeyCode::KEY_ESCAPE)
		postQuitEvent();

	if(key == EventHandler::KeyCode::KEY_1)
	{
		mAlpha = true;
		mMultiply = false;
		mCausticsOnly = false;
		mAlpha2 = false;
		mMultiply2 = false;
		mCausticsOnly2 = false;
	}
	if(key == EventHandler::KeyCode::KEY_2)
	{
		mAlpha = false;
		mMultiply = true;
		mCausticsOnly = false;
		mAlpha2 = false;
		mMultiply2 = false;
		mCausticsOnly2 = false;

	}
	if(key == EventHandler::KeyCode::KEY_3)
	{
		mAlpha = false;
		mMultiply = false;
		mCausticsOnly = true;
		mAlpha2 = false;
		mMultiply2 = false;
		mCausticsOnly2 = false;

	}
	if(key == EventHandler::KeyCode::KEY_4)
	{
		mAlpha = false;
		mMultiply = false;
		mCausticsOnly = false;
		mAlpha2 = true;
		mMultiply2 = false;
		mCausticsOnly2 = false;
	}
	if(key == EventHandler::KeyCode::KEY_5)
	{
		mAlpha = false;
		mMultiply = false;
		mCausticsOnly = false;
		mAlpha2 = false;
		mMultiply2 = true;
		mCausticsOnly2 = false;
	}
	if(key == EventHandler::KeyCode::KEY_6)
	{
		mAlpha = false;
		mMultiply = false;
		mCausticsOnly = false;
		mAlpha2 = false;
		mMultiply2 = false;
		mCausticsOnly2 = true;
	}
}
