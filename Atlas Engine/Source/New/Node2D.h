#pragma once

#include <vector>
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "Text.h"
#include "Object2D.h"

namespace Atlas {
	class Node2D {
	private:
		Node2D* parent;
		std::vector<Node2D*> children;
		glm::vec3 translation;
		Object2D* objectComponent;
		Text* textComponent;
	public:
		Node2D();
		~Node2D();
		// an individual node may contain a camera, a light, an object (physics body/mesh), and an infinite number of children nodes

		void Update(float deltaTime);

		void AddChildNode(Node2D* newChild);

		void RemoveAndDeleteChildNode(Node2D* child);



		void SetParent(Node2D* newParent);

		Node2D* GetParentNode();
		std::vector<Node2D*> GetChildren();
		Object2D* GetObjectComponent();
		Text* GetTextComponent();
	};
}