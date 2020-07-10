#pragma once

#include <string>
#include "Object2D.h"
#include "Font.h"

namespace Atlas {
	class Text {
	private:
		std::string text;
		Font* font;
	public:
		Text();
		~Text();

		void Update(float deltaTime);
	};
}