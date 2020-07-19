#include "Texture.h"
#include "Shared/S_Vendor/S_STB_Image/stb_image.h"
#include <iostream>

GLuint Atlas::Texture::LoadTexture(const std::string& texDirAndName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter)
{
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texDirAndName.c_str(), &width, &height, &nrChannels, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMaxFilter);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture \"%s\"!", texDirAndName.c_str());
	}
	return texID;
}

Atlas::Texture::Texture()
	: textureID(0), filePath("INVALID")
{
}

Atlas::Texture::Texture(const std::string& texDirAndName)
	: textureID(0), filePath(texDirAndName)
{
	textureID = LoadTexture(texDirAndName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
}

Atlas::Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

void Atlas::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Atlas::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

const std::string& Atlas::Texture::GetName()
{
	return filePath;
}

std::vector<void*>& Atlas::Texture::GetReferencingObjects()
{
	return referencingObjects;
}