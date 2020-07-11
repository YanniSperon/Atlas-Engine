#pragma once

#include "Object2D.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	class Renderable2D {
	private:
		Object2D* objectBeingRendered;

		glm::mat4 finalTransformation;
	public:
		Renderable2D(Object2D* object);
		Renderable2D(Object2D* object, glm::mat4 transformationMatrix);
		Renderable2D(Object2D* object, glm::mat4 translation, glm::mat4 rotation, glm::mat4 scale);
		~Renderable2D();

		Object2D* GetObject();
		glm::mat4 GetTransformMatrix();
	};
}