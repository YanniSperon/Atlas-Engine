#pragma once

#include "GL/glew.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include <string>

namespace L_Atlas {

	struct L_TexCoords {
		glm::vec2 min;
		glm::vec2 max;
	};

	class L_Loader {
	public:
		static GLuint LoadTexture(const std::string& texDirAndName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
		static GLuint LoadTexture(const std::string& texDir, const std::string& texName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
		static L_TexCoords GetTextureCoordinates(GLuint minX, GLuint minY, GLuint maxX, GLuint maxY, GLuint width, GLuint height);
	};
}