#include "FramebufferObject.h"
#include "New/System/Global/Global.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"

Atlas::FramebufferObject::FramebufferObject()
	: Object2D(MeshGenerator::CreateSquareCustom(glm::vec2(0.0f, 0.0f), glm::vec2(Global::Variables.screenWidth, Global::Variables.screenHeight), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "Resources/shaders/Basic2D.shader", new Texture()), fbo(0), width(Global::Variables.screenWidth), height(Global::Variables.screenHeight)
{

}

Atlas::FramebufferObject::FramebufferObject(int w, int h, int x, int y)
	: Object2D(), fbo(0), width(Global::Variables.screenWidth), height(Global::Variables.screenHeight)
{

}

void Atlas::FramebufferObject::Resize(int w, int h)
{
	mesh->DeleteMesh();
}

void Atlas::FramebufferObject::Bind()
{
}
