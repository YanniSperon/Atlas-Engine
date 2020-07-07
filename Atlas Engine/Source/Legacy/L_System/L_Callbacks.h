#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_System.h"

namespace L_Atlas {

	class L_Callbacks {
	public:
		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			if (L_Global::Variables.enableMouseMove) {
				L_Global::Variables.mouseX = xpos;
				L_Global::Variables.mouseY = ypos;
				if (ypos * L_Global::Variables.mouseSensitivity > 89.0f) {
					double newMouseY = 89.0f / L_Global::Variables.mouseSensitivity;
					glfwSetCursorPos(window, xpos, newMouseY);
					L_Global::Variables.activeCamera->LookAt(xpos, newMouseY);
				}
				else if (ypos * L_Global::Variables.mouseSensitivity < -89.0f) {
					double newMouseY = -89.0f / L_Global::Variables.mouseSensitivity;
					glfwSetCursorPos(window, xpos, newMouseY);
					L_Global::Variables.activeCamera->LookAt(xpos, newMouseY);
				}
				else {
					L_Global::Variables.activeCamera->LookAt(xpos, ypos);
				}
			}
		}

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			L_Global::Variables.currentWidth = width;
			L_Global::Variables.currentHeight = height;
			if (width > 0 && height > 0) {
				glViewport(0, 0, width, height);
			}
		}

		static void errorCallback(int error, const char* description)
		{
			L_System::Err("Error " + std::to_string(error) + ": " + std::string(description));
		}

		static void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
			if (severity != GL_DEBUG_SEVERITY_LOW) {
				(void)source; (void)type; (void)id;
				(void)severity; (void)length; (void)userParam;
				std::string sMessage = std::string((const char*)message);
				if (sMessage.find("Buffer detailed info") == std::string::npos) {
					L_System::Err("GLError: \"" + sMessage);
					if (severity == GL_DEBUG_SEVERITY_HIGH) {
						L_System::Err("    FATAL GLERROR!");
						abort();
					}
				}
			}
		}
	};
}