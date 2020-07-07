#include "L_Object.h"
#include "GLFW/glfw3.h"
#include "Legacy/L_Global/L_Global.h"
#include "L_Loader.h"
#include <iostream>
#include <algorithm>
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_STB_Image/stb_image.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Other/L_Convert.h"
#include "Legacy/L_Physics/L_PhysicsEngine.h"
#include "Shared/S_Vendor/S_Bullet/LinearMath/btQuaternion.h"

namespace L_Atlas {

	static int AddValueTexture(std::string meshName, int value) {
		if (value == 0) {
			if (L_Global::Variables.loadedTextureCache.find(meshName) != L_Global::Variables.loadedTextureCache.end()) {
				return AddValueTexture(meshName, value + 1);
			}
			else {
				return value;
			}
		}
		else {
			if (L_Global::Variables.loadedTextureCache.find(meshName + std::to_string(value)) != L_Global::Variables.loadedTextureCache.end()) {
				return AddValueTexture(meshName, value + 1);
			}
			else {
				return value;
			}
		}
	}

	L_Object::L_Object()
		: L_Mesh(), vertexBufferID(0), indexBufferID(0), numIndices(0), texID(0), shaderID(0), material(), glInitialized(false), textureDirectory(""), textureName(""), hasLighting(false), shaderDirectory(""), shaderName("")
	{

	}

	L_Object::L_Object(L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, unsigned long long int uid)
		: L_Mesh(type, meshDir, meshName), material(), glInitialized(glInit), textureDirectory(texDir), textureName(texName), hasLighting(lighting), indexBufferID(0), vertexBufferID(0), shaderDirectory(shaderDir), shaderName(shaderFileName)
	{
		if (L_Global::Variables.textureCache.find(texDir + texName) != L_Global::Variables.textureCache.end()) {
			texID = L_Global::Variables.textureCache[texDir + texName];
		}
		else {
			std::string file = texDir + texName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string textureDir = pathtemp.directory;
			std::string texName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedTextureCache[texName] = physicalLocation;

			L_Global::Variables.textureCache[textureDir + texName] = L_Loader::LoadTexture(textureDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
			texID = L_Global::Variables.textureCache[textureDir + texName];
		}

		if (L_Global::Variables.shaderCache.find(shaderDir + shaderFileName) != L_Global::Variables.shaderCache.end()) {
			shaderID = L_Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		else {
			std::string file = shaderDir + shaderFileName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string shadrDirectory = pathtemp.directory;
			std::string shadrName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedShaderCache[shadrName] = physicalLocation;

			L_Global::Variables.shaderCache[shadrDirectory + shadrName] = new L_Shader(shadrDirectory + shadrName);
			shaderID = L_Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		}
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	L_Object::L_Object(L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: L_Mesh(type, meshDir, meshName, rot, trans, s), material(), glInitialized(glInit), textureDirectory(texDir), textureName(texName), shaderDirectory(shaderDir), shaderName(shaderFileName), hasLighting(lighting), indexBufferID(0), vertexBufferID(0)
	{
		if (L_Global::Variables.textureCache.find(texDir + texName) != L_Global::Variables.textureCache.end()) {
			texID = L_Global::Variables.textureCache[texDir + texName];
		}
		else {
			std::string file = texDir + texName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string textureDir = pathtemp.directory;
			std::string texName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedTextureCache[texName] = physicalLocation;

			L_Global::Variables.textureCache[textureDir + texName] = L_Loader::LoadTexture(textureDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
			texID = L_Global::Variables.textureCache[textureDir + texName];
		}

		if (L_Global::Variables.shaderCache.find(shaderDir + shaderFileName) != L_Global::Variables.shaderCache.end()) {
			shaderID = L_Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		else {
			std::string file = shaderDir + shaderFileName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string shadrDirectory = pathtemp.directory;
			std::string shadrName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedShaderCache[shadrName] = physicalLocation;

			L_Global::Variables.shaderCache[shadrDirectory + shadrName] = new L_Shader(shadrDirectory + shadrName);
			shaderID = L_Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		}
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	L_Object::L_Object(L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, L_Material mat)
		: L_Mesh(type, meshDir, meshName, rot, trans, s), material(mat), glInitialized(glInit), textureDirectory(texDir), textureName(texName), shaderDirectory(shaderDir), shaderName(shaderFileName), hasLighting(lighting), indexBufferID(0), vertexBufferID(0)
	{
		if (L_Global::Variables.textureCache.find(texDir + texName) != L_Global::Variables.textureCache.end()) {
			texID = L_Global::Variables.textureCache[texDir + texName];
		}
		else {
			std::string file = texDir + texName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string textureDir = pathtemp.directory;
			std::string texName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedTextureCache[texName] = physicalLocation;

			L_Global::Variables.textureCache[textureDir + texName] = L_Loader::LoadTexture(textureDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
			texID = L_Global::Variables.textureCache[textureDir + texName];
		}

		if (L_Global::Variables.shaderCache.find(shaderDir + shaderFileName) != L_Global::Variables.shaderCache.end()) {
			shaderID = L_Global::Variables.shaderCache[shaderDir + shaderFileName]->GetShaderID();
		}
		else {
			std::string file = shaderDir + shaderFileName;
			std::replace(file.begin(), file.end(), '\\', '/');
			std::string physicalLocation = "";

			file = L_System::ConvertFilePathToLocal(file);
			L_Filepath pathtemp = L_System::SeperateFilepath(file);
			std::string shadrDirectory = pathtemp.directory;
			std::string shadrName = pathtemp.filename;
			physicalLocation = pathtemp.directory + pathtemp.filename;

			L_Global::Variables.loadedShaderCache[shadrName] = physicalLocation;

			L_Global::Variables.shaderCache[shadrDirectory + shadrName] = new L_Shader(shadrDirectory + shadrName);
			shaderID = L_Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		}
		numIndices = (GLsizei)GetShape().numIndices;

		if (glInit) {
			GLInit();
		}
	}

	L_Object::~L_Object()
	{
		if (glInitialized) {
			Unbind();
			glDeleteBuffers(1, &vertexBufferID);
			glDeleteBuffers(1, &indexBufferID);
		}
	}

	void L_Object::GLInit()
	{
		glInitialized = true;

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));



		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);



		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glFinish();
	}

	void L_Object::Draw()
	{
		Bind();
		//glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	}

	void L_Object::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	}

	void L_Object::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int L_Object::GetNumIndices()
	{
		return numIndices;
	}

	void L_Object::SetShader(GLuint id)
	{
		shaderID = id;
	}

	void L_Object::SetShader(std::string dir, std::string name)
	{
		if (L_Global::Variables.shaderCache.find(dir + name) != L_Global::Variables.shaderCache.end()) {
			shaderID = L_Global::Variables.shaderCache[dir + name]->GetShaderID();
		}
		else {
			L_Global::Variables.shaderCache[dir + name] = new L_Shader(dir + name);
			shaderID = L_Global::Variables.shaderCache[dir + name]->GetShaderID();
		}

		shaderDirectory = dir;
		shaderName = name;
	}

	void L_Object::SetTexture(GLuint tex)
	{
		texID = tex;
	}

	void L_Object::SetTexture(std::string dir, std::string name)
	{
		if (L_Global::Variables.textureCache.find(dir + name) != L_Global::Variables.textureCache.end()) {
			texID = L_Global::Variables.textureCache[dir + name];
		}
		else {
			L_Global::Variables.textureCache[dir + name] = L_Loader::LoadTexture(dir, name, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
			texID = L_Global::Variables.textureCache[dir + name];
		}

		textureDirectory = dir;
		textureName = name;
	}

	void L_Object::SetMaterial(L_Material mat)
	{
		material = mat;
	}

	GLuint L_Object::GetShaderID()
	{
		return shaderID;
	}

	GLuint L_Object::GetTextureID()
	{
		return texID;
	}

	std::string L_Object::GetTextureDirectory()
	{
		return textureDirectory;
	}

	std::string L_Object::GetTextureName()
	{
		return textureName;
	}

	std::string L_Object::GetShaderDirectory()
	{
		return shaderDirectory;
	}

	std::string L_Object::GetShaderName()
	{
		return shaderName;
	}

	L_Material L_Object::GetMaterial()
	{
		return material;
	}

	GLuint L_Object::GetVBO()
	{
		return vertexBufferID;
	}

	GLuint L_Object::GetIBO()
	{
		return indexBufferID;
	}

	unsigned long long int L_Object::GetUID()
	{
		return uid;
	}

	bool L_Object::GetGLInitialized()
	{
		return glInitialized;
	}

	bool L_Object::GetHasLighting()
	{
		return hasLighting;
	}

	void L_Object::SetHasLighting(bool newValue)
	{
		hasLighting = newValue;
	}

	std::string L_Object::GetType()
	{
		return "Object";
	}

	void L_Object::FlushCache()
	{
		for (auto it : L_Global::Variables.textureCache) {
			glDeleteTextures(1, &it.second);
		}
		L_Global::Variables.textureCache.erase(L_Global::Variables.textureCache.begin(), L_Global::Variables.textureCache.end());

		for (auto it : L_Global::Variables.shaderCache) {
			it.second->Unbind();
			delete it.second;
		}
		L_Global::Variables.shaderCache.erase(L_Global::Variables.shaderCache.begin(), L_Global::Variables.shaderCache.end());
	}
}