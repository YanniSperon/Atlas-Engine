#pragma once

#include "L_Mesh.h"
#include "Legacy/L_Rendering/L_Primitives/L_ShapeData.h"
#include "L_Shader.h"

namespace L_Atlas {

	struct L_Material {
		glm::vec3 ambient, diffuse, specular;
		float shininess;

		L_Material()
			: ambient(1.0f, 1.0f, 1.0f), diffuse(1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f), shininess(32)
		{

		}

		L_Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shin)
			: ambient(amb), diffuse(diff), specular(spec), shininess(shin)
		{

		}
	};

	class L_Object : public L_Mesh {
	private:
		unsigned long long int uid;
		GLuint vertexBufferID;
		GLuint indexBufferID;
		GLuint texID;
		GLuint shaderID;
		GLsizei numIndices;
		L_Material material;
		bool glInitialized;
		std::string textureDirectory;
		std::string textureName;
		std::string shaderDirectory;
		std::string shaderName;
		bool hasLighting;
	public:
		L_Object();
		L_Object(L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, unsigned long long int uid);
		L_Object(L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s);
		L_Object(L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderFileName, bool glInit, bool lighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, L_Material mat);
		virtual ~L_Object();

		void GLInit();
		void Draw();
		void Bind();
		void Unbind();
		void SetShader(GLuint id);
		void SetShader(std::string dir, std::string name);
		void SetTexture(GLuint tex);
		void SetTexture(std::string dir, std::string name);
		void SetMaterial(L_Material mat);
		void SetHasLighting(bool newValue);

		unsigned int GetNumIndices();
		GLuint GetShaderID();
		GLuint GetTextureID();
		std::string GetTextureDirectory();
		std::string GetTextureName();
		std::string GetShaderDirectory();
		std::string GetShaderName();
		bool GetGLInitialized();
		bool GetHasLighting();
		L_Material GetMaterial();
		GLuint GetVBO();
		GLuint GetIBO();

		unsigned long long int GetUID();

		virtual std::string GetType() override;

		static void FlushCache();
	};
}