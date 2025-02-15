#pragma once

#include <Shared/S_input/S_Input.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Input {

	class InputHandler {
	public:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);

		static void ProcessEvents(KeyboardInput* keyIn, MouseInput* mouseIn);

		static void Flush(KeyboardInput* keyIn, MouseInput* mouseIn);
	};
}