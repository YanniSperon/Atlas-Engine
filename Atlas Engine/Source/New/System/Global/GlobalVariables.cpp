#include "GlobalVariables.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"

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

	mesh3DManager = Mesh3DManager();
	mesh2DManager = Mesh2DManager();
	shaderManager = ShaderManager();
	textureManager = TextureManager();
}