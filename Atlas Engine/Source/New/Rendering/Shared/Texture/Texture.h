#pragma once

#include "GL/glew.h"
#include "New/Rendering/Shared/Object/Object.h"
#include <string>
#include <set>

namespace Atlas {
	class Texture {
	private:
		GLuint textureID;
		std::string filepath;
		std::string name;
		std::set<Object*> referencingObjects;

		GLuint LoadTexture(const std::string& texDirAndName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
	public:
		Texture();
		Texture(const Texture& tex2);
		Texture(const std::string& texDirAndName);
		Texture(GLuint texID, const std::string& path, const std::string& texName);
		~Texture();

		void Bind();
		void Unbind();
		
		const std::string& GetName();
		const std::string& GetFilepath();
		std::set<Object*>& GetReferencingObjects();

		void SetName(const std::string& newName);
		void SetReferencingObjects(std::set<Object*>& newRefObj);
	};
}