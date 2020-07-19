#pragma once

#include "GL/glew.h"
#include "Vertex2D.h"
#include <set>
#include <string>

namespace Atlas {

	struct Mesh2D {

		Mesh2D()
			: vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0), name("default"), referencingObjects()
		{

		}

		Vertex2D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;
		std::string name;

		std::set<void*> referencingObjects;

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