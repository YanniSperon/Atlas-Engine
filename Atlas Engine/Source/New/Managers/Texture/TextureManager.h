#pragma once

#include <string>
#include <unordered_map>
#include "New/Rendering/Shared/Texture/Texture.h"

namespace Atlas {
	class TextureManager {
	private:
		std::unordered_map<const std::string&, Texture*> loadedTextures;
	public:
		TextureManager();
		~TextureManager();
	};
}