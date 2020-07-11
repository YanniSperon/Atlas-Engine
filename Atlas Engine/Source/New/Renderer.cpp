#include "Renderer.h"
#include "Global.h"

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
	renderQueue3D = std::deque<Renderable3D>();
	renderQueue2D = std::deque<Renderable2D>();
	renderQueueText = std::deque<RenderableText>();
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

void Atlas::Renderer::AddRenderable3D(const Renderable3D& renderable)
{
	renderQueue3D.push_back(renderable);
}

void Atlas::Renderer::AddRenderable2D(const Renderable2D& renderable)
{
	renderQueue2D.push_back(renderable);
}

void Atlas::Renderer::AddRenderableText(const RenderableText& renderable)
{
	renderQueueText.push_back(renderable);
}

void Atlas::Renderer::Flush2D(glm::mat4 orthoMatrix)
{
	/*
	MAYBE DO
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	*/
	while (!renderQueue2D.empty()) {
		Renderable2D tempRenderable = renderQueue2D.front();
		tempRenderable.GetObject()->Draw(tempRenderable.GetTransformMatrix(), orthoMatrix);
		renderQueue2D.pop_front();
	}
}

void Atlas::Renderer::Flush3D(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	while (!renderQueue3D.empty()) {
		Renderable3D tempRenderable = renderQueue3D.front();
		tempRenderable.GetObject()->Draw(tempRenderable.GetTransformMatrix(), viewMatrix, projectionMatrix);
		renderQueue3D.pop_front();
	}
}
