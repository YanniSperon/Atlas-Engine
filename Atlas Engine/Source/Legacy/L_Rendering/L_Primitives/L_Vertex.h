#pragma once
#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace L_Atlas {
	struct L_Vertex {
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};

	struct L_Vertex2D {
		glm::vec2 position;
		glm::vec2 texCoord;
	};
}