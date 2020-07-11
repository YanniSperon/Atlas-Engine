#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>

#include "Scene.h"
#include "Shared/S_Input/S_Input.h"
#include "GLFW/glfw3.h"

namespace Atlas {
	class GlobalVariables {
	private:

	public:
		GlobalVariables();

		std::vector<std::string> consoleLog;
		std::chrono::steady_clock::time_point systemStartTime;
		int screenWidth;
		int screenHeight;

		Input::KeyboardInput keyIn;
		Input::MouseInput mouseIn;

		bool shouldReceiveInput;

		std::unordered_map<std::string, Mesh3D> loadedMeshes;
		std::unordered_map<std::string, Shader*> loadedShaders;
		std::unordered_map<std::string, Texture*> loadedTextures;

		GLFWwindow* window;
	};
}