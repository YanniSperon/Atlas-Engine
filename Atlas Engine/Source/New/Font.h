#pragma once

#include "GL/glew.h"
#include <vector>
#include "Object2D.h"
#include "Texture.h"

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