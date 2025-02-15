#include "Scene3D.h"

Atlas::Scene3D::Scene3D()
	: Scene(), rootNode(new Node3D()), activeCameraNode(nullptr)
{

}

Atlas::Scene3D::Scene3D(int initialWidth, int initialHeight)
	: Scene(initialWidth, initialHeight), rootNode(new Node3D()), activeCameraNode(nullptr)
{
}

Atlas::Scene3D::~Scene3D()
{
	delete rootNode;
}

void Atlas::Scene3D::Update(float deltaTime)
{
	activeCameraNode->GetCamera()->SetWidth(GetWidth());
	activeCameraNode->GetCamera()->SetHeight(GetHeight());
	if (!GetIsPaused()) {
		activeCameraNode->ControlCamera(0.2f, 10.0f, deltaTime);
		rootNode->Update(deltaTime);
	}
}

void Atlas::Scene3D::Begin()
{
	Renderer::ClearFramebuffer(GetBackgroundColor());
}

void Atlas::Scene3D::Draw(Renderer* renderer)
{
	if (activeCameraNode) {
		rootNode->Draw(renderer, glm::mat4(1.0f), glm::vec3(0.0f));
		renderer->Flush3D(activeCameraNode->GetCameraViewMatrix(), activeCameraNode->GetCameraProjectionMatrix());
	}
}

void Atlas::Scene3D::End()
{
	Renderer::SwapFramebuffer();
}

Atlas::Node3D* Atlas::Scene3D::GetRootNode()
{
	return rootNode;
}

Atlas::Node3D* Atlas::Scene3D::CreateChildNode()
{
	return new Node3D(rootNode);
}

void Atlas::Scene3D::AddNode(Node3D* node)
{
	rootNode->AddChildNode(node);
	node->SetParent(rootNode);
}

Atlas::Node3D* Atlas::Scene3D::GetNodeByName(const std::string& nodeName)
{
	return rootNode->SearchChildrenForNode(nodeName);
}

void Atlas::Scene3D::SetRootNode(Node3D* newNode)
{
	rootNode = newNode;
}

void Atlas::Scene3D::SetActiveCamera(Node3D* newCamera)
{
	activeCameraNode = newCamera;
}