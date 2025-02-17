#include "NAS2D/NAS2D.h"


class Test2State: public NAS2D::State
{
public:
	Test2State();
	~Test2State();

protected:
	void initialize() override;
	State* update() override;

	void onKeyDown(NAS2D::KeyCode key, NAS2D::KeyModifier mod, bool repeat);
	void onMouseMove(NAS2D::Point<int> position, NAS2D::Vector<int> change);
	void onMouseDown(NAS2D::MouseButton button, NAS2D::Point<int> position);

	void onWindowResized(NAS2D::Vector<int> newSize);

private:
	NAS2D::Timer mTimer;
	NAS2D::FpsCounter mFps;
	const NAS2D::Font mFont;
	const NAS2D::Image mImage1;
	const NAS2D::Image mArrows;
	NAS2D::Point<int> mMousePosition;
};
