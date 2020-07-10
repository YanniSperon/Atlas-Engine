#include "Node2D.h"

Atlas::Node2D::Node2D()
{
	parent = nullptr;
	children = std::vector<Node2D*>();
	translation = glm::vec3(0.0f);
	objectComponent = nullptr;
}

Atlas::Node2D::~Node2D()
{
}

void Atlas::Node2D::Update(float deltaTime)
{
	for (int i = 0; i < children.size(); i++) {
		children.at(i)->Update(deltaTime);
	}
	objectComponent->Update(deltaTime);
	textComponent->Update(deltaTime);
}

void Atlas::Node2D::AddChildNode(Node2D* newChild)
{
	children.push_back(newChild);
}

void Atlas::Node2D::RemoveAndDeleteChildNode(Node2D* child)
{
	for (int i = 0; i < children.size(); i++) {
		if (child == children.at(i)) {
			delete child;
			children.erase(children.begin() + i);
			break;
		}
	}
}

void Atlas::Node2D::SetParent(Node2D* newParent)
{
	parent = newParent;
}

Atlas::Node2D* Atlas::Node2D::GetParentNode()
{
	return parent;
}

std::vector<Atlas::Node2D*> Atlas::Node2D::GetChildren()
{
	return children;
}

Atlas::Object2D* Atlas::Node2D::GetObjectComponent()
{
	return objectComponent;
}

Atlas::Text* Atlas::Node2D::GetTextComponent()
{
	return textComponent;
}
