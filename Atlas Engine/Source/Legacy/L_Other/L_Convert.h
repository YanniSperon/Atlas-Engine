#pragma once

#include "Shared/S_Vendor/S_Bullet/btBulletDynamicsCommon.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include <vector>

namespace L_Atlas {
	class L_Convert {
	public:
		static glm::vec3 Vector3(const btVector3& vec);
		static btVector3 Vector3(const glm::vec3& vec);
		static std::vector<std::string> SeperateByDelimiter(const std::string& in, const char& delimiter);
		static std::string FormatSpaces(std::string in);
		static std::string Trim(std::string in);
		static void LeftTrim(std::string& in);
		static void RightTrim(std::string& in);
	};
}