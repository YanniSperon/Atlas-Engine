#include "Layer3D.h"

Atlas::Layer3D::Layer3D()
{
	scene = new Scene3D();
}

Atlas::Layer3D::Layer3D(int w, int h, int xPos, int yPos)
{
	scene = new Scene3D(w, h);
}

Atlas::Layer3D::~Layer3D()
{

}
