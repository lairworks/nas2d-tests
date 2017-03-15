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

#include <string>

const std::string APPLICATION_TITLE("NAS2D Sample Application");

int main(int argc, char *argv[])
{
	try
	{
		Game game(APPLICATION_TITLE, argv[0]);
		game.go(new GameState());
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	return 0;
}
