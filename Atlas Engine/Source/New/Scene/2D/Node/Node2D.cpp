#include "Node2D.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"
#include "New/System/Global/Global.h"

Atlas::Node2D::Node2D()
	: Node(E_NodeType::TWODIMENSIONAL), parent(nullptr), objectComponent(nullptr), textComponent(nullptr), translation(0.0f), rotation(0.0f), scale(1.0f)
{
	SetName("Root Node");
}

Atlas::Node2D::Node2D(const Node2D& node2)
	: Node(E_NodeType::TWODIMENSIONAL), parent(node2.parent), objectComponent(nullptr), textComponent(nullptr), translation(node2.translation), rotation(node2.rotation), scale(node2.scale)
{
	for (int i = 0; i < node2.children.size(); i++) {
		children.push_back(new Node2D(*node2.children.at(i)));
	}
	if (node2.textComponent) {
		textComponent = new Text(*node2.textComponent);
		textComponent->SetReferencingNode(this);
	}
	if (node2.objectComponent) {
		objectComponent = new Object2D(*node2.objectComponent);
		objectComponent->SetReferencingNode(this);
	}
}

Atlas::Node2D::Node2D(Node2D* parentNode)
	: Node(E_NodeType::TWODIMENSIONAL), parent(parentNode), objectComponent(nullptr), textComponent(nullptr), translation(0.0f), rotation(0.0f), scale(1.0f)
{
	parentNode->AddChildNode(this);
	SetName("Node");
}

Atlas::Node2D::~Node2D()
{
	for (int i = 0; i < children.size(); i++) {
		delete children.at(i);
	}
	children.clear();
	delete objectComponent;
	delete textComponent;
}

void Atlas::Node2D::Update(float deltaTime)
{
	for (int i = 0; i < children.size(); i++) {
		children.at(i)->Update(deltaTime);
	}
	if (objectComponent) {
		objectComponent->Update(deltaTime);
	}
	if (textComponent) {
		textComponent->Update(deltaTime);
	}
}

void Atlas::Node2D::Draw(Renderer* renderer, glm::mat4 currentTransformationMatrix)
{
#ifdef INHERIT_ROTATION
	glm::mat4 newTransformationMatrix = RotateAbout(GetTranslationScaleMatrix(), rotation) * currentTransformationMatrix;
#endif
#ifndef INHERIT_ROTATION
	glm::mat4 newTransformationMatrix = currentTransformationMatrix * GetTransformationMatrix();
#endif
#ifdef ATLAS_DEBUG
	printf("Name: %s\n", name.c_str());
	printf("Current Matrix:\n");
	printf("    (%f, %f, %f, %f)\n", currentTransformationMatrix[0][0], currentTransformationMatrix[0][1], currentTransformationMatrix[0][2], currentTransformationMatrix[0][3]);
	printf("    (%f, %f, %f, %f)\n", currentTransformationMatrix[1][0], currentTransformationMatrix[1][1], currentTransformationMatrix[1][2], currentTransformationMatrix[1][3]);
	printf("    (%f, %f, %f, %f)\n", currentTransformationMatrix[2][0], currentTransformationMatrix[2][1], currentTransformationMatrix[2][2], currentTransformationMatrix[2][3]);
	printf("    (%f, %f, %f, %f)\n", currentTransformationMatrix[3][0], currentTransformationMatrix[3][1], currentTransformationMatrix[3][2], currentTransformationMatrix[3][3]);
	printf("Personal Matrix:\n");
	printf("    (%f, %f, %f, %f)\n", GetTransformationMatrix()[0][0], GetTransformationMatrix()[0][1], GetTransformationMatrix()[0][2], GetTransformationMatrix()[0][3]);
	printf("    (%f, %f, %f, %f)\n", GetTransformationMatrix()[1][0], GetTransformationMatrix()[1][1], GetTransformationMatrix()[1][2], GetTransformationMatrix()[1][3]);
	printf("    (%f, %f, %f, %f)\n", GetTransformationMatrix()[2][0], GetTransformationMatrix()[2][1], GetTransformationMatrix()[2][2], GetTransformationMatrix()[2][3]);
	printf("    (%f, %f, %f, %f)\n", GetTransformationMatrix()[3][0], GetTransformationMatrix()[3][1], GetTransformationMatrix()[3][2], GetTransformationMatrix()[3][3]);
	printf("New Matrix:\n");
	printf("    (%f, %f, %f, %f)\n", newTransformationMatrix[0][0], newTransformationMatrix[0][1], newTransformationMatrix[0][2], newTransformationMatrix[0][3]);
	printf("    (%f, %f, %f, %f)\n", newTransformationMatrix[1][0], newTransformationMatrix[1][1], newTransformationMatrix[1][2], newTransformationMatrix[1][3]);
	printf("    (%f, %f, %f, %f)\n", newTransformationMatrix[2][0], newTransformationMatrix[2][1], newTransformationMatrix[2][2], newTransformationMatrix[2][3]);
	printf("    (%f, %f, %f, %f)\n", newTransformationMatrix[3][0], newTransformationMatrix[3][1], newTransformationMatrix[3][2], newTransformationMatrix[3][3]);
#endif
	for (int i = 0; i < children.size(); i++) {
		//children.at(i)->Draw(renderer, newTransformationMatrix);
		children.at(i)->Draw(renderer, newTransformationMatrix);
	}
	if (objectComponent) {
#ifdef ATLAS_DEBUG
		printf("   Object Transformation Matrix:\n");
		printf("        (%f, %f, %f, %f)\n", objectComponent->GetTransformationMatrix()[0][0], objectComponent->GetTransformationMatrix()[0][1], objectComponent->GetTransformationMatrix()[0][2], objectComponent->GetTransformationMatrix()[0][3]);
		printf("        (%f, %f, %f, %f)\n", objectComponent->GetTransformationMatrix()[1][0], objectComponent->GetTransformationMatrix()[1][1], objectComponent->GetTransformationMatrix()[1][2], objectComponent->GetTransformationMatrix()[1][3]);
		printf("        (%f, %f, %f, %f)\n", objectComponent->GetTransformationMatrix()[2][0], objectComponent->GetTransformationMatrix()[2][1], objectComponent->GetTransformationMatrix()[2][2], objectComponent->GetTransformationMatrix()[2][3]);
		printf("        (%f, %f, %f, %f)\n", objectComponent->GetTransformationMatrix()[3][0], objectComponent->GetTransformationMatrix()[3][1], objectComponent->GetTransformationMatrix()[3][2], objectComponent->GetTransformationMatrix()[3][3]);
		printf("Children size of %i\n", children.size());
		printf("-----------------------------------------------------------------------------------\n");
#endif
#ifdef INHERIT_ROTATION
		renderer->AddRenderable3D(Renderable3D(objectComponent, newTransformationMatrix * objectComponent->GetTransformationMatrix()));
#endif
#ifndef INHERIT_ROTATION
		objectComponent->SetFinalTransformation(newTransformationMatrix * objectComponent->GetTransformationMatrix());
		renderer->AddObject2D(objectComponent);
#endif
	}
#ifdef ATLAS_DEBUG
	else {
		printf("Children size of %i\n", children.size());
		printf("-----------------------------------------------------------------------------------\n");
	}
#endif
}

void Atlas::Node2D::AddChildNode(Node2D* newChild)
{
	children.push_back(newChild);
	newChild->SetParent(this);
}

void Atlas::Node2D::RemoveChildByNode(Node2D* child)
{
	for (int i = 0; i < children.size(); i++) {
		if (child == children.at(i)) {
			children.erase(children.begin() + i);
			break;
		}
	}
}

void Atlas::Node2D::RemoveChildByName(std::string name)
{
	for (int i = 0; i < children.size(); i++) {
		if (name == children.at(i)->GetName()) {
			children.erase(children.begin() + i);
			break;
		}
	}
}

void Atlas::Node2D::RemoveAndDeleteChildByNode(Node2D* child)
{
	for (int i = 0; i < children.size(); i++) {
		if (child == children.at(i)) {
			delete children.at(i);
			children.erase(children.begin() + i);
			break;
		}
	}
}

void Atlas::Node2D::RemoveAndDeleteChildByName(std::string name)
{
	for (int i = 0; i < children.size(); i++) {
		if (name == children.at(i)->GetName()) {
			delete children.at(i);
			children.erase(children.begin() + i);
			break;
		}
	}
}

Atlas::Node2D* Atlas::Node2D::SearchChildrenForNode(std::string nodeName)
{
	Node2D* returnValue = nullptr;
	if (this->name == nodeName) {
		return this;
	}
	for (int i = 0; i < children.size(); i++) {
		Node2D* temp = children.at(i)->SearchChildrenForNode(nodeName);
		if (temp) {
			returnValue = temp;
		}
	}
	return returnValue;
}

Atlas::Node2D* Atlas::Node2D::SearchParentAndChildrenForNode(std::string nodeName)
{
	Node2D* rootNode = this;
	Node2D* tempParent = rootNode->GetParent();
	while (tempParent) {
		rootNode = tempParent;
		tempParent = rootNode->GetParent();
	}

	return rootNode->SearchChildrenForNode(nodeName);
}

bool Atlas::Node2D::IsNameTaken(std::string name)
{
	return SearchParentAndChildrenForNode(name);
}

void Atlas::Node2D::SetParent(Node2D* newParent)
{
	parent = newParent;
}

void Atlas::Node2D::SetObject(Object2D* object)
{
	if (objectComponent) {
		objectComponent->SetReferencingNode(nullptr);
	}
	objectComponent = object;
	objectComponent->SetReferencingNode(this);
}

void Atlas::Node2D::SetText(Text* text)
{
	textComponent = text;
}

void Atlas::Node2D::SetName(std::string newName)
{
	int count = 1;
	if (IsNameTaken(newName)) {
		while (IsNameTaken(newName + std::to_string(count))) {
			count++;
		}
		name = newName + std::to_string(count);
	}
	else {
		name = newName;
	}
}

void Atlas::Node2D::SetTranslation(glm::vec2 newTranslation)
{
	translation = newTranslation;
}

void Atlas::Node2D::SetRotation(float newRotation)
{
	rotation = newRotation;
}

void Atlas::Node2D::SetScale(glm::vec2 newScale)
{
	scale = newScale;
}

Atlas::Node2D* Atlas::Node2D::GetParent()
{
	return parent;
}

std::vector<Atlas::Node2D*> Atlas::Node2D::GetChildren()
{
	return children;
}

Atlas::Object2D* Atlas::Node2D::GetObject()
{
	return objectComponent;
}

Atlas::Text* Atlas::Node2D::GetText() {
	return textComponent;
}

std::string Atlas::Node2D::GetName()
{
	return name;
}

glm::vec2 Atlas::Node2D::GetTranslation()
{
	return translation;
}

float Atlas::Node2D::GetRotation()
{
	return rotation;
}

glm::vec2 Atlas::Node2D::GetScale()
{
	return scale;
}

glm::mat4 Atlas::Node2D::GetTranslationMatrix()
{
	return glm::translate(glm::mat4(), glm::vec3(translation, 0.0f));
}

glm::mat4 Atlas::Node2D::GetRotationMatrix()
{
	return glm::yawPitchRoll(0.0f, 0.0f, glm::radians(rotation));
}

glm::mat4 Atlas::Node2D::GetScaleMatrix()
{
	return glm::scale(glm::mat4(), glm::vec3(scale, 1.0f));
}

glm::mat4 Atlas::Node2D::GetTransformationMatrix()
{
	return glm::translate(glm::mat4(), glm::vec3(translation, 0.0f)) * glm::yawPitchRoll(0.0f, 0.0f, glm::radians(rotation)) * glm::scale(glm::mat4(), glm::vec3(scale, 1.0f));
}

glm::mat4 Atlas::Node2D::GetTranslationScaleMatrix()
{
	return glm::translate(glm::mat4(), glm::vec3(translation, 0.0f)) * glm::scale(glm::mat4(), glm::vec3(scale, 1.0f));
}

glm::mat4 Atlas::Node2D::RotateAbout(glm::mat4 matrix, float rotation)
{
	return glm::yawPitchRoll(0.0f, 0.0f, glm::radians(rotation)) * matrix;
}
