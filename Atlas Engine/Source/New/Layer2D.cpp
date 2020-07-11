#include "Layer2D.h"
#include "Scene2D.h"

Atlas::Layer2D::Layer2D()
{
	SetScene(new Scene2D());
}

Atlas::Layer2D::Layer2D(int w, int h, int xPos, int yPos)
	: Layer(w, h, xPos, yPos)
{
	SetScene(new Scene2D(w, h));
}

Atlas::Layer2D::~Layer2D()
{

}
