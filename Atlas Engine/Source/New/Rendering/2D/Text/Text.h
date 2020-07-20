#pragma once

#include <string>
#include "New/Rendering/2D/Object/Object2D.h"
#include "New/Scene/Shared/Node/Node.h"
#include "Font.h"

namespace Atlas {
	class Text {
	private:
		std::string text;
		Font* font;

		glm::mat4 finalTransformation;

		Node* referencingNode;
	public:
		Text();
		~Text();

		void Update(float deltaTime);

		void SetFinalTransformation(glm::mat4 trans);

		Node* GetReferencingNode();
		void SetReferencingNode(Node* newNode);
	};
}