#pragma once

#include "GL/glew.h"
#include "New/Rendering/Shared/Object/Object.h"
#include <string>
#include <vector>

namespace Atlas {
	class Texture {
	private:
		GLuint textureID;
		std::string filePath;
		std::vector<Object*> referencingObjects;

		GLuint LoadTexture(const std::string& texDirAndName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
	public:
		Texture();
		Texture(const std::string& texDirAndName);
		~Texture();

		void Bind();
		void Unbind();
		const std::string& GetName();
		std::vector<void*>& GetReferencingObjects();
	};
}