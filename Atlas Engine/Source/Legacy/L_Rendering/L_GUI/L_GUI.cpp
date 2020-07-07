#include "L_GUI.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_IO.h"
#include "L_Window.h"
#include "Legacy/L_System/L_System.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#include "Shared/S_Vendor/S_IMGUI/imgui.h"
#include "Shared/S_Vendor/S_IMGUI/imgui_impl_glfw_gl3.h"
#include "Shared/S_Vendor/S_IMGUI/imgui_internal.h"

namespace L_Atlas {

	void L_GUI::Initialize(GLFWwindow* window)
	{
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.IniFilename = NULL;

		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();
	}

	void L_GUI::LoadLevelEditorGUI(GLFWwindow* window, L_LevelEditor::L_EditorType currentEditorType, L_LevelEditor::L_Mode currentMode, unsigned int& selectedObject, bool& EnableWireframe)
	{
		ImGui_ImplGlfwGL3_NewFrame();
		static bool EnableDebug = true;
		static bool EnableSpawnMenu = true;
		static bool EnableConsole = true;
		static bool EnableInfoPage = true;
		static bool EnableFileManager = true;
		static bool EnablePhysicsManager = true;
		static bool ShouldToggleVSync = false;
		static bool GUIEnabled = true;
		static bool EnableObjectInfoPage = true;
		static bool EnablePostProcessingManager = true;
		if (L_Global::Variables.keyIn.leftAltPressed) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			L_Global::Variables.enableMouseMove = false;
		}
		if (L_Global::Variables.keyIn.leftAltReleased) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			L_Global::Variables.enableMouseMove = true;
			glfwSetCursorPos(window, L_Global::Variables.mouseX, L_Global::Variables.mouseY);
		}
		if (L_Global::Variables.keyIn.tildePressed) {
			EnableConsole = !EnableConsole;
		}

		{
			ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
			ImGui::SetNextWindowSize(ImVec2((190.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (245.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
			ImGui::Begin("File", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			ImGui::Checkbox("Enable Debug Options##debugControl", &EnableDebug);
			ImGui::Checkbox("Enable File Manager##filemanager", &EnableFileManager);
			ImGui::Checkbox("Enable Spawn Menu##spawnControl", &EnableSpawnMenu);
			ImGui::Checkbox("Enable Info Page##infoControl", &EnableInfoPage);
			ImGui::Checkbox("Enable Object Settings##objectSettingsControl", &EnableObjectInfoPage);
			ImGui::Checkbox("Enable PSFX Manager##psfxmanager", &EnablePostProcessingManager);
			ImGui::Checkbox("Enable Physics Manager##physicstoggle", &EnablePhysicsManager);
			ImGui::Separator();
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Save##saveButton", ImVec2(ImGui::GetWindowSize().x * 0.5f, 0.0f))) {
				L_Global::Variables.currentScene.Save("Resources/L_Other/", "level.lvl");
			}
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Close##closeButton", ImVec2(ImGui::GetWindowSize().x * 0.5f, 0.0f))) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			ImGui::End();
		}

		if (EnableDebug) {
			L_Window::DrawDebug(EnableConsole, EnableWireframe);
		}

		if (EnableSpawnMenu) {
			L_Window::DrawSpawnWindow(L_Global::Variables.currentScene.objectsOnScene, selectedObject);
		}

		if (EnableInfoPage) {
			L_Window::DrawInfoWindow(currentEditorType, currentMode);
		}

		if (EnableObjectInfoPage) {
			if (L_Global::Variables.currentScene.objectsOnScene.size() > 0 && selectedObject < L_Global::Variables.currentScene.objectsOnScene.size() && selectedObject >= 0) {
				L_Window::DrawObjectSettingsWindow(L_Global::Variables.currentScene.objectsOnScene[selectedObject]);
			}
		}

		if (EnableConsole) {
			L_System::DrawConsole();
		}

		if (EnableFileManager) {
			L_Window::DrawFileManager(window);
		}

		if (EnablePostProcessingManager) {
			L_Window::DrawPostProcessingManager(window);
		}

		//if (EnablePhysicsManager) {
		//	Window::DrawPhysicsManager();
		//}
	}

	void L_GUI::LoadPhysicsSimulatorGUI()
	{
		ImGui_ImplGlfwGL3_NewFrame();
		L_Window::DrawFPSCounter();
		L_System::DrawConsole();
	}

	void L_GUI::Draw()
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void L_GUI::Terminate()
	{
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}
}
