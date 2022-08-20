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
	mArrows("gui/default/arrow.png")
{}


Test2State::~Test2State()
{
	auto& eventHandler = NAS2D::Utility<NAS2D::EventHandler>::get();
	eventHandler.mouseMotion().disconnect(this, &Test2State::onMouseMove);
	eventHandler.mouseButtonDown().disconnect(this, &Test2State::onMouseDown);
	eventHandler.keyDown().disconnect(this, &Test2State::onKeyDown);
	eventHandler.windowResized().disconnect(this, &Test2State::onWindowResized);
}

void Test2State::initialize()
{
	auto& eventHandler = NAS2D::Utility<NAS2D::EventHandler>::get();
	eventHandler.mouseMotion().connect(this, &Test2State::onMouseMove);
	eventHandler.mouseButtonDown().connect(this, &Test2State::onMouseDown);
	eventHandler.keyDown().connect(this, &Test2State::onKeyDown);
	eventHandler.windowResized().connect(this, &Test2State::onWindowResized);

	auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();
	renderer.showSystemPointer(true);
	renderer.window_icon("NAS2D.ico");
	renderer.minimumSize({800, 600});
}


NAS2D::State* Test2State::update()
{
	auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();

	renderer.clearScreen(NAS2D::Color::Gray);

	renderer.drawText(mFont, "NAS2D Renderer Test", NAS2D::Point{10, 10}, NAS2D::Color::White);

	renderer.drawBox(NAS2D::Rectangle{10, 50, 40, 40}, NAS2D::Color::White);
	renderer.drawBoxFilled(NAS2D::Rectangle{70, 50, 40, 40}, NAS2D::Color{200, 0, 0});

	renderer.drawGradient(NAS2D::Rectangle{10, 100, 100, 100}, NAS2D::Color::Blue, NAS2D::Color::Green, NAS2D::Color::Red, NAS2D::Color::Magenta);

	renderer.drawCircle(NAS2D::Point{150, 70}, 20, NAS2D::Color{0, 200, 0, 255}, 16);
	renderer.drawCircle(NAS2D::Point{150, 120}, 20, NAS2D::Color{0, 200, 0, 255}, 16, NAS2D::Vector<float>{0.5, 1.0});
	renderer.drawCircle(NAS2D::Point{150, 170}, 20, NAS2D::Color{0, 200, 0, 255}, 16, NAS2D::Vector<float>{1.0, 0.5});

	renderer.drawImage(mImage1, NAS2D::Point{200, 20}, 0);
	renderer.drawImageRotated(mImage1, NAS2D::Point{500, 20}, (mTimer.tick() / 20.0f));

	renderer.drawSubImage(mImage1, NAS2D::Point{10, 250}, NAS2D::Rectangle{0, 0, 64, 64});
	renderer.drawSubImageRotated(mImage1, NAS2D::Point{100, 250}, NAS2D::Rectangle{0, 0, 64, 64}, (mTimer.tick() / 20.0f));

	renderer.drawImageRotated(mImage1, NAS2D::Point{500, 300}, -(mTimer.tick() / 20.0f));

	for (int i = 0; i < 2000; ++i)
	{
		uint8_t grey = 100 + jitter() * 2;
		renderer.drawPoint(NAS2D::Point{10 + jitter(), 330 + jitter()}, NAS2D::Color{grey, grey, grey});
	}

	renderer.drawImageRepeated(mArrows, NAS2D::Rectangle{100, 330, 250, 64});

	renderer.clipRect(NAS2D::Rectangle{400, 330, 128, 128});
	renderer.drawImageRepeated(mArrows, NAS2D::Rectangle<int>::Create({0, 0}, renderer.size()));
	renderer.clipRectClear();

	renderer.drawImage(mArrows, NAS2D::Point{500, 500}, 2.0f * sin(-(mTimer.tick() / 200.0f)));

	renderer.drawSubImageRepeated(mArrows, NAS2D::Rectangle{300, 300, 200, 200}, NAS2D::Rectangle{5, 5, 10, 10});

	if (renderer.fullscreen()) renderer.drawText(mFont, "Fullsreen", NAS2D::Point{10, 500}, NAS2D::Color::White);
	else renderer.drawText(mFont, "Windowed", NAS2D::Point{10, 500}, NAS2D::Color::White);

	if (renderer.resizeable()) renderer.drawText(mFont, "Resizeable", NAS2D::Point{10, 520}, NAS2D::Color::White);
	else renderer.drawText(mFont, "Not Resizeable", NAS2D::Point{10, 520}, NAS2D::Color::White);

	renderer.drawText(mFont, "ESC: Exit | F1: Toggle Fullscreen | F2: Toggle Resizeable", NAS2D::Point{10, renderer.size().y - 10 - mFont.height()}, NAS2D::Color::White);

	return this;
}


void Test2State::onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier /*mod*/, bool /*repeat*/)
{
	switch (key)
	{
		case NAS2D::EventHandler::KeyCode::KEY_ESCAPE:
			NAS2D::postQuitEvent();
			break;
		case NAS2D::EventHandler::KeyCode::KEY_F1: {
			auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();
			renderer.fullscreen(!renderer.fullscreen());
			break;
		}
		case NAS2D::EventHandler::KeyCode::KEY_F2: {
			auto& renderer = NAS2D::Utility<NAS2D::Renderer>::get();
			renderer.resizeable(!renderer.resizeable());
			break;
		}
		default:
			break;
	}
}


void Test2State::onMouseMove(NAS2D::Point<int> /*position*/, NAS2D::Vector<int> /*change*/)
{}


void Test2State::onMouseDown(NAS2D::EventHandler::MouseButton /*button*/, NAS2D::Point<int> /*position*/)
{}


void Test2State::onWindowResized(NAS2D::Vector<int> /*newSize*/)
{}
