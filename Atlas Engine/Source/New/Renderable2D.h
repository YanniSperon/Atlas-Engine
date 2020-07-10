#pragma once

#include "Object2D.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	class Renderable2D {
	private:
		Object2D* objectBeingRendered;

		glm::vec2 finalTranslation;
		float finalRotation;
		glm::vec2 finalScale;
	public:
		Renderable2D();
		~Renderable2D();

		Object2D* GetObject();
	};
}