#include "Layer.h"
#include "Global.h"

Atlas::Layer::Layer()
	: width(Global::Variables.screenWidth), height(Global::Variables.screenHeight), x(0), y(0), scene(nullptr), layerType(E_LayerType::NONE)
{

}

Atlas::Layer::Layer(E_LayerType type, int w, int h, int xPos, int yPos)
	: width(w), height(h), x(xPos), y(yPos), layerType(type)
{
	switch (type)
	{
	case Atlas::E_LayerType::NONE:
		scene = nullptr;
		break;
	case Atlas::E_LayerType::TWODIMENSIONAL:
		scene = nullptr;
		break;
	case Atlas::E_LayerType::THREEDIMENSIONAL:
		scene = new Scene3D(w, h);
		break;
	default:
		scene = nullptr;
		break;
	}
}

Atlas::Layer::~Layer()
{

}

void Atlas::Layer::Draw(Renderer* renderer)
{
	if (scene) {
		scene->Begin();
		scene->Draw(renderer);
		scene->End();
	}
}
