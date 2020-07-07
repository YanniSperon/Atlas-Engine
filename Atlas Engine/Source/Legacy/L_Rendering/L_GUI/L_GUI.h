#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Legacy/L_LevelEditor/L_LevelEditor.h"

namespace L_Atlas {

	class L_GUI {
	public:
		static void Initialize(GLFWwindow* window);
		static void LoadLevelEditorGUI(GLFWwindow* window, L_LevelEditor::L_EditorType currentEditorType, L_LevelEditor::L_Mode currentMode, unsigned int& selectedObject, bool& EnableWireframe);
		static void LoadPhysicsSimulatorGUI();
		static void Draw();
		static void Terminate();
	};
}