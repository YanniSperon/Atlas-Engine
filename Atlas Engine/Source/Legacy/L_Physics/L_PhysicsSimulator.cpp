#include "L_PhysicsSimulator.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Legacy/L_Game/L_Physics/L_PhysicsScene.h"
#include "Legacy/L_Global/L_Global.h"
#include "Shared/S_Input/S_InputHandler.h"
#include "Legacy/L_Rendering/L_RenderingEngine.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Rendering/L_FX/L_PostProcessor.h"
#include "Legacy/L_Rendering/L_GUI/L_GUI.h"
#include "Legacy/L_Other/L_Timer.h"

namespace L_Atlas {
	
	void L_PhysicsSimulator::LaunchSimulation(L_Scene* SceneToSimulate, double timeConstant)
	{
		L_System::Warn("Physics Simulator entered");
		L_Camera* originalCamera = L_Global::Variables.activeCamera;
		L_PhysicsEngine::Initialize();
		bool shouldExit = false;
		L_PhysicsRenderer renderer = L_PhysicsRenderer();
		L_PhysicsScene physicsScene = L_PhysicsScene(SceneToSimulate);
		L_PhysicsEngine::SetL_PhysicsScene(&physicsScene);
		bool shouldReenableMovementControls = false;
		if (originalCamera->GetHasLookControls()) {
			shouldReenableMovementControls = true;
			originalCamera->SetHasLookControls(false);
		}
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto currentTime = lastTime;
		L_Timer shootTimer(0.1f);
		while (!shouldExit && !glfwWindowShouldClose(L_Global::Variables.window)) {
			///////////////////////////////////////////////////////////////////////////
			glfwPollEvents();
			Input::InputHandler::ProcessEvents(&L_Global::Variables.keyIn, &L_Global::Variables.mouseIn, true);
			///////////////////////////////////////////////////////////////////////////
			currentTime = std::chrono::high_resolution_clock::now();
			auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
			lastTime = currentTime;
			double deltaTime = deltaTimeNanoseconds.count() / 1000000000.0 * timeConstant;
			///////////////////////////////////////////////////////////////////////////
			if (L_Global::Variables.keyIn.escapePressed) {
				shouldExit = true;
				L_System::Warn("Physics Simulator exited");
			}
			if (L_Atlas::L_Global::Variables.keyIn.wHeld) {
				physicsScene.playersOnScene.at(0)->MoveForward(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.sHeld) {
				physicsScene.playersOnScene.at(0)->MoveBackward(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.aHeld) {
				physicsScene.playersOnScene.at(0)->StrafeLeft(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.dHeld) {
				physicsScene.playersOnScene.at(0)->StrafeRight(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.spaceHeld) {
				physicsScene.playersOnScene.at(0)->MoveUp(deltaTime);
			}
			if (L_Atlas::L_Global::Variables.keyIn.leftControlHeld) {
				physicsScene.playersOnScene.at(0)->MoveDown(deltaTime);
			}
			if (L_Global::Variables.mouseIn.leftClicked) {
				physicsScene.physicsObjectsOnScene.push_back(new L_PhysicsObject(new L_Object(L_Type::cubeModel, "", "", "Resources/images/textures/", "newcow.png", "Resources/shaders/", "Lighting.shader", true, true, L_System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), physicsScene.playersOnScene.at(0)->GetTranslation(), glm::vec3(0.25f, 0.25f, 0.5f)), 50.0f));
				physicsScene.physicsObjectsOnScene.at(physicsScene.physicsObjectsOnScene.size() - 1)->Launch(physicsScene.playersOnScene.at(0)->GetViewDirection());
				shootTimer.Reset(0.1f);
				shootTimer.Start();
			}
			if (L_Global::Variables.mouseIn.leftHeld) {
				shootTimer.ElapseTime(deltaTime);
				if (shootTimer.HasFinished()) {
					physicsScene.physicsObjectsOnScene.push_back(new L_PhysicsObject(new L_Object(L_Type::cubeModel, "", "", "Resources/images/textures/", "newcow.png", "Resources/shaders/", "Lighting.shader", true, true, L_System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), physicsScene.playersOnScene.at(0)->GetTranslation(), glm::vec3(0.25f, 0.25f, 0.5f)), 50.0f));
					physicsScene.physicsObjectsOnScene.at(physicsScene.physicsObjectsOnScene.size() - 1)->Launch(physicsScene.playersOnScene.at(0)->GetViewDirection());
					shootTimer.Reset(0.1f);
					shootTimer.Start();
				}
			}
			physicsScene.playersOnScene.at(0)->BringWith(physicsScene.playersOnScene.at(0)->GetPlayerModel());
			L_PhysicsEngine::Update(deltaTime);
			///////////////////////////////////////////////////////////////////////////
			L_RenderingEngine::BeginPhysicsSimulator();
			///////////////////////////////////////////////////////////////////////////
			physicsScene.playersOnScene.at(0)->LookAt(L_Global::Variables.mouseX, L_Global::Variables.mouseY);
			physicsScene.Submit(&renderer, physicsScene.playersOnScene.at(0));
			physicsScene.playersOnScene.at(0)->ChangeMovementSpeed(L_Global::Variables.movementSpeed);
			renderer.SimpleFlush(physicsScene.playersOnScene.at(0), L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, L_Global::Variables.FOV, physicsScene.physicsL_LightsOnScene.at(0));
			///////////////////////////////////////////////////////////////////////////
			L_PhysicsEngine::DrawDebug();
			///////////////////////////////////////////////////////////////////////////
			L_PostProcessor::RenderPhysicsRenderer(&renderer, &physicsScene);
			L_GUI::LoadPhysicsSimulatorGUI();
			L_GUI::Draw();
			///////////////////////////////////////////////////////////////////////////
			L_RenderingEngine::End();
			///////////////////////////////////////////////////////////////////////////
			Input::InputHandler::Flush(&L_Global::Variables.keyIn, &L_Global::Variables.mouseIn);
			///////////////////////////////////////////////////////////////////////////
		}
		if (shouldReenableMovementControls) {
			originalCamera->SetHasLookControls(true);
		}
		originalCamera->BringWith(originalCamera->GetSkybox());
		L_Camera::SetFocus(originalCamera);
		L_PhysicsEngine::Cleanup();
	}
}
