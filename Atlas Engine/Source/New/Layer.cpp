#include "Layer.h"
#include "Global.h"

Atlas::Layer::Layer()
	: width(Global::Variables.screenWidth), height(Global::Variables.screenHeight), x(0), y(0), scene(nullptr)
{

}

Atlas::Layer::Layer(int w, int h, int xPos, int yPos)
	: width(w), height(h), x(xPos), y(yPos), scene(nullptr)
{

}

Atlas::Layer::~Layer()
{

}

void Atlas::Layer::Draw(Renderer* renderer)
{
	if (scene) {
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		scene->Begin();
		scene->Draw(renderer);
		scene->End();
	}
}

void Atlas::Layer::Update(float deltaTime)
{
	scene->Update(deltaTime);
}

void Atlas::Layer::SetScene(Scene* newScene)
{
	scene = newScene;
}

void Atlas::Layer::SetSize(int w, int h)
{
	width = w;
	height = h;

}

Atlas::Scene* Atlas::Layer::GetScene()
{
	return scene;
}
