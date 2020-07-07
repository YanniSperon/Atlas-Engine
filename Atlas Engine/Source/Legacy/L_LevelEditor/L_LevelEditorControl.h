#pragma once

#include "L_LevelEditor.h"

namespace L_LevelEditor {
	class L_LevelEditorControl {
	public:
		static void Control(L_LevelEditor::L_EditorType& currentEditorType, L_LevelEditor::L_Mode& currentMode, unsigned int& selectedObject, float deltaTime);
	};
}