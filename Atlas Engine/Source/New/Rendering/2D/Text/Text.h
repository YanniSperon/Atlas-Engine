#pragma once

#include <string>
#include "New/Rendering/2D/Object/Object2D.h"
#include "Font.h"

namespace Atlas {
	class Text {
	private:
		std::string text;
		Font* font;

		glm::mat4 finalTransformation;
	public:
		Text();
		~Text();

		void Update(float deltaTime);

		void SetFinalTransformation(glm::mat4 trans);
	};
}