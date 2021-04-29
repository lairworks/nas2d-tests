#include "NAS2D/NAS2D.h"


class Test2State: public NAS2D::State
{
public:
	Test2State();
	~Test2State();

protected:
	void initialize() override;
	State* update() override;

	void onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier mod, bool repeat);
	void onMouseMove(int x, int y, int relX, int relY);
	void onMouseDown(NAS2D::EventHandler::MouseButton button, int x, int y);

	void onWindowResized(NAS2D::Vector<int> newSize);

private:
	NAS2D::Timer mTimer;
	NAS2D::FpsCounter mFps;
	const NAS2D::Font mFont;
	const NAS2D::Image mImage1;
	const NAS2D::Image mArrows;
	NAS2D::Point<int> mMousePosition;
};
