#pragma once

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a);
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "Mesh3D.h"
#include <string>

namespace Atlas {
	class MeshGenerator {
	public:
		static Mesh3D CreateCube(const glm::vec3& min, const glm::vec3& max);
		static Mesh3D LoadTexturedShape(const std::string& modelDirAndName);
	};
}