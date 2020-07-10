#pragma once

#include <vector>
#include <string>
#include "Camera.h"
#include "Light.h"
#include "Object3D.h"
#include "Renderer.h"

namespace Atlas {
	class Node3D {
	private:
		Node3D* parent;
		std::vector<Node3D*> children;
		Camera* cameraComponent;
		Light* lightComponent;
		Object3D* objectComponent;
		std::string name;
		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;
	public:
		Node3D();
		Node3D(Node3D* parentNode);
		~Node3D();
		// an individual node may contain a camera, a light, an object (physics body/mesh), and an infinite number of children nodes

		void Update(float deltaTime);
		void Draw(Renderer* renderer, glm::mat4 currentTransformationMatrix, glm::vec3 axis);

		void AddChildNode(Node3D* newChild);
		void RemoveChildByNode(Node3D* child);
		void RemoveChildByName(std::string name);
		void RemoveAndDeleteChildByNode(Node3D* child);
		void RemoveAndDeleteChildByName(std::string name);

		Node3D* SearchChildrenForNode(std::string nodeName);
		Node3D* SearchParentAndChildrenForNode(std::string nodeName);

		bool IsNameTaken(std::string nodeName);

		void ControlCamera(float mouseSensitivity, float movementSpeed, float deltaTime);

		Node3D* GetParent();
		std::vector<Node3D*> GetChildren();
		Camera* GetCamera();
		Light* GetLight();
		Object3D* GetObject();
		std::string GetName();
		glm::vec3 GetTranslation();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();
		
		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::mat4 GetTransformationMatrix();
		glm::mat4 GetTranslationScaleMatrix();
		glm::mat4 GetCameraViewMatrix();
		glm::mat4 GetCameraProjectionMatrix();
		glm::mat4 RotateAbout(glm::mat4 matrix, glm::vec3 rotation, glm::vec3 axis);

		void SetParent(Node3D* newParent);
		void SetCamera(Camera* camera);
		void SetLight(Light* light);
		void SetObject(Object3D* object);
		void SetName(std::string newName);
		void SetTranslation(glm::vec3 newTranslation);
		void SetRotation(glm::vec3 newRotation);
		void SetScale(glm::vec3 newScale);
	};
}