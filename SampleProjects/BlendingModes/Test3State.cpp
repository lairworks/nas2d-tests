#include "Test3State.h"

#include <GL/glew.h>

#include <sstream>
#include <string>


const int CausticsSpeed = 55;
const int TileSize = 256;


Test3State::Test3State() :
	mFont("fonts/opensans-bold.ttf", 25),
	mSmallFont("fonts/opensans.ttf", 14),
	mMud("mud.png"),
	mCaustics1("caustics_atlas.png"),
	mCaustics2("caustics_atlas_noalpha.png"),
	mCaustics3("caustics_atlas_2.png"),
	mCaustics4("caustics_atlas_2_noalpha.png"),
	mCurrentCaustics(&mCaustics1),
	mBlendingModeText("Alpha"),
	mMultiply(false)
{}


void Test3State::initialize()
{
	NAS2D::Utility<NAS2D::Renderer>::get().showSystemPointer(true);
	NAS2D::Utility<NAS2D::EventHandler>::get().keyDown().connect({this, &Test3State::onKeyDown});
}


NAS2D::State* Test3State::update()
{
	auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();

	static int counter = 0;

	if (mCausticsTimer.accumulator() > CausticsSpeed)
	{
		mCausticsTimer.reset();
		counter++;
		if (counter >= 16)
			counter = 0;
	}

	const auto viewSizePixels = renderer.size();
	for(int col = 0; col < viewSizePixels.y; col += TileSize)
	{
		for(int row = 0; row < viewSizePixels.x; row += TileSize)
		{
			renderer.drawImage(mMud, NAS2D::Point{row, col});
		}
	}

	if (mMultiply)
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	for(int col = 0; col < viewSizePixels.y; col += TileSize)
	{
		for(int row = 0; row < viewSizePixels.x; row += TileSize)
		{
			renderer.drawSubImage(*mCurrentCaustics, NAS2D::Point{row, col}, NAS2D::Rectangle{(counter % 4) * TileSize, ((counter % 16) / 4) * TileSize, TileSize, TileSize});
		}
	}
	if (mMultiply)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	renderer.drawText(mFont, "Blending Demo", NAS2D::Point{5, 5}, NAS2D::Color::White);
	renderer.drawText(mSmallFont, "Press keys 1 - 6 to change blend modes.", NAS2D::Point{5, 5 + mFont.height()}, NAS2D::Color::White);
	renderer.drawText(mSmallFont, mBlendingModeText, NAS2D::Point{renderer.size().x - mSmallFont.width(mBlendingModeText) - 5, 5}, NAS2D::Color::White);
	renderer.drawText(mSmallFont, "FPS: " + std::to_string(mFps.fps()), NAS2D::Point{-65, -mSmallFont.height() - 5} + renderer.size(), NAS2D::Color::White);

	return this;
}


void Test3State::onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier /*mod*/, bool repeat)
{
	if (repeat)
		return;

	if (key == NAS2D::EventHandler::KeyCode::KEY_ESCAPE)
		NAS2D::postQuitEvent();

	if (key == NAS2D::EventHandler::KeyCode::KEY_1)
	{
		mCurrentCaustics = &mCaustics1;
		mBlendingModeText = "Alpha";
		mMultiply = false;
	}
	if (key == NAS2D::EventHandler::KeyCode::KEY_2)
	{
		mCurrentCaustics = &mCaustics2;
		mBlendingModeText = "Multiply";
		mMultiply = true;
	}
	if (key == NAS2D::EventHandler::KeyCode::KEY_3)
	{
		mCurrentCaustics = &mCaustics2;
		mBlendingModeText = "Caustics Only";
		mMultiply = false;
	}
	if (key == NAS2D::EventHandler::KeyCode::KEY_4)
	{
		mCurrentCaustics = &mCaustics3;
		mBlendingModeText = "Alpha";
		mMultiply = false;
	}
	if (key == NAS2D::EventHandler::KeyCode::KEY_5)
	{
		mCurrentCaustics = &mCaustics4;
		mBlendingModeText = "Multiply";
		mMultiply = true;
	}
	if (key == NAS2D::EventHandler::KeyCode::KEY_6)
	{
		mCurrentCaustics = &mCaustics4;
		mBlendingModeText = "Caustics Only";
		mMultiply = false;
	}
}
