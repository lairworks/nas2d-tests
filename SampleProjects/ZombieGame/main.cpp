// ==================================================================================
// = NAS2D Test App 1
// = Copyright © 2008 - 2017 New Age Software
// ==================================================================================
// = NAS2D is distributed under the terms of the zlib license. You are free to copy,
// = modify and distribute the software under the terms of the zlib license.
// = 
// = Acknowledgement of your use of NAS2D is appriciated but is not required.
// ==================================================================================
#include "NAS2D/NAS2D.h"
#include "GameState.h"

#include <iostream>
#include <string>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif


int main(int /*argc*/, char* /*argv*/[])
{
	try
	{
		NAS2D::Game game("NAS2D Sample Application", "NAS2D_Test", "LairWorks Entertainment");
		NAS2D::Utility<NAS2D::Renderer>::get().size({800, 600});
		game.go(new GameState());
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;

		#ifdef WINDOWS
		MessageBoxA(NULL, e.what(), "Application Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		#endif
	}
	catch(...)
	{
		std::cout << "Unknown error occurred." << std::endl;

		#ifdef WINDOWS
		MessageBoxA(NULL, "Unknown error occurred.", "Unexpected Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		#endif
	}

	return 0;
}
