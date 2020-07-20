#pragma once

#include "New/Scene/Shared/Node/Node.h"

namespace Atlas {
	class Light {
	private:
		// include data about color etc, make different types of lights extend this class

		Node* referencingNode;
	public:
		Light();
		Light(const Light& light2);
		~Light();

		void Update(float deltaTime);

		Node* GetReferencingNode();
		void SetReferencingNode(Node* node);
	};
}