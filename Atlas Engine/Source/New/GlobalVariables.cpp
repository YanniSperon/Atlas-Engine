#include "GlobalVariables.h"

Atlas::GlobalVariables::GlobalVariables()
{
	// Initialize default values

	consoleLog = std::vector<std::string>();
	systemStartTime = std::chrono::high_resolution_clock::now();
	screenWidth = 1920;
	screenHeight = 1080;

	keyIn = Input::KeyboardInput();
	mouseIn = Input::MouseInput();

	window = nullptr;

	shouldReceiveInput = true;
}
