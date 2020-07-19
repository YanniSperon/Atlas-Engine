#pragma once

#include "GL/glew.h"
#include "Vertex3D.h"
#include <string>
#include <vector>

namespace Atlas {

	struct Mesh3D {

		Mesh3D()
			: vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0), name(""), referencingObjects(), vramHandle(nullptr)
		{

		}

		Vertex3D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;
		std::string name;
		//        object3d
		std::vector<void*> referencingObjects;

		void* vramHandle;

		GLsizeiptr VertexBufferSize() const {
			return numVertices * sizeof(Vertex3D);
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