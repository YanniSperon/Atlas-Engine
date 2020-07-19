#pragma once

#include "GL/glew.h"

namespace Atlas {
	struct VRAMHandle {
		VRAMHandle()
			: vbo(0), ibo(0), referencingMesh()
		{

		}
		GLuint vbo;
		GLuint ibo;
		void* referencingMesh;

		void DeleteFromVRAM() {
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
		}
	};
}