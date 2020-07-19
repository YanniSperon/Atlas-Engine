#pragma once

#include <string>
#include <unordered_map>
#include "New/Rendering/Shared/Shader/Shader.h"

namespace Atlas {
	class ShaderManager {
	private:
		std::unordered_map<const std::string&, Shader*> loadedShaders;
	public:
		ShaderManager();
		~ShaderManager();
	};
}