#pragma once
#include "Legacy/L_Rendering/L_Scene/L_Object.h"
#include "Legacy/L_LevelEditor/L_LevelEditor.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

namespace L_Atlas {

	class L_Window {
	public:
		static void DrawInfoWindow(L_LevelEditor::L_EditorType& currentEditorType, L_LevelEditor::L_Mode& currentMode);
		static void DrawDebug(bool& EnableConsole, bool& EnableWireframe);
		static void DrawFPSCounter();
		static void DrawFileManager(GLFWwindow* window);
		static void DrawPostProcessingManager(GLFWwindow* window);
		static void DrawSpawnWindow(std::vector<L_Object*>& objectsOnScene, unsigned int& selectedObject);
		static void DrawObjectSettingsWindow(L_Object* object);
		static void DrawPhysicsManager(double& timeConstant);
	};
}