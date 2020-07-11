#pragma once

#include "Object2D.h"

namespace Atlas {
	class FramebufferObject {
	private:
		Object2D* object;
		GLuint fbo;
		int width;
		int height;
		int xPos;
		int yPos;
	public:
		FramebufferObject();
		FramebufferObject(int w, int h, int x, int y);
		void Resize(int w, int h);
		void Move(int x, int y);
		void Bind();
	};
}