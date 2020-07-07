#pragma once

#include "L_ShapeData.h"
#include <string>

namespace L_Atlas {

	class L_ShapeGenerator {
	public:
		static L_ShapeData makeCube(const glm::vec3& min, const glm::vec3& max);
		static L_ShapeData makeInvertedLightingCube(const glm::vec3& min, const glm::vec3& max);
		static L_ShapeData makeSkybox(const glm::vec3& min, const glm::vec3& max);
		static L_ShapeData loadShape(const std::string& fileName);
		static L_ShapeData loadTexturedShape(const std::string& directory, const std::string& name);

		static L_ShapeData2D makeSquare(const glm::vec2& min, const glm::vec2& max, const glm::vec2& minTexCoords, const glm::vec2& maxTexCoords);
	};
}