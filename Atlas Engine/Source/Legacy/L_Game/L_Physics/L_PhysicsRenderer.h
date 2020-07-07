#pragma once

#include <deque>
#include "L_PhysicsObject.h"
#include "L_PhysicsLight.h"
#include "Legacy/L_Rendering/L_GUI/L_Primitives/L_Object2D.h"
#include "Legacy/L_Game/L_Player.h"

namespace L_Atlas {

	class L_PhysicsRenderer {
	private:
		std::deque<L_PhysicsObject*> renderQueue3D;
		std::deque<L_Object*> renderQueueObject3D;
		std::deque<L_Object2D*> renderQueue2D;
		glm::mat4 projectionMatrix;
		glm::mat4 orthographicMatrix;
		int localWidthBuffer = 0;
		int localHeightBuffer = 0;
	public:
		void Submit2D(L_Object2D* renderable);
		void Submit3D(L_PhysicsObject* renderable, glm::vec3 camPos);
		void Submit3DObject(L_Object* renderable, glm::vec3 camPos);
		void SubmitForceRender3D(L_PhysicsObject* renderable);
		void SubmitForceRender3DObject(L_Object* renderable);
		void SimpleFlush(L_Player* camera, int width, int height, float FOV, L_PhysicsLight* light);
	};
}