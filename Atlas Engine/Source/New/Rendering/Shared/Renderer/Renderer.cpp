#include "Renderer.h"
#include "New/System/Global/Global.h"

void Atlas::Renderer::ClearFramebuffer(glm::vec4 clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Atlas::Renderer::SwapFramebuffer()
{
	glfwSwapBuffers(Global::Variables.window);
}

Atlas::Renderer::Renderer()
{
	renderQueue3D = std::deque<Object3D*>();
	renderQueue2D = std::deque<Object2D*>();
	renderQueueText = std::deque<Text*>();
}

Atlas::Renderer::~Renderer()
{
	while (!renderQueue3D.empty()) {
		renderQueue3D.pop_front();
	}
	while (!renderQueue2D.empty()) {
		renderQueue2D.pop_front();
	}
	while (!renderQueueText.empty()) {
		renderQueueText.pop_front();
	}
}

void Atlas::Renderer::AddObject3D(Object3D* obj)
{
	renderQueue3D.push_back(obj);
}

void Atlas::Renderer::AddObject2D(Object2D* obj)
{
	renderQueue2D.push_back(obj);
}

void Atlas::Renderer::AddText(Text* txt)
{
	renderQueueText.push_back(txt);
}

void Atlas::Renderer::Flush2D(glm::mat4 orthoMatrix)
{
	/*
	MAYBE DO
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	*/
	while (!renderQueue2D.empty()) {
		renderQueue2D.front()->Draw(orthoMatrix);
		renderQueue2D.pop_front();
	}
}

void Atlas::Renderer::Flush3D(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	while (!renderQueue3D.empty()) {
		renderQueue3D.front()->Draw(viewMatrix, projectionMatrix);
		renderQueue3D.pop_front();
	}
}
