#pragma once

#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	struct Vertex3D {
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};
}