#include <GL/glew.h>

#include "Test2State.h"

#include <functional>
#include <random>


std::mt19937 generator;
std::uniform_int_distribution<int> jitter_distribution(0, 64);

auto jitter = std::bind(jitter_distribution, generator);


Test2State::Test2State() :
	mFont("fonts/opensans-bold.ttf", 16),
	mImage1("mud.png"),
	mArrows("gui/default/arrow.png"),
	mRenderTarget(256, 256)
{}


Test2State::~Test2State()
{
	Utility<EventHandler>::get().mouseMotion().disconnect(this, &Test2State::onMouseMove);
	Utility<EventHandler>::get().mouseButtonDown().disconnect(this, &Test2State::onMouseDown);
	Utility<EventHandler>::get().keyDown().disconnect(this, &Test2State::onKeyDown);
	Utility<EventHandler>::get().windowResized().disconnect(this, &Test2State::onWindowResized);
}

void Test2State::initialize()
{
	Utility<EventHandler>::get().mouseMotion().connect(this, &Test2State::onMouseMove);
	Utility<EventHandler>::get().mouseButtonDown().connect(this, &Test2State::onMouseDown);
	Utility<EventHandler>::get().keyDown().connect(this, &Test2State::onKeyDown);
	Utility<EventHandler>::get().windowResized().connect(this, &Test2State::onWindowResized);

	Utility<Renderer>::get().showSystemPointer(true);
	Utility<Renderer>::get().window_icon("NAS2D.ico");
	Utility<Renderer>::get().minimum_size(800, 600);
}


State* Test2State::update()
{
	Renderer& r = Utility<Renderer>::get();

	r.clearScreen(NAS2D::Color::Grey);

	r.drawText(mFont, "NAS2D Renderer Test", 10, 10, 255, 255, 255);

	r.drawBox(10, 50, 40, 40, 255, 255, 255);
	r.drawBoxFilled(70, 50, 40, 40, 200, 0, 0);

	r.drawGradient(10, 100, 100, 100, Color::Blue, Color::Bright_green, Color::Red, Color::Magenta);

	r.drawCircle(150, 70, 20, 0, 200, 0, 255, 16);
	r.drawCircle(150, 120, 20, 0, 200, 0, 255, 16, 0.5f);
	r.drawCircle(150, 170, 20, 0, 200, 0, 255, 16, 1.0f, 0.5f);

	r.drawImage(mImage1, 200, 20, 0);
	r.drawImageRotated(mImage1, 500, 20, (mTimer.tick() / 20.0f));

	r.drawSubImage(mImage1, 10, 250, 0, 0, 64, 64);
	r.drawSubImageRotated(mImage1, 100, 250, 0, 0, 64, 64, (mTimer.tick() / 20.0f));

	r.drawImageRotated(mImage1, 500, 300, -(mTimer.tick() / 20.0f));

	for (int i = 0; i < 2000; ++i)
	{
		int grey = jitter() * 2;
		r.drawPoint(10 + jitter(), 330 + jitter(), 100 + grey, 100 + grey, 100 + grey);
	}

	r.drawImageRepeated(mArrows, 100, 330, 250, 64);

	r.clipRect(400, 330, 128, 128);
	r.drawImageRepeated(mArrows, 0, 0, r.width(), r.height());
	r.clipRectClear();

	r.drawImage(mArrows, 500, 500, 2.0f * sin(-(mTimer.tick() / 200.0f)));

	r.drawSubImageRepeated(mArrows, 300, 300, 200, 200, 5, 5, 10, 10);

	if (r.fullscreen()) r.drawText(mFont, "Fullsreen", 10, 500, 255, 255, 255);
	else r.drawText(mFont, "Windowed", 10, 500, 255, 255, 255);

	if (r.resizeable()) r.drawText(mFont, "Resizeable", 10, 520, 255, 255, 255);
	else r.drawText(mFont, "Not Resizeable", 10, 520, 255, 255, 255);

	r.drawText(mFont, "ESC: Exit | F1: Toggle Fullscreen | F2: Toggle Resizeable", 10, r.height() - 10 - mFont.height(), 255, 255, 255);

	return this;
}


void Test2State::onKeyDown(EventHandler::KeyCode key, EventHandler::KeyModifier /*mod*/, bool /*repeat*/)
{
	switch (key)
	{
		case EventHandler::KeyCode::KEY_ESCAPE:
			postQuitEvent();
			break;
		case EventHandler::KeyCode::KEY_F1:
			Utility<Renderer>::get().fullscreen(!Utility<Renderer>::get().fullscreen());
			break;
		case EventHandler::KeyCode::KEY_F2:
			Utility<Renderer>::get().resizeable(!Utility<Renderer>::get().resizeable());
			break;
		default:
			break;
	}
}


void Test2State::onMouseMove(int /*x*/, int /*y*/, int /*relX*/, int /*relY*/)
{}


void Test2State::onMouseDown(EventHandler::MouseButton /*button*/, int /*x*/, int /*y*/)
{}


void Test2State::onWindowResized(int /*w*/, int /*h*/)
{}
