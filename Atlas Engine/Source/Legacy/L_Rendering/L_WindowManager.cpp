#include "L_WindowManager.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Legacy/L_Rendering/L_FX/L_PostProcessor.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_Callbacks.h"

namespace L_Atlas {
	bool L_Atlas::L_WindowManager::Initialize()
	{
		if (!glfwInit()) {
			L_System::Err("Error initializing GLFW!");
			return false;
		}

		if (L_Global::Variables.fullscreen) {
			L_Global::Variables.window = glfwCreateWindow(L_Global::Variables.initialWidth, L_Global::Variables.initialHeight, "Atlas", glfwGetPrimaryMonitor(), nullptr);
		}
		else {
			if (L_Global::Variables.forceFullscreen) {
				const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				if (mode->width == L_Global::Variables.currentWidth && mode->height == L_Global::Variables.currentHeight) {
					L_Global::Variables.window = glfwCreateWindow(L_Global::Variables.initialWidth, L_Global::Variables.initialHeight, "Atlas", glfwGetPrimaryMonitor(), nullptr);
				}
				else {
					//glfwWindowHint(GLFW_DECORATED, false);
					L_Global::Variables.window = glfwCreateWindow(L_Global::Variables.initialWidth, L_Global::Variables.initialHeight, "Atlas", nullptr, nullptr);
				}
			}
			else {
				//glfwWindowHint(GLFW_DECORATED, false);
				L_Global::Variables.window = glfwCreateWindow(L_Global::Variables.initialWidth, L_Global::Variables.initialHeight, "Atlas", nullptr, nullptr);
			}
		}

		if (!L_Global::Variables.window)
		{
			L_System::Err("Error initializing GLFW!");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(L_Global::Variables.window);

		//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

		glfwSwapInterval(L_Global::Variables.VSyncPreference);
		
		if (glewInit() != GLEW_OK) {
			L_System::Err("Error initializing GLEW (OpenGL)");
			return false;
		}

		glfwSetInputMode(L_Global::Variables.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (L_Global::Variables.mouseMode == L_MouseMode::raw) {
			if (glfwRawMouseMotionSupported()) {
				glfwSetInputMode(L_Global::Variables.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			}
		}
		glfwSetCursorPosCallback(L_Global::Variables.window, L_Callbacks::cursorPositionCallback);
		glfwSetFramebufferSizeCallback(L_Global::Variables.window, L_Callbacks::framebufferSizeCallback);
		glfwSetErrorCallback(L_Callbacks::errorCallback);
		
		return true;
	}
}