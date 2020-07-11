#include "Scene2D.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"

Atlas::Scene2D::Scene2D()
	: Scene(), rootNode(new Node2D())
{

}

Atlas::Scene2D::Scene2D(int initialWidth, int initialHeight)
	: Scene(initialWidth, initialHeight), rootNode(new Node2D())
{
}

Atlas::Scene2D::~Scene2D()
{
	delete rootNode;
}

void Atlas::Scene2D::Update(float deltaTime)
{
	if (!GetIsPaused()) {
		rootNode->Update(deltaTime);
	}
}

void Atlas::Scene2D::Begin()
{
	Renderer::ClearFramebuffer(GetBackgroundColor());
}

void Atlas::Scene2D::Draw(Renderer* renderer)
{
	rootNode->Draw(renderer, glm::mat4(1.0f));
	renderer->Flush2D(glm::ortho(0.0f, (float)GetWidth(), 0.0f, (float)GetHeight()));
}

void Atlas::Scene2D::End()
{
	Renderer::SwapFramebuffer();
}

Atlas::Node2D* Atlas::Scene2D::GetRootNode()
{
	return rootNode;
}

Atlas::Node2D* Atlas::Scene2D::CreateChildNode()
{
	return new Node2D(rootNode);
}

void Atlas::Scene2D::AddNode(Node2D* node)
{
	rootNode->AddChildNode(node);
	node->SetParent(rootNode);
}

Atlas::Node2D* Atlas::Scene2D::GetNodeByName(const std::string& nodeName)
{
	return rootNode->SearchChildrenForNode(nodeName);
}

void Atlas::Scene2D::SetRootNode(Node2D* newNode)
{
	rootNode = newNode;
}