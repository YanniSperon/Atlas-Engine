#include "FramebufferObject.h"
#include "Global.h"
#include "MeshGenerator.h"

Atlas::FramebufferObject::FramebufferObject()
	: object(MeshGenerator::CreateScreenSizedSquare(), ), fbo(0), width(Global::Variables.screenWidth), height(Global::Variables.screenHeight), xPos(0), yPos(0)
{

}

Atlas::FramebufferObject::FramebufferObject(int w, int h, int x, int y)
	: object(), fbo(0), width(Global::Variables.screenWidth), height(Global::Variables.screenHeight), xPos(0), yPos(0)
{

}

void Atlas::FramebufferObject::Resize(int w, int h)
{
}

void Atlas::FramebufferObject::Move(int x, int y)
{
}

void Atlas::FramebufferObject::Bind()
{
}
