// ==================================================================================
// = NAS2D
// = Copyright © 2008 - 2014 New Age Software
// ==================================================================================
// = NAS2D is distributed under the terms of the zlib license. You are free to copy,
// = modify and distribute the software under the terms of the zlib license.
// = 
// = Acknowledgement of your use of NAS2D is appriciated but is not required.
// ==================================================================================

#include "NAS2D/NAS2D.h"

#include "Test2State.h"

#ifdef WINDOWS
#include <Windows.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{

	try
	{
		Game game("NAS2D Test 2: Renderer Functions", argv[0]);
		game.go(new Test2State());
	}
	catch(std::exception& e)
	{
		stringstream errorMessage;
		errorMessage << e.what() << endl;
	
		#if defined(WINDOWS)
		MessageBoxA(NULL, "Application Error", e.what(), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		#endif
	}
	catch(...)
	{
	}

	return 0;
}
