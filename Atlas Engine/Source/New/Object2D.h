#pragma once

#include "GL/glew.h"
#include "Mesh2D.h"

namespace Atlas {
	class Object2D {
	private:
		GLuint vbo;
		GLuint ibo;
		Mesh2D mesh;
	public:
		Object2D();
		~Object2D();

		void Update(float deltaTime);

		void LoadIntoVRAM();
		void UnloadFromVRAM();
	};
}