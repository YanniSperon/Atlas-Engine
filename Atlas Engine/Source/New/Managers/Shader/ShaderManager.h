#pragma once

#include <string>
#include <unordered_map>
#include "New/Rendering/Shared/Shader/Shader.h"
#include "New/Scene/Shared/Updatable/Updatable.h"

namespace Atlas {
	class ShaderManager : public Updatable {
	private:
		std::unordered_map<const std::string&, Shader*> loadedShaders;

		ShaderProgramSource& ReadShader(const std::string filepath);
		GLuint LoadShader(ShaderProgramSource source);
		GLuint CompileShader(GLuint type, const std::string& source);
	public:
		ShaderManager();
		~ShaderManager();

		virtual void Update(float deltaTime);

		Shader* LoadShader(const std::string& filepath);

		Shader* GetShader(Shader* shdr);
		Shader* GetShader(ShaderProgramSource& src, const std::string& filepath);
		void DeleteReference(Object* obj);
		void AddReference(Object* obj);

		void DeleteShader(const std::string& name);
		void DeleteShader(Shader* shdr);

		void SetShader(Shader* newShdr);
		void ReplaceShader(Shader* newShdr);
	};
}