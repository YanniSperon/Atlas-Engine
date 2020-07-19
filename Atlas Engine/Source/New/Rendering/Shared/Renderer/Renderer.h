#pragma once

#include <deque>
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "New/Rendering/3D/Object/Object3D.h"
#include "New/Rendering/2D/Object/Object2D.h"
#include "New/Rendering/2D/Text/Text.h"

namespace Atlas {
	class Renderer {
	private:
		std::deque<Object3D*> renderQueue3D;
		std::deque<Object2D*> renderQueue2D;
		std::deque<Text*> renderQueueText;
	public:
		static void ClearFramebuffer(glm::vec4 clearColor);
		static void SwapFramebuffer();

		Renderer();
		~Renderer();

		void AddObject3D(Object3D* obj);
		void AddObject2D(Object2D* obj);
		void AddText(Text* txt);

		void Flush2D(glm::mat4 orthoMatrix);
		void Flush3D(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	};
}