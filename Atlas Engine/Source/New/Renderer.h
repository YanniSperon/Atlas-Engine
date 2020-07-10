#pragma once

#include <deque>
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "Renderable3D.h"
#include "Renderable2D.h"
#include "RenderableText.h""

namespace Atlas {
	class Renderer {
	private:
		std::deque<Renderable3D> renderQueue3D;
		std::deque<Renderable2D> renderQueue2D;
		std::deque<RenderableText> renderQueueText;
	public:
		static void ClearFramebuffer(glm::vec4 clearColor);
		static void SwapFramebuffer();

		Renderer();
		~Renderer();

		void AddRenderable3D(const Renderable3D& renderable);
		void AddRenderable2D(const Renderable2D& renderable);
		void AddRenderableText(const RenderableText& renderable);

		void Flush(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	};
}