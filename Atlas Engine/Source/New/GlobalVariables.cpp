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

	shouldReceiveInput = true;

	loadedMeshes = std::unordered_map<std::string, Mesh3D>();
	loadedShaders = std::unordered_map<std::string, Shader*>();
	loadedTextures = std::unordered_map<std::string, Texture*>();

	window = nullptr;
}
