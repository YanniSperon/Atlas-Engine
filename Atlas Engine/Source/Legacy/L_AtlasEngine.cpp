#include "Legacy/L_AtlasEngine.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Rendering/L_WindowManager.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_Rendering/L_Scene/L_Mesh.h"
#include "Legacy/L_Rendering/L_RenderingEngine.h"
#include "Legacy/L_System/L_IO.h"
#include "Legacy/L_LevelEditor/L_LevelEditor.h"
#include "Legacy/L_LevelEditor/L_LevelEditorControl.h"
#include "Legacy/L_Rendering/L_FX/L_PostProcessor.h"
#include "Legacy/L_Rendering/L_GUI/L_GUI.h"
#include "Shared/S_Input/S_InputHandler.h"
#include "Legacy/L_Physics/L_PhysicsSimulator.h"
#include <chrono>

namespace L_Atlas {
	bool AtlasEngine::Start()
	{
		L_Atlas::L_System::SetWorkingDirectory();

		if (!L_WindowManager::Initialize()) {
			return false;
		}

		// SOUNDENGINE::INITIALIZIZEAWDIW;
		//irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
		//engine->setSoundVolume(1);

		//PhysicsEngine::Initialize();
		{
			L_RenderingEngine::Initialize();

			//Global::Variables.currentScene.camerasOnScene.push_back(new Player(true, Global::Variables.originalMovementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f, Global::Variables.mouseSensitivity, type::normalModel, "Resources/models/", "person.obj", "Resources/images/textures/", "person4k.png", "Resources/shaders/", "Lighting.shader", true, true, true, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 5.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 100.0f, Material()));
			L_Global::Variables.activeCamera->SetSkybox(new L_Object(L_Type::normalModel, "Resources/models/", "skybox.obj", "Resources/images/textures/", "skybox.png", "Resources/shaders/", "Basic.shader", true, false, L_System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 50.0f, 50.0f)));
			L_Global::Variables.currentScene.lightsOnScene.push_back(new L_Light(L_LightIntensity(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)), L_Type::cubeInvertedLighting, "", "", "Resources/images/colors/", "yellow.png", "Resources/shaders/", "Lighting.shader", true, true, L_System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), L_Material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 512.0f)));
			L_Global::Variables.currentScene.preloadedObjectsOnScene.push_back(new L_Object(L_Type::normalModel, "Resources/models/", "plane.obj", "Resources/images/colors/", "white.png", "Resources/shaders/", "Lighting.shader", true, true, L_System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f), L_Material(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f)));
			
			L_IO::LoadFile(L_Global::Variables.currentScene.objectsOnScene, "Resources/other/", "level.lvl");

			L_LevelEditor::L_EditorType currentEditorType(L_LevelEditor::Scene);
			L_LevelEditor::L_Mode currentMode(L_LevelEditor::cam);

			bool GUIEnabled = true;
			bool EnableWireframe = false;
			glm::vec3 camPos(0.0f, 0.0f, 0.0f);
			bool EditorEnabled = true;
			double timeConstant = 1.0;
			auto lastTime = std::chrono::high_resolution_clock::now();
			auto currentTime = lastTime;
			unsigned int selectedObject;
			bool shouldLaunchSimulation = false;

			if (L_Global::Variables.currentScene.objectsOnScene.size() > 0) {
				selectedObject = L_Global::Variables.currentScene.objectsOnScene.size() - 1;
			}
			else {
				selectedObject = 0;
			}
			L_Global::Variables.mouseX = 36000000.0;
			L_Global::Variables.mouseY = 0.0;
			glfwSetCursorPos(L_Global::Variables.window, 36000000.0, 0.0);

			while (!glfwWindowShouldClose(L_Global::Variables.window))
			{
				///////////////////////////////////////////////////////////////////////////
				currentTime = std::chrono::high_resolution_clock::now();
				auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
				lastTime = currentTime;
				double deltaTime = deltaTimeNanoseconds.count()/1000000000.0 * timeConstant;
				///////////////////////////////////////////////////////////////////////////
				glfwPollEvents();
				Input::InputHandler::ProcessEvents(&L_Global::Variables.keyIn, &L_Global::Variables.mouseIn, true);
				///////////////////////////////////////////////////////////////////////////
				L_RenderingEngine::Begin();
				///////////////////////////////////////////////////////////////////////////
				//PhysicsEngine::Update(deltaTime);
				///////////////////////////////////////////////////////////////////////////
				if ((L_Global::Variables.keyIn.leftControlHeld && L_Global::Variables.keyIn.fHeld) || (L_Global::Variables.keyIn.leftControlPressed && L_Global::Variables.keyIn.fPressed)) {
					glfwSetWindowMonitor(L_Global::Variables.window, glfwGetPrimaryMonitor(), 0, 0, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, GLFW_DONT_CARE);
					//glfwSetWindowMonitor(window, nullptr, 0, 0, Global::Variables.currentWidth, Global::Variables.currentHeight, GLFW_DONT_CARE);
				}
				else if ((L_Global::Variables.keyIn.leftControlHeld && L_Global::Variables.keyIn.qHeld) || (L_Global::Variables.keyIn.leftControlPressed && L_Global::Variables.keyIn.qPressed)) {
					glfwSetWindowShouldClose(L_Global::Variables.window, GLFW_TRUE);
				}
				else if ((L_Global::Variables.keyIn.leftControlHeld && L_Global::Variables.keyIn.sHeld) || (L_Global::Variables.keyIn.leftControlPressed && L_Global::Variables.keyIn.sPressed) || (L_Global::Variables.keyIn.leftControlHeld && L_Global::Variables.keyIn.sPressed) || (L_Global::Variables.keyIn.leftControlPressed && L_Global::Variables.keyIn.sHeld)) {
					L_Global::Variables.currentScene.Save("Resources/other/", "level.lvl");
				}
				if (L_Global::Variables.keyIn.leftControlHeld && L_Global::Variables.keyIn.rightControlHeld) {
					shouldLaunchSimulation = true;
				}
				///////////////////////////////////////////////////////////////////////////
				if (EditorEnabled) {
					L_LevelEditor::L_LevelEditorControl::Control(currentEditorType, currentMode, selectedObject, deltaTime);
				}
				///////////////////////////////////////////////////////////////////////////
				L_Global::Variables.activeCamera->ChangeMovementSpeed(L_Global::Variables.movementSpeed);
				L_Global::Variables.currentScene.Submit(L_Global::Variables.currentRenderer, L_Global::Variables.activeCamera);
				///////////////////////////////////////////////////////////////////////////
				L_Global::Variables.currentRenderer->SimpleFlush(L_Global::Variables.activeCamera, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, L_Global::Variables.FOV, L_Global::Variables.currentScene.lightsOnScene.at(0));
				///////////////////////////////////////////////////////////////////////////
				L_RenderingEngine::Render(EnableWireframe, GUIEnabled, currentEditorType, currentMode, selectedObject, timeConstant);
				///////////////////////////////////////////////////////////////////////////
				Input::InputHandler::Flush(&L_Global::Variables.keyIn, &L_Global::Variables.mouseIn);
				///////////////////////////////////////////////////////////////////////////
				L_RenderingEngine::End();
				///////////////////////////////////////////////////////////////////////////
				if (shouldLaunchSimulation) {
					L_PhysicsSimulator::LaunchSimulation(&L_Global::Variables.currentScene, timeConstant);
					shouldLaunchSimulation = false;
				}
			}
			L_RenderingEngine::Cleanup();
		}
		L_Global::Variables.currentScene.Save("Resources/other/", "level.lvl");
		L_Global::Variables.config.WriteConfig("Resources/other/", "config.cfg");
		return true;
	}

	void AtlasEngine::Cleanup()
	{
		L_GUI::Terminate();
		glfwTerminate();
	}
}