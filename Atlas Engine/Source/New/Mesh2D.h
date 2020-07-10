#pragma once

#include "GL/glew.h"
#include "Vertex2D.h"

namespace Atlas {

	struct Mesh2D {

		Mesh2D()
			: vertices(NULL), numVertices(0), indices(NULL), numIndices(0)
		{

		}

		Vertex2D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;

		GLsizeiptr VertexBufferSize() const {
			return numVertices * sizeof(Vertex2D);
		}

		GLsizeiptr IndexBufferSize() const {
			return numIndices * sizeof(GLuint);
		}

		void DeleteMesh() {
			delete[] vertices;
			delete[] indices;
			numVertices = numIndices = 0;
		}
	};
}