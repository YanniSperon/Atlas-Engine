#pragma once

#include "New/Rendering/2D/Object/Object2D.h"

namespace Atlas {
	class FramebufferObject : public Object2D {
	private:
		GLuint fbo;
		int width;
		int height;
	public:
		FramebufferObject();
		FramebufferObject(int w, int h, int x, int y);
		void Resize(int w, int h);
		void Bind();
	};
}