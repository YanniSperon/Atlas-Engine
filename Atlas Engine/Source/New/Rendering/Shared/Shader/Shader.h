#pragma once

#include <string>
#include <unordered_map>
#include <set>
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "New/Rendering/Shared/Object/Object.h"

namespace Atlas {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	private:
		std::string filepath;
		std::string name;
		GLuint rendererID;
		std::unordered_map<std::string, int> uniformLocationCache;
		std::set<Object*> referencingObjects;
	public:
		Shader();
		Shader(const Shader& shader2);
		Shader(const std::string& path);
		Shader(const ShaderProgramSource& source, const std::string& path);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformVec3f(const std::string& name, const glm::vec3& vector);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
		GLuint GetShaderID();
		const std::string& GetFilepath();
		const std::string& GetName();
		void SetName(const std::string& newName);

		std::set<Object*>& GetReferencingObjects();
		void SetReferencingObjects(std::set<Object*>& newRefObj);
	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		int GetUniformLocation(const std::string& name);
	};
}