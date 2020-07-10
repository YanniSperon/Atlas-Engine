#include "Scene3D.h"

Atlas::Scene3D::Scene3D()
	: Scene(), rootNode(new Node3D())
{

}

Atlas::Scene3D::Scene3D(int initialWidth, int initialHeight)
	: Scene(initialWidth, initialHeight), rootNode(new Node3D())
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

Atlas::Node3D* Atlas::Scene3D::GetRootNode()
{
	return rootNode;
}

void Atlas::Scene3D::Draw(Renderer* renderer)
{
	if (activeCameraNode) {
		Renderer::ClearFramebuffer(GetBackgroundColor());
		rootNode->Draw(renderer, glm::mat4());
		renderer->Flush(activeCameraNode->GetCameraViewMatrix(), activeCameraNode->GetCameraProjectionMatrix());
		Renderer::SwapFramebuffer();
	}
}

Atlas::Node3D* Atlas::Scene3D::CreateChildNode()
{
	Node3D* newNode = new Node3D(rootNode);
	return newNode;
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