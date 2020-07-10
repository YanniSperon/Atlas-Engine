#pragma once

#include "Text.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	class RenderableText {
	private:
		Text* text;

		glm::vec2 finalTranslation;
		float finalRotation;
		glm::vec2 finalScale;
	public:
		RenderableText();
		~RenderableText();

		Text* GetText();
	};
}