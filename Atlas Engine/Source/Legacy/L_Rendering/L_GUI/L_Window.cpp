#include "L_Window.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "Shared/S_Vendor/S_IMGUI/imgui.h"
#include "Shared/S_Vendor/S_IMGUI/imgui_impl_glfw_gl3.h"
#include "Shared/S_Vendor/S_IMGUI/imgui_internal.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_Rendering/L_Scene/L_Loader.h"
#include "Legacy/L_Rendering/L_Primitives/L_ShapeGenerator.h"
#include "Legacy/L_Rendering/L_FX/L_PostProcessor.h"
#include "Legacy/L_Other/L_Convert.h"
#include <algorithm>

namespace L_Atlas {

	static int AddValueFile(std::string directory, std::string file, int value) {
		if (value == 0) {
			if (L_System::DoesFileExist(directory + file)) {
				return AddValueFile(directory, file, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (L_System::DoesFileExist(directory + std::to_string(value) + file)) {
				return AddValueFile(directory, file, value + 1);
			}
			else {
				return value;
			}
		}
	}

	static int AddValueL_Mesh(std::string meshName, int value) {
		if (value == 0) {
			if (L_Global::Variables.loadedL_MeshCache.find(meshName) != L_Global::Variables.loadedL_MeshCache.end()) {
				return AddValueL_Mesh(meshName, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (L_Global::Variables.loadedL_MeshCache.find(meshName + std::to_string(value)) != L_Global::Variables.loadedL_MeshCache.end()) {
				return AddValueL_Mesh(meshName, value + 1);
			}
			else {
				return value;
			}
		}
	}
	
	static int AddValueTexture(std::string meshName, int value) {
		if (value == 0) {
			if (L_Global::Variables.loadedTextureCache.find(meshName) != L_Global::Variables.loadedTextureCache.end()) {
				return AddValueTexture(meshName, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (L_Global::Variables.loadedTextureCache.find(meshName + std::to_string(value)) != L_Global::Variables.loadedTextureCache.end()) {
				return AddValueTexture(meshName, value + 1);
			}
			else {
				return value;
			}
		}
	}
	
	static int AddValueShader(std::string meshName, int value) {
		if (value == 0) {
			if (L_Global::Variables.loadedShaderCache.find(meshName) != L_Global::Variables.loadedShaderCache.end()) {
				return AddValueShader(meshName, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (L_Global::Variables.loadedShaderCache.find(meshName + std::to_string(value)) != L_Global::Variables.loadedShaderCache.end()) {
				return AddValueShader(meshName, value + 1);
			}
			else {
				return value;
			}
		}
	}

	void L_Window::DrawInfoWindow(L_LevelEditor::L_EditorType& currentEditorType, L_LevelEditor::L_Mode& currentMode)
	{
		ImGui::SetNextWindowPos(ImVec2((812.5f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((295.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (70.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Current Editor Type: ");
		ImGui::SameLine();
		if (currentEditorType == L_LevelEditor::L_EditorType::light) {
			ImGui::Text("Light");
		}
		else if (currentEditorType == L_LevelEditor::L_EditorType::Scene) {
			ImGui::Text("Scene");
		}
		ImGui::Separator();
		ImGui::Text("Current Editing Mode: ");
		ImGui::SameLine();
		if (currentMode == L_LevelEditor::L_Mode::cam) {
			ImGui::Text("Camera");
		}
		else if (currentMode == L_LevelEditor::L_Mode::rotate) {
			ImGui::Text("Rotate");
		}
		else if (currentMode == L_LevelEditor::L_Mode::scale) {
			ImGui::Text("Scale");
		}
		else if (currentMode == L_LevelEditor::L_Mode::texture) {
			ImGui::Text("Texture");
		}
		else if (currentMode == L_LevelEditor::L_Mode::translate) {
			ImGui::Text("Translate");
		}
		ImGui::End();
	}
	
	void L_Window::DrawDebug(bool& EnableConsole, bool& Wireframe)
	{
		ImGui::SetNextWindowPos(ImVec2((230.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((240.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (100.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.12f).x);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
		ImGui::Checkbox("Enable Console##consoleControl", &EnableConsole);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Toggle display mode##wireframetoggler", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			if (Wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				Wireframe = false;
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				Wireframe = true;
			}
		}
		ImGui::End();
	}

	void L_Window::DrawFPSCounter()
	{
		ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((240.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (50.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.12f).x);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void L_Window::DrawFileManager(GLFWwindow* window)
	{
		ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (285.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((190.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (100.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("File Manager", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new mesh##loadmeshbutton1", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = L_System::FileOpenDialog("Select a mesh to load", "OBJECT File\0*.obj\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				L_System::Warn("Loading mesh \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string meshDir = "";
				std::string meshName = "";
				if (lastSlashPos != std::string::npos) {
					meshDir = file.substr(0, lastSlashPos + 1);
					meshName = file.substr(lastSlashPos + 1);
				}
				else {
					meshName = file;
				}
				physicalLocation = meshDir + meshName;
				if (L_System::IsFilePathInWorkingDirectory(file)) {
					file = L_System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					meshDir = "";
					meshName = "";
					if (lastSlashPos != std::string::npos) {
						meshDir = file.substr(0, lastSlashPos + 1);
						meshName = file.substr(lastSlashPos + 1);
					}
					else {
						meshName = file;
					}
					physicalLocation = meshDir + meshName;
				}
				else {
					std::string val = std::to_string(AddValueFile("Resources/models/", meshName, 0));
					if (val == "0") {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/models/" + meshName);
					}
					else {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/models/" + val + meshName);
					}
					L_System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = L_System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					meshDir = "";
					meshName = "";
					if (lastSlashPos != std::string::npos) {
						meshDir = physicalLocation.substr(0, lastSlashPos + 1);
						meshName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						meshName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueL_Mesh(meshName, 0));
				if (val == "0") {
					L_Global::Variables.loadedL_MeshCache[meshName] = (physicalLocation);
				}
				else {
					L_Global::Variables.loadedL_MeshCache[val + meshName] = (physicalLocation);
				}
				try {
					if (L_Global::Variables.meshCache.find(meshDir + meshName) == L_Global::Variables.meshCache.end()) {
						L_Global::Variables.meshCache[meshDir + meshName] = L_ShapeGenerator::loadTexturedShape(meshDir, meshName);
					}
				}
				catch (const std::exception & e) {
					try {
						if (L_Global::Variables.meshCache.find(meshDir + meshName) == L_Global::Variables.meshCache.end()) {
							L_Global::Variables.meshCache[meshDir + meshName] = L_ShapeGenerator::loadShape(physicalLocation);
						}
					}
					catch (const std::exception & e) {
						L_System::Err("Unrecognized file type, must be wavefront .obj file following the specified format");
					}
				}
				L_System::Warn("L_Mesh \"" + file + "\" loaded");
			}
		}
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new texture##loadtexturebutton1", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = L_System::FileOpenDialog("Select a texture to load", "Portable Network Graphics\0*.png\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				L_System::Warn("Loading texture \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string textureDir = "";
				std::string textureName = "";
				if (lastSlashPos != std::string::npos) {
					textureDir = file.substr(0, lastSlashPos + 1);
					textureName = file.substr(lastSlashPos + 1);
				}
				else {
					textureName = file;
				}
				physicalLocation = textureDir + textureName;
				if (L_System::IsFilePathInWorkingDirectory(file)) {
					file = L_System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					textureDir = "";
					textureName = "";
					if (lastSlashPos != std::string::npos) {
						textureDir = file.substr(0, lastSlashPos + 1);
						textureName = file.substr(lastSlashPos + 1);
					}
					else {
						textureName = file;
					}
					physicalLocation = textureDir + textureName;
				}
				else {
					std::string val = std::to_string(AddValueFile("Resources/images/textures/", textureName, 0));
					if (val == "0") {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/images/textures/" + textureName);
					}
					else {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/images/textures/" + val + textureName);
					}
					L_System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = L_System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					textureDir = "";
					textureName = "";
					if (lastSlashPos != std::string::npos) {
						textureDir = physicalLocation.substr(0, lastSlashPos + 1);
						textureName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						textureName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueTexture(textureName, 0));
				if (val == "0") {
					L_Global::Variables.loadedTextureCache[textureName] = physicalLocation;
				}
				else {
					L_Global::Variables.loadedTextureCache[val + textureName] = physicalLocation;
				}
				if (L_Global::Variables.textureCache.find(textureDir + textureName) == L_Global::Variables.textureCache.end()) {
					L_Global::Variables.textureCache[textureDir + textureName] = L_Loader::LoadTexture(physicalLocation, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
				}
				L_System::Warn("Texture \"" + file + "\" loaded");
			}
		}
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new shader##loadshaderbutton1", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = L_System::FileOpenDialog("Select a shader to load", "SHADER File\0*.shader\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				L_System::Warn("Loading shader \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string shaderDir = "";
				std::string shaderName = "";
				if (lastSlashPos != std::string::npos) {
					shaderDir = file.substr(0, lastSlashPos + 1);
					shaderName = file.substr(lastSlashPos + 1);
				}
				else {
					shaderName = file;
				}
				physicalLocation = shaderDir + shaderName;
				if (L_System::IsFilePathInWorkingDirectory(file)) {
					file = L_System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = file.substr(0, lastSlashPos + 1);
						shaderName = file.substr(lastSlashPos + 1);
					}
					else {
						shaderName = file;
					}
					physicalLocation = shaderDir + shaderName;
				}
				else {
					std::string val = std::to_string(AddValueFile("Resources/shaders/", shaderName, 0));
					if (val == "0") {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/shaders/" + shaderName);
					}
					else {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/shaders/" + val + shaderName);
					}
					L_System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = L_System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = physicalLocation.substr(0, lastSlashPos + 1);
						shaderName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						shaderName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueShader(shaderName, 0));
				if (val == "0") {
					L_Global::Variables.loadedShaderCache[shaderName] = physicalLocation;
				}
				else {
					L_Global::Variables.loadedShaderCache[val + shaderName] = physicalLocation;
				}

				if (L_Global::Variables.shaderCache.find(shaderDir + shaderName) == L_Global::Variables.shaderCache.end()) {
					L_Global::Variables.shaderCache[shaderDir + shaderName] = new L_Shader(physicalLocation);
				}
				L_System::Warn("Shader \"" + file + "\" loaded");
			}
		}
		ImGui::End();
	}

	void L_Window::DrawPostProcessingManager(GLFWwindow* window)
	{
		static std::string currentSelectedPSFX = "";
		ImGui::SetNextWindowPos(ImVec2((1605.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (935.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((295.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (125.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("Post-Processing Manager", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		if (ImGui::Button("Load new PSFX shader##loadpsfxshader", ImVec2(ImGui::GetWindowSize().x * 0.75f, 0.0f))) {
			std::string file = L_System::FileOpenDialog("Select a mesh to load", "SHADER File\0*.shader\0", window);
			std::replace(file.begin(), file.end(), '\\', '/');
			if (file != "INVALID") {
				L_System::Warn("Loading shader \"" + file + "\"");
				std::string physicalLocation = "";
				std::size_t lastSlashPos = file.find_last_of("/");
				std::string shaderDir = "";
				std::string shaderName = "";
				if (lastSlashPos != std::string::npos) {
					shaderDir = file.substr(0, lastSlashPos + 1);
					shaderName = file.substr(lastSlashPos + 1);
				}
				else {
					shaderName = file;
				}
				physicalLocation = shaderDir + shaderName;
				if (L_System::IsFilePathInWorkingDirectory(file)) {
					file = L_System::ConvertFilePathToLocal(file);
					lastSlashPos = file.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = file.substr(0, lastSlashPos + 1);
						shaderName = file.substr(lastSlashPos + 1);
					}
					else {
						shaderName = file;
					}
					physicalLocation = shaderDir + shaderName;
				}
				else {
					std::string val = std::to_string(AddValueFile("Resources/shaders/", shaderName, 0));
					if (val == "0") {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/shaders/" + shaderName);
					}
					else {
						physicalLocation = L_System::ConvertFilePathToAbsolute("Resources/shaders/" + val + shaderName);
					}
					L_System::CopyFileAtlas(file, physicalLocation);
					physicalLocation = L_System::ConvertFilePathToLocal(physicalLocation);
					lastSlashPos = physicalLocation.find_last_of("/");
					shaderDir = "";
					shaderName = "";
					if (lastSlashPos != std::string::npos) {
						shaderDir = physicalLocation.substr(0, lastSlashPos + 1);
						shaderName = physicalLocation.substr(lastSlashPos + 1);
					}
					else {
						shaderName = physicalLocation;
					}
				}
				std::string val = std::to_string(AddValueShader(shaderName, 0));
				if (val == "0") {
					L_Global::Variables.loadedPostProcessingShaderCache[shaderName] = physicalLocation;
				}
				else {
					L_Global::Variables.loadedPostProcessingShaderCache[val + shaderName] = physicalLocation;
				}

				if (L_Global::Variables.shaderCache.find(shaderDir + shaderName) == L_Global::Variables.shaderCache.end()) {
					L_Global::Variables.shaderCache[shaderDir + shaderName] = new L_Shader(physicalLocation);
				}
				L_System::Warn("Shader \"" + file + "\" loaded");
			}
		}
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.15f).x);
		ImGui::Text("Current post-processing shader");
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.175f).x);
		if (ImGui::BeginCombo("##psfxcombo", currentSelectedPSFX.c_str()))
		{
			for (auto it : L_Global::Variables.loadedPostProcessingShaderCache) {
				bool is_selected = (currentSelectedPSFX == it.first);
				if (ImGui::Selectable(it.first.c_str(), is_selected)) {
					currentSelectedPSFX = it.first;
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
		if (ImGui::Button("Apply##t1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
			L_PostProcessor::ChangeEffect(L_Global::Variables.loadedPostProcessingShaderCache[currentSelectedPSFX]);
		}
		ImGui::End();
	}

	void L_Window::DrawSpawnWindow(std::vector<L_Object*>& objectsOnScene, unsigned int& selectedObject)
	{
		static glm::vec3 InputRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputScale = glm::vec3(1.0f, 1.0f, 1.0f);
		static glm::vec3 InputAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		//float mass = 1.0f;
		static int InputShininess = 32;
		static std::string currentSelectedL_Mesh = "";
		static std::string currentSelectedTexture = "";
		static std::string currentSelectedShader = "";
		//static bool hasPhysics = true;

		ImGui::SetNextWindowPos(ImVec2((1605.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (20.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((295.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (405.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("Spawn Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.1f).x);
		if (ImGui::BeginCombo("L_Mesh##meshcombo", currentSelectedL_Mesh.c_str()))
		{
			for (auto it : L_Global::Variables.loadedL_MeshCache) {
				bool is_selected = (currentSelectedL_Mesh == it.first);
				if (ImGui::Selectable(it.first.c_str(), is_selected)) {
					currentSelectedL_Mesh = it.first;
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.1f).x);
		if (ImGui::BeginCombo("Texture##texturecombo", currentSelectedTexture.c_str()))
		{
			for (auto it : L_Global::Variables.loadedTextureCache) {
				bool is_selected = (currentSelectedTexture == it.first);
				if (ImGui::Selectable(it.first.c_str(), is_selected)) {
					currentSelectedTexture = it.first;
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.1f).x);
		if (ImGui::BeginCombo("Shader##shadercombo", currentSelectedShader.c_str()))
		{
			for (auto it : L_Global::Variables.loadedShaderCache) {
				bool is_selected = (currentSelectedTexture == it.first);
				if (ImGui::Selectable(it.first.c_str(), is_selected)) {
					currentSelectedShader = it.first;
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::Separator();
		//ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.42f).x);
		//ImGui::Text("Physics");
		//ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.275f).x);
		//ImGui::Checkbox("Enable Physics", &hasPhysics);
		//ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.125f).x);
		//ImGui::InputFloat("Mass##massfloatin", &mass);
		//ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
		ImGui::Text("Position");
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		ImGui::InputFloat3("Rotation##rotfloatin", &InputRotation[0]);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		ImGui::InputFloat3("Translation##transfloatin", &InputTranslation[0]);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		ImGui::InputFloat3("Scale##scalefloatin", &InputScale[0]);
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
		ImGui::Text("Lighting");
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		ImGui::InputFloat3("Ambient##ambientfloatin", &InputAmbient[0]);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		ImGui::InputFloat3("Diffuse##diffusefloatin", &InputDiffuse[0]);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		ImGui::InputFloat3("Specular##specularfloatin", &InputSpecular[0]);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.05f).x);
		ImGui::SliderInt("Shininess##shininessintslider", &InputShininess, 0, 512);
		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
		if (ImGui::Button("Spawn##spawn", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
			if (currentSelectedTexture == "" || currentSelectedL_Mesh == "" || currentSelectedShader == "") {
				L_System::Log("Please select a mesh, texture, and shader");
			}
			else {
				if (L_Global::Variables.loadedL_MeshCache.find(currentSelectedL_Mesh) != L_Global::Variables.loadedL_MeshCache.end() && L_Global::Variables.loadedTextureCache.find(currentSelectedTexture) != L_Global::Variables.loadedTextureCache.end() && L_Global::Variables.loadedShaderCache.find(currentSelectedShader) != L_Global::Variables.loadedShaderCache.end()) {
					L_Filepath meshpath = L_System::SeperateFilepath(L_Global::Variables.loadedL_MeshCache[currentSelectedL_Mesh]);
					L_Filepath texpath = L_System::SeperateFilepath(L_Global::Variables.loadedTextureCache[currentSelectedTexture]);
					L_Filepath shaderpath = L_System::SeperateFilepath(L_Global::Variables.loadedShaderCache[currentSelectedShader]);

					L_System::Log("Spawned object with model \"" + meshpath.directory + meshpath.filename + "\" at (" + std::to_string(InputTranslation.x) + ", " + std::to_string(InputTranslation.y) + ", " + std::to_string(InputTranslation.z) + ")");
					objectsOnScene.push_back(new L_Object(L_Type::normalModel, meshpath.directory, meshpath.filename, texpath.directory, texpath.filename, shaderpath.directory, shaderpath.filename, true, true, L_System::GenerateUniqueID(), InputRotation, InputTranslation, InputScale, L_Material(InputAmbient, InputDiffuse, InputSpecular, ((float)InputShininess))));
					selectedObject = objectsOnScene.size() - 1;
				}
				else {
					L_System::Err("Invalid or corrupted cache files!");
				}
			}
		}
		ImGui::End();
	}
	
	void L_Window::DrawObjectSettingsWindow(L_Object* object)
	{
		static glm::vec3 InputModificationRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputModificationTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		static glm::vec3 InputModificationScale = glm::vec3(1.0f, 1.0f, 1.0f);
		static glm::vec3 InputModificationAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputModificationDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		static glm::vec3 InputModificationSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		static int InputModificationShininess = 32;
		static char* items[] = { "Rendering", "Lighting", "Position" };
		static char* current_item = items[0];
		static std::string currentSelectedTexture = "";
		static std::string currentSelectedShader = "";

		ImGui::SetNextWindowPos(ImVec2((1605.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (445.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((295.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (470.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("Object Settings", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
		if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(items[n], is_selected)) {
					current_item = items[n];
					if (is_selected) {
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
				}
			}
			ImGui::EndCombo();
		}
		
		ImGui::Text("");
		ImGui::Separator();

		if (current_item == "Rendering") {
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
			ImGui::Text("Texture");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			if (ImGui::BeginCombo("##texturecombo", currentSelectedTexture.c_str()))
			{
				for (auto it : L_Global::Variables.loadedTextureCache) {
					bool is_selected = (currentSelectedTexture == it.first);
					if (ImGui::Selectable(it.first.c_str(), is_selected)) {
						currentSelectedTexture = it.first;
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##t1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				L_Filepath texpath = L_System::SeperateFilepath(L_Global::Variables.loadedTextureCache[currentSelectedTexture]);
				object->SetTexture(std::string(texpath.directory), std::string(texpath.filename));
			}
			ImGui::Separator();
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.4f).x);
			ImGui::Text("Shader");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			if (ImGui::BeginCombo("##shadercombo", currentSelectedShader.c_str()))
			{
				for (auto it : L_Global::Variables.loadedShaderCache) {
					bool is_selected = (currentSelectedTexture == it.first);
					if (ImGui::Selectable(it.first.c_str(), is_selected)) {
						currentSelectedShader = it.first;
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##s1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				L_Filepath shaderpath = L_System::SeperateFilepath(L_Global::Variables.loadedShaderCache[currentSelectedShader]);
				object->SetShader(std::string(shaderpath.directory), std::string(shaderpath.filename));
			}
		}
		else if (current_item == "Position") {

			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.38f).x);
			ImGui::Text("Rotation");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			ImGui::InputFloat3("##in1", &InputModificationRotation[0]);
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##in1", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				object->RotateVec3(InputModificationRotation);
			}

			ImGui::Separator();

			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.36f).x);
			ImGui::Text("Translation");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			ImGui::InputFloat3("##in2", &InputModificationTranslation[0]);
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##in2", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				object->TranslateVec3(InputModificationTranslation);
			}

			ImGui::Separator();

			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.41f).x);
			ImGui::Text("Scale");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			ImGui::InputFloat3("##in3", &InputModificationScale[0]);
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##in3", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				object->ScaleVec3(InputModificationScale);
			}
		}
		else if (current_item == "Lighting") {
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
			ImGui::Text("Ambient Reflection");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			ImGui::InputFloat3("##lin2", &InputModificationAmbient[0]);
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##lin2", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				auto temp = object->GetMaterial();
				temp.ambient = InputModificationAmbient;
				object->SetMaterial(temp);
			}

			ImGui::Separator();

			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
			ImGui::Text("Diffuse Reflection");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			ImGui::InputFloat3("##lin3", &InputModificationDiffuse[0]);
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##lin3", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				auto temp = object->GetMaterial();
				temp.diffuse = InputModificationDiffuse;
				object->SetMaterial(temp);
			}

			ImGui::Separator();

			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
			ImGui::Text("Specular Reflection");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			ImGui::InputFloat3("##lin4", &InputModificationSpecular[0]);
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##lin4", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				auto temp = object->GetMaterial();
				temp.ambient = InputModificationSpecular;
				object->SetMaterial(temp);
			}

			ImGui::Separator();

			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.27f).x);
			ImGui::Text("Reflection Shininess");
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.17f).x);
			ImGui::SliderInt("##lin5", &InputModificationShininess, 0, 512);
			ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
			if (ImGui::Button("Apply##lin5", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
				auto temp = object->GetMaterial();
				temp.shininess = InputModificationShininess;
				object->SetMaterial(temp);
			}
		}

		ImGui::End();
	}

	void L_Window::DrawPhysicsManager(double& timeConstant)
	{
		static bool EnablePhysics = true;
		static glm::vec3 gravity = glm::vec3(0.0f, -9.80665, 0.0f);
		static double tempTimeConstant = 1.0;
		L_PhysicsEngine::SetPhysics(EnablePhysics);
		ImGui::SetNextWindowPos(ImVec2((20.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (405.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::SetNextWindowSize(ImVec2((190.0f / 1920.0f) * ((float)L_Global::Variables.currentWidth), (175.0f / 1080.0f) * ((float)L_Global::Variables.currentHeight)));
		ImGui::Begin("Physics Manager", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.3f).x);
		ImGui::Checkbox("Enable Physics", &EnablePhysics);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.1f).x);
		ImGui::InputFloat3("Gravity##gravityfloatin", &gravity[0]);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
		if (ImGui::Button("Apply##applygravitybutton", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
			L_PhysicsEngine::SetGravity(L_Convert::Vector3(gravity));
		}
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.1f).x);
		ImGui::InputDouble("Time Constant##timeconstantdoublein", &timeConstant);
		ImGui::SetCursorPosX((ImGui::GetWindowSize() * 0.25f).x);
		if (ImGui::Button("Apply##applytimeconstantbutton", ImVec2(ImGui::GetWindowSize().x * 0.50f, 0.0f))) {
			timeConstant = tempTimeConstant;
		}
		ImGui::End();
	}
}