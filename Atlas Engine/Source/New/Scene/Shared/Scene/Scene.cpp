#include "Scene.h"
#include "New/System/Global/Global.h"

Atlas::Scene::Scene()
	: width(Global::Variables.screenWidth), height(Global::Variables.screenHeight), isPaused(false), backgroundColor(0.0f)
{
}

Atlas::Scene::Scene(int initialWidth, int initialHeight)
	: width(initialWidth), height(initialHeight), isPaused(false), backgroundColor(0.0f)
{

}

Atlas::Scene::~Scene()
{

}

bool Atlas::Scene::GetIsPaused()
{
	return isPaused;
}

glm::vec4 Atlas::Scene::GetBackgroundColor()
{
	return backgroundColor;
}

int Atlas::Scene::GetWidth()
{
	return width;
}

int Atlas::Scene::GetHeight()
{
	return height;
}

void Atlas::Scene::SetIsPaused(bool newValue)
{
	isPaused = newValue;
}

void Atlas::Scene::SetBackgroundColor(glm::vec4 color)
{
	backgroundColor = color;
}

void Atlas::Scene::SetWidth(int newWidth)
{
	width = newWidth;
}

void Atlas::Scene::SetHeight(int newHeight)
{
	height = newHeight;
}

void Atlas::Scene::ToggleIsPaused()
{
	isPaused = !isPaused;
}
