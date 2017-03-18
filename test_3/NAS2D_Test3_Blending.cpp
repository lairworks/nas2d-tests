// ==================================================================================
// = NAS2D Test 3: Blending and Blend Modes
// ==================================================================================
// = Provides an example of setting different blend modes and displays the output.
// ==================================================================================
#include "NAS2D/NAS2D.h"
#include "Test3State.h"

#include <iostream>
#include <string>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

const std::string APPLICATION_TITLE = "NAS2D Test App3";

int main(int argc, char *argv[])
{
	try
	{
		Game game(APPLICATION_TITLE, argv[0]);
		game.go(new Test3State());
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
