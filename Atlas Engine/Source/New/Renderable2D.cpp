#include "Renderable2D.h"

Atlas::Renderable2D::Renderable2D()
	: objectBeingRendered(nullptr), finalTranslation(0.0f), finalRotation(0.0f), finalScale(0.0f)
{
}

Atlas::Renderable2D::~Renderable2D()
{
}

Atlas::Object2D* Atlas::Renderable2D::GetObject()
{
	return objectBeingRendered;
}
