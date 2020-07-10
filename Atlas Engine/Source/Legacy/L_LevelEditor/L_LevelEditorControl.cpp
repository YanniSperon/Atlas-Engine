#include "L_LevelEditorControl.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Physics/L_PhysicsEngine.h"

void L_LevelEditor::L_LevelEditorControl::Control(L_LevelEditor::L_EditorType& currentEditorType, L_LevelEditor::L_Mode& currentMode, unsigned int& selectedObject, float deltaTime)
{
	if (L_Atlas::L_Global::Variables.keyIn.leftShiftHeld) {
		L_Atlas::L_Global::Variables.movementSpeed = 2.0f * L_Atlas::L_Global::Variables.originalMovementSpeed;
	}
	if (L_Atlas::L_Global::Variables.keyIn.leftShiftReleased) {
		L_Atlas::L_Global::Variables.movementSpeed = L_Atlas::L_Global::Variables.originalMovementSpeed;
	}
	if (L_Atlas::L_Global::Variables.keyIn.capsLockHeld) {
		L_Atlas::L_Global::Variables.movementSpeed = 0.5f * L_Atlas::L_Global::Variables.originalMovementSpeed;
	}
	if (L_Atlas::L_Global::Variables.keyIn.capsLockReleased) {
		L_Atlas::L_Global::Variables.movementSpeed = L_Atlas::L_Global::Variables.originalMovementSpeed;
	}

	if (L_Atlas::L_Global::Variables.keyIn.onePressed) {
		currentEditorType = L_LevelEditor::L_EditorType::Scene;
	}
	if (L_Atlas::L_Global::Variables.keyIn.twoPressed) {
		currentEditorType = L_LevelEditor::L_EditorType::light;
	}

	if ((L_Atlas::L_Global::Variables.currentScene.objectsOnScene.size() > 0 && currentEditorType == L_LevelEditor::L_EditorType::Scene) || (currentEditorType == L_LevelEditor::L_EditorType::light)) {
		if (L_Atlas::L_Global::Variables.keyIn.cPressed) {
			currentMode = L_LevelEditor::L_Mode::cam;
		}
		else if (L_Atlas::L_Global::Variables.keyIn.ePressed) {
			currentMode = L_LevelEditor::L_Mode::scale;
		}
		else if (L_Atlas::L_Global::Variables.keyIn.rPressed) {
			currentMode = L_LevelEditor::L_Mode::rotate;
		}
		else if (L_Atlas::L_Global::Variables.keyIn.vPressed) {
			currentMode = L_LevelEditor::L_Mode::translate;
		}
		else if (L_Atlas::L_Global::Variables.keyIn.tPressed) {
			currentMode = L_LevelEditor::L_Mode::texture;
		}
	}
	else {
		currentMode = L_LevelEditor::L_Mode::cam;
	}
	///////////////////////////////////////////////////////////////////////////
	if (currentEditorType == L_LevelEditor::L_EditorType::Scene) {
		if (currentMode == L_LevelEditor::L_Mode::scale) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, 0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->ScaleAdd3f(0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == L_LevelEditor::L_Mode::translate) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, 0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->TranslateAdd3f(0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == L_LevelEditor::L_Mode::cam) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveForward(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveBackward(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.activeCamera->StrafeLeft(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.activeCamera->StrafeRight(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveUp(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveDown(deltaTime);
			}
		}
		else if (currentMode == L_LevelEditor::L_Mode::rotate) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime));
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, 0.0f, glm::degrees(L_Atlas::L_Global::Variables.movementSpeed * deltaTime));
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(glm::degrees(L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene[selectedObject]->RotateAdd3f(0.0f, glm::degrees(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
		}

		if (L_Atlas::L_Global::Variables.keyIn.leftBracketPressed) {
			if (selectedObject > 0) {
				selectedObject--;
			}
		}
		if (L_Atlas::L_Global::Variables.keyIn.rightBracketPressed) {
			if (selectedObject < L_Atlas::L_Global::Variables.currentScene.objectsOnScene.size() - 1) {
				selectedObject++;
			}
		}
		if (L_Atlas::L_Global::Variables.keyIn.nPressed) {
			L_Atlas::L_System::Log("Cube created!");
			L_Atlas::L_Global::Variables.currentScene.objectsOnScene.push_back(new L_Atlas::L_Object(L_Atlas::L_Type::cubeModel, "", "", "Resources/images/textures/", "newcow.png", "Resources/shaders/", "Lighting.shader", true, true, L_Atlas::L_System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), L_Atlas::L_Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)));
			selectedObject = L_Atlas::L_Global::Variables.currentScene.objectsOnScene.size() - 1;
		}
		if (L_Atlas::L_Global::Variables.keyIn.backspacePressed) {
			if (L_Atlas::L_Global::Variables.currentScene.objectsOnScene.size() > 0) {
				L_Atlas::L_System::Log("Object deleted!");
				delete L_Atlas::L_Global::Variables.currentScene.objectsOnScene.at(selectedObject);
				L_Atlas::L_Global::Variables.currentScene.objectsOnScene.erase(L_Atlas::L_Global::Variables.currentScene.objectsOnScene.begin() + selectedObject);

				if (selectedObject > 0) {
					selectedObject--;
				}
				else {
					selectedObject = 0;
				}
			}
		}
	}
	else if (currentEditorType == L_LevelEditor::L_EditorType::light) {
		if (currentMode == L_LevelEditor::L_Mode::scale) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, 0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, 0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->ScaleAdd3f(0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == L_LevelEditor::L_Mode::translate) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, 0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, 0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->TranslateAdd3f(0.0f, -L_Atlas::L_Global::Variables.movementSpeed * deltaTime, 0.0f);
			}
		}
		else if (currentMode == L_LevelEditor::L_Mode::cam) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveForward(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveBackward(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.activeCamera->StrafeLeft(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.activeCamera->StrafeRight(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveUp(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.activeCamera->MoveDown(deltaTime);
			}
		}
		else if (currentMode == L_LevelEditor::L_Mode::rotate) {
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, 0.0f, glm::degrees(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime));
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, 0.0f, glm::degrees(L_Atlas::L_Global::Variables.movementSpeed * deltaTime));
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(glm::degrees(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(glm::degrees(L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f, 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, glm::degrees(L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				L_Atlas::L_Global::Variables.currentScene.lightsOnScene.at(0)->RotateAdd3f(0.0f, glm::degrees(-L_Atlas::L_Global::Variables.movementSpeed * deltaTime), 0.0f);
			}
		}
	}
}
