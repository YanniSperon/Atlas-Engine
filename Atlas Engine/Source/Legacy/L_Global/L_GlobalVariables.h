#pragma once

#include "Legacy/L_System/L_Config.h"
#include "Legacy/L_Rendering/L_Scene/L_Camera.h"
#include "Shared/S_Input/S_Input.h"
#include "Legacy/L_Rendering/L_Scene/L_Shader.h"
#include "Legacy/L_Game/L_Scene.h"
#include "Legacy/L_Rendering/L_GUI/L_Primitives/L_Object2D.h"
#include "Legacy/L_Physics/L_PhysicsEngine.h"
#include "Legacy/L_Rendering/L_Scene/L_SimpleRenderer.h"
#include <chrono>
#include <unordered_map>
#include <vector>

namespace L_Atlas {

	class L_GlobalVariables {
	public:
		L_GlobalVariables();
		
		std::vector<std::string> consoleLog;

		std::chrono::steady_clock::time_point systemStartTime;

		L_Config config;

		double mouseX;
		double mouseY;

		float movementSpeed;
		float originalMovementSpeed;
		bool isPaused;

		bool fullscreen;
		bool forceFullscreen;
		float mouseSensitivity;
		float FOV;
		int initialWidth;
		int initialHeight;
		bool hasVR;
		bool VSyncPreference;
		L_MouseMode mouseMode;

		L_Camera* activeCamera;

		int currentWidth;
		int currentHeight;

		KeyboardInput keyIn;
		MouseInput mouseIn;
		
		bool enableMouseClick;
		bool enableMouseMove;
		bool enableKeyboard;
		
		std::unordered_map<std::string, L_ShapeData> meshCache;

		std::unordered_map<std::string, L_Shader*> shaderCache;
	
		std::unordered_map<std::string, GLuint> textureCache;

		std::unordered_map<std::string, std::string> loadedL_MeshCache;

		std::unordered_map<std::string, std::string> loadedTextureCache;

		std::unordered_map<std::string, std::string> loadedShaderCache;

		std::unordered_map<std::string, std::string> loadedPostProcessingShaderCache;

		L_Scene currentScene;

		GLFWwindow* window;

		L_SimpleRenderer* currentRenderer;
	};

}