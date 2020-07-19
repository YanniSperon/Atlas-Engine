#include "Light.h"

Atlas::Light::Light()
{
}

Atlas::Light::~Light()
{
}

void Atlas::Light::Update(float deltaTime)
{
}

void* Atlas::Light::GetReferencingNode()
{
    return referencingNode;
}

void Atlas::Light::SetReferencingNode(void* node)
{
    referencingNode = node;
}
