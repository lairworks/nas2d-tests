// ==================================================================================
// = NAS2D Test App 2
// = Copyright © 2008 - 2019 LairWorks Entertainment
// ==================================================================================
// = NAS2D is distributed under the terms of the zlib license. You are free to copy,
// = modify and distribute the software under the terms of the zlib license.
// = 
// = Acknowledgement of your use of NAS2D is appriciated but is not required.
// ==================================================================================
#include "NAS2D/NAS2D.h"
#include "Test2State.h"

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <iostream>

const std::string APPLICATION_TITLE = "NAS2D Test 2: Renderer Functions";


int main(int /*argc*/, char *argv[])
{

	try
	{
		Game game(APPLICATION_TITLE, "NAS2D_Test2", "LairWorks Entertainment", argv[0]);
		game.go(new Test2State());
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
