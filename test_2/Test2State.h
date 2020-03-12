#include "NAS2D/NAS2D.h"

using namespace NAS2D;

class Test2State: public State
{
public:
	Test2State();
	~Test2State();

protected:
	void initialize() override;
	State* update() override;


	void onKeyDown(EventHandler::KeyCode key, EventHandler::KeyModifier mod, bool repeat);
	void onMouseMove(int x, int y, int relX, int relY);
	void onMouseDown(EventHandler::MouseButton button, int x, int y);

	void onWindowResized(int w, int h);

private:
	Timer		mTimer;

	FpsCounter	mFps;

	Font		mFont;
	
	Image		mImage1;
	Image		mArrows;

	Image		mRenderTarget;

	Point_2d	mMousePosition;
};
