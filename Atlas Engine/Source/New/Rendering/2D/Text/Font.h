#pragma once

#include "GL/glew.h"
#include <vector>
#include "New/Rendering/2D/Object/Object2D.h"
#include "New/Rendering/Shared/Texture/Texture.h"

namespace Atlas {
	class Font {
	private:
		Texture* texture;
		std::vector<Object2D*> characters;
	public:
		Font();
		~Font();

		void LoadFontSheet();

		void LoadIntoVRAM();
		void UnloadFromVRAM();
	};
}