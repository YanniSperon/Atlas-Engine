#include "L_GlobalVariables.h"

namespace L_Atlas {

	L_GlobalVariables::L_GlobalVariables()
	{
		systemStartTime = std::chrono::high_resolution_clock::now();
		config = L_Config("Resources/other/", "config.cfg");

		mouseX = 0.0;
		mouseY = 0.0;
		movementSpeed = 10.0f;
		originalMovementSpeed = movementSpeed;
		isPaused = false;

		fullscreen = config.GetFullscreenPreference();
		forceFullscreen = config.GetForceFullscreen();
		mouseSensitivity = config.GetMouseSensitivityPreference();
		FOV = config.GetFOVPreference();
		initialWidth = config.GetInitialWidthPreference();
		initialHeight = config.GetInitialHeightPreference();
		hasVR = config.GetVRPreference();
		VSyncPreference = config.GetVSyncPreference();
		mouseMode = config.GetMouseMode();

		activeCamera = new L_Camera(true, movementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), mouseSensitivity, nullptr);

		currentWidth = initialWidth;
		currentHeight = initialHeight;

		keyIn = Input::KeyboardInput();
		mouseIn = Input::MouseInput();

		enableMouseClick = true;
		enableMouseMove = true;
		enableKeyboard = true;

		consoleLog = std::vector<std::string>();

		for (int i = 0; i < 10; i++) {
			consoleLog.push_back("");
		}

		meshCache = std::unordered_map<std::string, L_ShapeData>();
		
		shaderCache = std::unordered_map<std::string, L_Shader*>();

		textureCache = std::unordered_map<std::string, GLuint>();

		loadedL_MeshCache = std::unordered_map<std::string, std::string>();
		
		loadedTextureCache = std::unordered_map<std::string, std::string>();
		
		loadedShaderCache = std::unordered_map<std::string, std::string>();

		loadedPostProcessingShaderCache = std::unordered_map<std::string, std::string>();

		currentScene = L_Scene();
		currentScene.camerasOnScene.push_back(activeCamera);

		window = nullptr;

		currentRenderer = nullptr;
	}
}