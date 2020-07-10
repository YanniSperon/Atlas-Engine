#pragma once

#include "Object3D.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	class Renderable3D {
	private:
		Object3D* objectBeingRendered;

		glm::mat4 finalTransformation;
	public:
		Renderable3D(Object3D* object);
		Renderable3D(Object3D* object, glm::mat4 transformationMatrix);
		Renderable3D(Object3D* object, glm::mat4 translation, glm::mat4 rotation, glm::mat4 scale);
		~Renderable3D();

		Object3D* GetObject();
		glm::mat4 GetTransformMatrix();
		// this is going to include the same information as an object, except it will also include a
		// reference to the Scene it is coming from which includes lights, camera, etc
	};
}