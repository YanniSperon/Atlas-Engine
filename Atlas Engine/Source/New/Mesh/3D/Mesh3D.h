#pragma once

#include "GL/glew.h"
#include "Vertex3D.h"
#include "New/Rendering/Shared/Object/Object.h"
#include <string>
#include <set>

namespace Atlas {

	struct Mesh3D {

		Mesh3D()
			: vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0), name("default"), referencingObjects()
		{

		}

		Vertex3D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;
		std::string name;

		std::set<Object*> referencingObjects;

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