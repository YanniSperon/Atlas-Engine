#include "Node3D.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"
#include "New/System/Global/Global.h"

Atlas::Node3D::Node3D()
	: parent(nullptr), cameraComponent(nullptr), lightComponent(nullptr), objectComponent(nullptr), translation(0.0f), rotation(0.0f), scale(1.0f)
{
	SetName("Root Node");
}

Atlas::Node3D::Node3D(Node3D* parentNode)
	: parent(parentNode), cameraComponent(nullptr), lightComponent(nullptr), objectComponent(nullptr), translation(0.0f), rotation(0.0f), scale(1.0f)
{
	parentNode->AddChildNode(this);
	SetName("Node");
}

Atlas::Node3D::~Node3D()
{
	for (int i = 0; i < children.size(); i++) {
		delete children.at(i);
	}
	children.clear();
	delete cameraComponent;
	delete lightComponent;
	delete objectComponent;
}

void Atlas::Node3D::Update(float deltaTime)
{
	for (int i = 0; i < children.size(); i++) {
		children.at(i)->Update(deltaTime);
	}
	if (cameraComponent) {
		cameraComponent->Update(deltaTime);
	}
	if (lightComponent) {
		lightComponent->Update(deltaTime);
	}
	if (objectComponent) {
		objectComponent->Update(deltaTime);
	}
}

void Atlas::Node3D::Draw(Renderer* renderer, glm::mat4 currentTransformationMatrix, glm::vec3 axis)
{
#ifdef INHERIT_ROTATION
	glm::mat4 newTransformationMatrix = RotateAbout(GetTranslationScaleMatrix(), rotation, axis) * currentTransformationMatrix;
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
		children.at(i)->Draw(renderer, newTransformationMatrix, translation);
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
		renderer->AddObject3D(objectComponent);
#endif
	}
#ifdef ATLAS_DEBUG
	else {
		printf("Children size of %i\n", children.size());
		printf("-----------------------------------------------------------------------------------\n");
	}
#endif
}

void Atlas::Node3D::AddChildNode(Node3D* newChild)
{
	children.push_back(newChild);
	newChild->SetParent(this);
}

void Atlas::Node3D::RemoveChildByNode(Node3D* child)
{
	for (int i = 0; i < children.size(); i++) {
		if (child == children.at(i)) {
			children.erase(children.begin() + i);
			break;
		}
	}
}

void Atlas::Node3D::RemoveChildByName(std::string name)
{
	for (int i = 0; i < children.size(); i++) {
		if (name == children.at(i)->GetName()) {
			children.erase(children.begin() + i);
			break;
		}
	}
}

void Atlas::Node3D::RemoveAndDeleteChildByNode(Node3D* child)
{
	for (int i = 0; i < children.size(); i++) {
		if (child == children.at(i)) {
			delete children.at(i);
			children.erase(children.begin() + i);
			break;
		}
	}
}

void Atlas::Node3D::RemoveAndDeleteChildByName(std::string name)
{
	for (int i = 0; i < children.size(); i++) {
		if (name == children.at(i)->GetName()) {
			delete children.at(i);
			children.erase(children.begin() + i);
			break;
		}
	}
}

Atlas::Node3D* Atlas::Node3D::SearchChildrenForNode(std::string nodeName)
{
	Node3D* returnValue = nullptr;
	if (this->name == nodeName) {
		return this;
	}
	for (int i = 0; i < children.size(); i++) {
		Node3D* temp = children.at(i)->SearchChildrenForNode(nodeName);
		if (temp) {
			returnValue = temp;
		}
	}
	return returnValue;
}

Atlas::Node3D* Atlas::Node3D::SearchParentAndChildrenForNode(std::string nodeName)
{
	Node3D* rootNode = this;
	Node3D* tempParent = rootNode->GetParent();
	while (tempParent) {
		rootNode = tempParent;
		tempParent = rootNode->GetParent();
	}

	return rootNode->SearchChildrenForNode(nodeName);
}

bool Atlas::Node3D::IsNameTaken(std::string name)
{
	return SearchParentAndChildrenForNode(name);
}

void Atlas::Node3D::ControlCamera(float mouseSensitivity, float movementSpeed, float deltaTime)
{
	if (cameraComponent) {
		if (Global::Variables.keyIn.sHeld) {
			translation += cameraComponent->MoveBackwardComponent(movementSpeed, deltaTime);
		}
		if (Global::Variables.keyIn.wHeld) {
			translation += cameraComponent->MoveForwardComponent(movementSpeed, deltaTime);
		}
		if (Global::Variables.keyIn.dHeld) {
			translation += cameraComponent->StrafeRightComponent(movementSpeed, deltaTime);
		}
		if (Global::Variables.keyIn.aHeld) {
			translation += cameraComponent->StrafeLeftComponent(movementSpeed, deltaTime);
		}
		if (Global::Variables.keyIn.leftControlHeld) {
			translation += cameraComponent->MoveDownComponent(movementSpeed, deltaTime);
		}
		if (Global::Variables.keyIn.spaceHeld) {
			translation += cameraComponent->MoveUpComponent(movementSpeed, deltaTime);
		}

		cameraComponent->LookAtMouse(0.2f, Global::Variables.mouseIn.mouseXPos, Global::Variables.mouseIn.mouseYPos);
	}
}

void Atlas::Node3D::SetParent(Node3D* newParent)
{
	parent = newParent;
}

void Atlas::Node3D::SetCamera(Camera* camera)
{
	if (cameraComponent) {
		cameraComponent->SetReferencingNode(nullptr);
	}
	cameraComponent = camera;
	cameraComponent->SetReferencingNode(this);
}

void Atlas::Node3D::SetLight(Light* light)
{
	if (lightComponent) {
		lightComponent->SetReferencingNode(nullptr);
	}
	lightComponent = light;
	lightComponent->SetReferencingNode(this);
}

void Atlas::Node3D::SetObject(Object3D* object)
{
	if (objectComponent) {
		objectComponent->SetReferencingNode(nullptr);
	}
	objectComponent = object;
	objectComponent->SetReferencingNode(this);
}

void Atlas::Node3D::SetName(std::string newName)
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

void Atlas::Node3D::SetTranslation(glm::vec3 newTranslation)
{
	translation = newTranslation;
}

void Atlas::Node3D::SetRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
}

void Atlas::Node3D::SetScale(glm::vec3 newScale)
{
	scale = newScale;
}

Atlas::Node3D* Atlas::Node3D::GetParent()
{
	return parent;
}

std::vector<Atlas::Node3D*> Atlas::Node3D::GetChildren()
{
	return children;
}

Atlas::Object3D* Atlas::Node3D::GetObject()
{
	return objectComponent;
}

Atlas::Light* Atlas::Node3D::GetLight()
{
	return lightComponent;
}

Atlas::Camera* Atlas::Node3D::GetCamera()
{
	return cameraComponent;
}

std::string Atlas::Node3D::GetName()
{
	return name;
}

glm::vec3 Atlas::Node3D::GetTranslation()
{
	return translation;
}

glm::vec3 Atlas::Node3D::GetRotation()
{
	return rotation;
}

glm::vec3 Atlas::Node3D::GetScale()
{
	return scale;
}

glm::mat4 Atlas::Node3D::GetTranslationMatrix()
{
	return glm::translate(glm::mat4(), translation);
}

glm::mat4 Atlas::Node3D::GetRotationMatrix()
{
	return glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
}

glm::mat4 Atlas::Node3D::GetScaleMatrix()
{
	return glm::scale(glm::mat4(), scale);
}

glm::mat4 Atlas::Node3D::GetTransformationMatrix()
{
	return glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)) * glm::scale(glm::mat4(), scale);
}

glm::mat4 Atlas::Node3D::GetTranslationScaleMatrix()
{
	return glm::translate(glm::mat4(), translation) * glm::scale(glm::mat4(), scale);
}

glm::mat4 Atlas::Node3D::GetCameraViewMatrix()
{
	if (cameraComponent) {
		return glm::lookAt(translation, translation + cameraComponent->GetForwardDirection(), cameraComponent->GetUpwardDirection());
	}
	return glm::mat4();
}

glm::mat4 Atlas::Node3D::GetCameraProjectionMatrix()
{
	if (cameraComponent) {
		return cameraComponent->GetProjectionMatrix();
	}
	return glm::mat4();
}

glm::mat4 Atlas::Node3D::RotateAbout(glm::mat4 matrix, glm::vec3 rotation, glm::vec3 axis)
{
	glm::mat4 returnValue = matrix;
#ifdef ATLAS_DEBUG
	printf("Input:\n");
	printf("    [(%f, %f, %f, %f)\n", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
	printf("    (%f, %f, %f, %f)\n", matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
	printf("    (%f, %f, %f, %f)\n", matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
	printf("    (%f, %f, %f, %f)]\n", matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
	printf("    Axis: (%f, %f, %f)\n", axis.x, axis.y, axis.z);
	printf("    Rotation: (%f, %f, %f)\n", rotation.x, rotation.y, rotation.z);
#endif
	if (axis.x > 0.05f || axis.x < -0.05f) {
		returnValue = glm::rotate(returnValue, glm::radians(rotation.x), glm::vec3(axis.x, 0.0f, 0.0f));
#ifdef ATLAS_DEBUG
		printf("X Rotation:\n");
		printf("    (%f, %f, %f, %f)\n", returnValue[0][0], returnValue[0][1], returnValue[0][2], returnValue[0][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[1][0], returnValue[1][1], returnValue[1][2], returnValue[1][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[2][0], returnValue[2][1], returnValue[2][2], returnValue[2][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[3][0], returnValue[3][1], returnValue[3][2], returnValue[3][3]);
#endif
	}
	if (axis.y > 0.05f || axis.y < -0.05f) {
		returnValue = glm::rotate(returnValue, glm::radians(rotation.y), glm::vec3(0.0f, axis.y, 0.0f));
#ifdef ATLAS_DEBUG
		printf("Y Rotation:\n");
		printf("    (%f, %f, %f, %f)\n", returnValue[0][0], returnValue[0][1], returnValue[0][2], returnValue[0][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[1][0], returnValue[1][1], returnValue[1][2], returnValue[1][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[2][0], returnValue[2][1], returnValue[2][2], returnValue[2][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[3][0], returnValue[3][1], returnValue[3][2], returnValue[3][3]);
#endif
	}
	if (axis.z > 0.05f || axis.z < -0.05f) {
		returnValue = glm::rotate(returnValue, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, axis.z));
#ifdef ATLAS_DEBUG
		printf("Z Rotation:\n");
		printf("    (%f, %f, %f, %f)\n", returnValue[0][0], returnValue[0][1], returnValue[0][2], returnValue[0][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[1][0], returnValue[1][1], returnValue[1][2], returnValue[1][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[2][0], returnValue[2][1], returnValue[2][2], returnValue[2][3]);
		printf("    (%f, %f, %f, %f)\n", returnValue[3][0], returnValue[3][1], returnValue[3][2], returnValue[3][3]);
#endif
	}

	return returnValue;
}
