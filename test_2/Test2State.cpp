#include "Test2State.h"


Test2State::Test2State():	mFont("fonts/opensans-bold.ttf", 14),
							mBackgroundImage(),
							mPointer("graphics/pointer.png")
{}


Test2State::~Test2State()
{
	Utility<EventHandler>::get().mouseMotion().disconnect(this, &Test2State::onMouseMove);
	Utility<EventHandler>::get().mouseButtonDown().disconnect(this, &Test2State::onMouseDown);
	Utility<EventHandler>::get().keyDown().disconnect(this, &Test2State::onKeyDown);
}

void Test2State::initialize()
{
	Utility<EventHandler>::get().mouseMotion().connect(this, &Test2State::onMouseMove);
	Utility<EventHandler>::get().mouseButtonDown().connect(this, &Test2State::onMouseDown);
	Utility<EventHandler>::get().keyDown().connect(this, &Test2State::onKeyDown);

	Utility<Renderer>::get().showSystemPointer(true);
}


State* Test2State::update()
{
	Renderer& r = Utility<Renderer>::get();

	r.clearScreen(NAS2D::COLOR_BLACK);

	r.drawText(mFont, "NAS2D Renderer Test", 10, 10, 255, 255, 255);

	r.drawBox(10, 50, 40, 40, 255, 255, 255);
	r.drawBoxFilled(70, 50, 40, 40, 200, 0, 0);

	r.drawGradient(10, 100, 100, 100, COLOR_BLUE, COLOR_BRIGHT_GREEN, COLOR_RED, COLOR_MAGENTA);

	r.drawCircle(150, 70, 20, 0, 200, 0, 255, 16);

	return this;
}


void Test2State::onKeyDown(EventHandler::KeyCode key, EventHandler::KeyModifier mod, bool repeat)
{
	switch (key)
	{
		case EventHandler::KEY_ESCAPE:
			postQuitEvent();
			break;
		default:
			break;
	}
}


void Test2State::onMouseMove(int x, int y, int relX, int relY)
{
}


void Test2State::onMouseDown(EventHandler::MouseButton button, int x, int y)
{
}
