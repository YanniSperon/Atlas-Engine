#include "L_PostProcessor.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Game/L_Player.h"
#include "Legacy/L_Global/L_Global.h"
#include <algorithm>

namespace L_Atlas {

	static L_Object2D* quadForRenderingFX;
	static unsigned int postProcessingFramebuffer;
	static unsigned int textureColorbuffer;
	static unsigned int rbo;
	static unsigned int intermediateFramebuffer;
	static unsigned int screenTexture;
	static L_MSAA multisampling;

	void L_PostProcessor::PrepareForInitialization(L_MSAA multiSampleAntiAliasing)
	{
		multisampling = multiSampleAntiAliasing;
		if (multisampling.enabled && multisampling.value == 0) {
			multisampling.enabled = false;
		}
		if (multisampling.enabled) {
			glfwWindowHint(GLFW_SAMPLES, multisampling.value);
		}
	}

	void L_PostProcessor::Initialize(std::string postProcessingShaderAddress)
	{
		if (multisampling.enabled) {
			glEnable(GL_MULTISAMPLE);

			glGenFramebuffers(1, &postProcessingFramebuffer);
			glGenTextures(1, &textureColorbuffer);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorbuffer);
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, multisampling.value , GL_RGB, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, GL_TRUE);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisampling.value, GL_DEPTH24_STENCIL8, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight);

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFramebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorbuffer, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				L_System::Err("Framebuffer incomplete!");
			}

			glGenFramebuffers(1, &intermediateFramebuffer);

			glGenTextures(1, &screenTexture);
			glBindTexture(GL_TEXTURE_2D, screenTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				L_System::Err("Framebuffer incomplete!");
			}
		}
		else {
			glGenFramebuffers(1, &postProcessingFramebuffer);
			glGenTextures(1, &textureColorbuffer);
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight);

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFramebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				L_System::Err("Framebuffer incomplete!");
			}
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		unsigned int shaderID = 0;

		if (L_Global::Variables.shaderCache.find(postProcessingShaderAddress) != L_Global::Variables.shaderCache.end()) {
			shaderID = L_Global::Variables.shaderCache[postProcessingShaderAddress]->GetShaderID();
		}
		else {
			std::string file = postProcessingShaderAddress;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string shadrDirectory = pathtemp.directory;
			std::string shadrName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedPostProcessingShaderCache[shadrName] = physicalLocation;

			L_Global::Variables.shaderCache[shadrDirectory + shadrName] = new L_Shader(shadrDirectory + shadrName);
			shaderID = L_Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		}
		if (multisampling.enabled) {
			quadForRenderingFX = new L_Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(L_Global::Variables.currentWidth, L_Global::Variables.currentHeight), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), intermediateFramebuffer, shaderID, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		}
		else {
			quadForRenderingFX = new L_Object2D(glm::vec2(0.0f, 0.0f), glm::vec2(L_Global::Variables.currentWidth, L_Global::Variables.currentHeight), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), textureColorbuffer, shaderID, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		}
	}

	void L_PostProcessor::PrepareForRendering()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFramebuffer);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void L_PostProcessor::PrepareForRenderingPhysicsSimulation()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFramebuffer);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void L_PostProcessor::Render(L_Renderer* renderer)
	{
		if (multisampling.enabled) {
			glBindFramebuffer(GL_READ_FRAMEBUFFER, postProcessingFramebuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
			glBlitFramebuffer(0, 0, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, 0, 0, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
			glDisable(GL_DEPTH_TEST);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(L_Global::Variables.activeCamera, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, L_Global::Variables.FOV, L_Global::Variables.currentScene.lightsOnScene.at(0));
		}
		else {
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(L_Global::Variables.activeCamera, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, L_Global::Variables.FOV, L_Global::Variables.currentScene.lightsOnScene.at(0));
		}
	}

	void L_PostProcessor::RenderPhysicsRenderer(L_PhysicsRenderer* renderer, L_PhysicsScene* Scene)
	{
		if (multisampling.enabled) {
			glBindFramebuffer(GL_READ_FRAMEBUFFER, postProcessingFramebuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
			glBlitFramebuffer(0, 0, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, 0, 0, L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
			glDisable(GL_DEPTH_TEST);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(Scene->playersOnScene.at(0), L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, L_Global::Variables.FOV, Scene->physicsL_LightsOnScene.at(0));
		}
		else {
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->Submit2D(quadForRenderingFX);
			renderer->SimpleFlush(Scene->playersOnScene.at(0), L_Global::Variables.currentWidth, L_Global::Variables.currentHeight, L_Global::Variables.FOV, Scene->physicsL_LightsOnScene.at(0));
		}
	}

	void L_PostProcessor::ChangeEffect(std::string newShaderShortenedName)
	{
		unsigned int shaderID = 0;

		if (L_Global::Variables.shaderCache.find(newShaderShortenedName) != L_Global::Variables.shaderCache.end()) {
			shaderID = L_Global::Variables.shaderCache[newShaderShortenedName]->GetShaderID();
		}
		else {
			std::string file = newShaderShortenedName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string shadrDirectory = pathtemp.directory;
			std::string shadrName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedPostProcessingShaderCache[shadrName] = physicalLocation;

			L_Global::Variables.shaderCache[shadrDirectory + shadrName] = new L_Shader(shadrDirectory + shadrName);
			shaderID = L_Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		}

		quadForRenderingFX->SetShader(shaderID);
	}

	void L_PostProcessor::Cleanup()
	{
		delete quadForRenderingFX;
		glDeleteFramebuffers(1, &postProcessingFramebuffer);
		glDeleteTextures(1, &textureColorbuffer);
		glDeleteRenderbuffers(1, &rbo);
		glDeleteFramebuffers(1, &intermediateFramebuffer);
		glDeleteTextures(1, &screenTexture);
	}
}