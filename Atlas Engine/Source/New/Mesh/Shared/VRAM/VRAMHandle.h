#pragma once

#include "GL/glew.h"

namespace Atlas {
	struct VRAMHandle {
		VRAMHandle()
			: vbo(0), ibo(0)
		{

		}
		GLuint vbo;
		GLuint ibo;
	};
}