#pragma once

#include <string>
#include <unordered_map>
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace L_Atlas {

	struct L_ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class L_Shader
	{
	private:
		std::string m_FilePath;
		GLuint m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	public:
		L_Shader();
		L_Shader(const std::string& filepath);
		~L_Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformVec3f(const std::string& name, const glm::vec3& vector);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
		GLuint GetShaderID();
	private:
		L_ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		int GetUniformLocation(const std::string& name);
	};
}