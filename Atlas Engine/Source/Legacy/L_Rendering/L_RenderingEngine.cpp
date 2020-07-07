#include "L_RenderingEngine.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Legacy/L_System/L_Callbacks.h"
#include "Legacy/L_Rendering/L_Scene/L_SimpleRenderer.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_Rendering/L_FX/L_PostProcessor.h"
#include "Legacy/L_System/L_System.h"
#include "Shared/S_Input/S_InputHandler.h"
#include "Legacy/L_Rendering/L_GUI/L_GUI.h"

namespace L_Atlas {

	void L_RenderingEngine::Initialize()
	{
		L_PostProcessor::PrepareForInitialization(L_MSAA(false, 0));

		L_System::Log("Vendor: " + std::string((char*)glGetString(GL_VENDOR)));
		L_System::Log("Model: " + std::string((char*)glGetString(GL_RENDERER)));
		L_System::Log("Version: " + std::string((char*)glGetString(GL_VERSION)));

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(L_Callbacks::openglCallbackFunction, NULL);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

		L_Global::Variables.currentRenderer = new L_SimpleRenderer();

		L_PostProcessor::Initialize("Resources/shaders/NoPostFX.shader");
		L_PostProcessor::ChangeEffect("Resources/shaders/BlurPostFX.shader");
		L_PostProcessor::ChangeEffect("Resources/shaders/FXAAPostFX.shader");
		L_PostProcessor::ChangeEffect("Resources/shaders/GreyscalePostFX.shader");
		L_PostProcessor::ChangeEffect("Resources/shaders/InvertPostFX.shader");
		L_PostProcessor::ChangeEffect("Resources/shaders/SharpenPostFX.shader");
		L_PostProcessor::ChangeEffect("Resources/shaders/NoPostFX.shader");

		L_GUI::Initialize(L_Global::Variables.window);

		//Font arial24pt = Font("Resources/fonts/arial/", "arial.ttf", 24);
		//Font timesnewroman32pt = Font("Resources/fonts/times new roman/", "times.ttf", 32);
		//GLuint leftEyeFrameBuffer;
		//glGenFramebuffers(1, &leftEyeFrameBuffer);
		//GLuint rightEyeFrameBuffer;
		//glGenFramebuffers(1, &rightEyeFrameBuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//GLuint leftEyeFrameBuffer;
		//glGenFramebuffers(1, &leftEyeFrameBuffer);
		//GLuint rightEyeFrameBuffer;
		//glGenFramebuffers(1, &rightEyeFrameBuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void L_RenderingEngine::Begin()
	{
		L_PostProcessor::PrepareForRendering();
	}

	void L_RenderingEngine::BeginPhysicsSimulator()
	{
		L_PostProcessor::PrepareForRenderingPhysicsSimulation();
	}

	void L_RenderingEngine::Render(bool& EnableWireframe, bool& EnableGUI, L_LevelEditor::L_EditorType& currentEditorType, L_LevelEditor::L_Mode& currentMode, unsigned int& selectedObject)
	{
		if (EnableWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//PhysicsEngine::DrawDebug();
			L_PostProcessor::Render(L_Global::Variables.currentRenderer);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			//PhysicsEngine::DrawDebug();
			L_PostProcessor::Render(L_Global::Variables.currentRenderer);
		}
		if (EnableGUI) {
			L_GUI::LoadLevelEditorGUI(L_Global::Variables.window, currentEditorType, currentMode, selectedObject, EnableWireframe);
			L_GUI::Draw();
		}
	}

	void L_RenderingEngine::End()
	{
		glfwSwapBuffers(L_Global::Variables.window);
	}

	void L_RenderingEngine::Cleanup()
	{
		L_Mesh::FlushCache();
		L_Object::FlushCache();
		L_PostProcessor::Cleanup();
	}
}