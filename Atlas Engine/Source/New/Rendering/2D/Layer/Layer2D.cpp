#include "Layer2D.h"
#include "New/Scene/2D/Scene/Scene2D.h"

Atlas::Layer2D::Layer2D()
{
	scene = new Scene2D();
}

Atlas::Layer2D::Layer2D(int w, int h, int xPos, int yPos)
	: Layer(w, h, xPos, yPos)
{
	scene = new Scene2D(w, h);
}

Atlas::Layer2D::~Layer2D()
{

}
