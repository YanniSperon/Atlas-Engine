#pragma once

#include <deque>
#include "L_Renderer.h"

namespace L_Atlas {

	class L_SimpleRenderer : public L_Renderer {
	private:
		std::deque<L_Object*> renderQueue3D;
		std::deque<L_Object2D*> renderQueue2D;
		std::deque<L_Sentence*> renderQueueText;
		glm::mat4 projectionMatrix;
		glm::mat4 orthographicMatrix;
		int localWidthBuffer = 0;
		int localHeightBuffer = 0;
	public:
		void SubmitText(L_Sentence* renderable) override;
		void Submit2D(L_Object2D* renderable) override;
		void Submit3D(L_Object* renderable, glm::vec3 camPos) override;
		void SubmitForceRender3D(L_Object* renderable) override;
		//void Flush(Camera* camera, int width, int height, float FOV) override;
		//void Flush(Camera* camera, int width, int height, float FOV, L_Light* light) override;
		//void SimpleFlush(Camera* camera, int width, int height, float FOV) override;
		void SimpleFlush(L_Camera* camera, int width, int height, float FOV, L_Light* light) override;
	};
}