#pragma once

#include <vector>
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "Text.h"
#include "Object2D.h"
#include "Renderer.h"

namespace Atlas {
	class Node2D {
	private:
		Node2D* parent;
		std::vector<Node2D*> children;
		Object2D* objectComponent;
		Text* textComponent;
		std::string name;
		glm::vec2 translation;
		float rotation;
		glm::vec2 scale;
	public:
		Node2D();
		Node2D(Node2D* parentNode);
		~Node2D();

		void Update(float deltaTime);
		void Draw(Renderer* renderer, glm::mat4 currentTransformationMatrix);

		void AddChildNode(Node2D* newChild);
		void RemoveChildByNode(Node2D* child);
		void RemoveChildByName(std::string name);
		void RemoveAndDeleteChildByNode(Node2D* child);
		void RemoveAndDeleteChildByName(std::string name);

		Node2D* SearchChildrenForNode(std::string nodeName);
		Node2D* SearchParentAndChildrenForNode(std::string nodeName);

		bool IsNameTaken(std::string nodeName);

		Node2D* GetParent();
		std::vector<Node2D*> GetChildren();
		Object2D* GetObject();
		Text* GetText();
		std::string GetName();
		glm::vec2 GetTranslation();
		float GetRotation();
		glm::vec2 GetScale();

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::mat4 GetTransformationMatrix();
		glm::mat4 GetTranslationScaleMatrix();
		glm::mat4 GetCameraViewMatrix();
		glm::mat4 GetCameraProjectionMatrix();
		glm::mat4 RotateAbout(glm::mat4 matrix, float rotation);

		void SetParent(Node2D* newParent);
		void SetObject(Object2D* object);
		void SetText(Text* text);
		void SetName(std::string newName);
		void SetTranslation(glm::vec2 newTranslation);
		void SetRotation(float newRotation);
		void SetScale(glm::vec2 newScale);
	};
}