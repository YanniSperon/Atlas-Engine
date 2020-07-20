#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>

#include "Shared/S_Input/S_Input.h"
#include "GLFW/glfw3.h"
#include "New/Managers/Mesh/3D/Mesh3DManager.h"
#include "New/Managers/Mesh/2D/Mesh2DManager.h"
#include "New/Managers/Shader/ShaderManager.h"
#include "New/Managers/Texture/TextureManager.h"

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

		GLFWwindow* window;

		Mesh3DManager mesh3DManager;
		Mesh2DManager mesh2DManager;
		ShaderManager shaderManager;
		TextureManager textureManager;
	};
}