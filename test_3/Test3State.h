#include <NAS2D/NAS2D.h>

using namespace NAS2D;

class Test3State: public NAS2D::State
{
public:
	Test3State();

protected:
	void initialize() override;
	State* update() override;

	void onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier mod, bool repeat);

private:

	NAS2D::Timer mCausticsTimer; /**< Caustics timer. */

	NAS2D::FpsCounter mFps; /**< FPS Counter */

	NAS2D::Font mFont; /**< Main font. */
	NAS2D::Font mSmallFont; /**< FPS font. */

	NAS2D::Image mMud; /**< Background image. */
	NAS2D::Image mCaustics1; /**< Caustics image atlas. */
	NAS2D::Image mCaustics2; /**< Caustics image atlas with no alpha. */

	NAS2D::Image mCaustics3; /**< Caustics image atlas. */
	NAS2D::Image mCaustics4; /**< Caustics image atlas with no alpha. */

	NAS2D::Image* mCurrentCaustics;

	bool mMultiply; /**< Flag to indicate that we want to draw screen blend mode. */
	bool mCausticsOnly; /**< Flag to indicate that we only want to show the caustics. */
};
