#include "Light.h"

Atlas::Light::Light()
    : referencingNode(nullptr)
{

}

Atlas::Light::Light(const Light& light2)
    : referencingNode(light2.referencingNode)
{

}

Atlas::Light::~Light()
{

}

void Atlas::Light::Update(float deltaTime)
{

}

Atlas::Node* Atlas::Light::GetReferencingNode()
{
    return referencingNode;
}

void Atlas::Light::SetReferencingNode(Node* node)
{
    referencingNode = node;
}
