#pragma once

#include "Legacy/L_LevelEditor/L_LevelEditor.h"

namespace L_Atlas {
	class L_RenderingEngine {
	public:
		static void Initialize();
		static void Begin();
		static void BeginPhysicsSimulator();
		static void Render(bool& EnableWireframe, bool& EnableGUI, L_LevelEditor::L_EditorType& currentEditorType, L_LevelEditor::L_Mode& currentMode, unsigned int& selectedObject);
		static void End();
		static void Cleanup();
	};
}