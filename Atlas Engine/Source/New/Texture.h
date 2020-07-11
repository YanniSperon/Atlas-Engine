#pragma once

#include "GL/glew.h"
#include <string>

namespace Atlas {
	class Texture {
	private:
		GLuint textureID;

		GLuint LoadTexture(const std::string& texDirAndName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
	public:
		Texture();
		Texture(const std::string& texDirAndName);
		~Texture();

		void Bind();
		void Unbind();
	};
}