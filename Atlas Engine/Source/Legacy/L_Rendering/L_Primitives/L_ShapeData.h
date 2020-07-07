#pragma once

#include <GL/glew.h>
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "L_Vertex.h"

namespace L_Atlas {

	struct L_ShapeData
	{
		L_ShapeData() :
			vertices(0), numVertices(0), indices(0), numIndices(0) {}
		L_Vertex* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;
		glm::vec3 min;
		glm::vec3 max;

		GLsizeiptr vertexBufferSize() const {
			return numVertices * sizeof(L_Vertex);
		}
		GLsizeiptr indexBufferSize() const {
			return numIndices * sizeof(GLuint);
		}


		void cleanUp() {
			delete[] vertices;
			delete[] indices;

			numVertices = numIndices = 0;
		}
	};

	struct L_ShapeData2D
	{
		L_ShapeData2D() :
			vertices(0), numVertices(0), indices(0), numIndices(0) {}
		L_Vertex2D* vertices;
		GLuint numVertices;
		GLuint* indices;
		GLuint numIndices;

		GLsizeiptr vertexBufferSize() const {
			return numVertices * sizeof(L_Vertex2D);
		}
		GLsizeiptr indexBufferSize() const {
			return numIndices * sizeof(GLuint);
		}


		void cleanUp() {
			delete[] vertices;
			delete[] indices;

			numVertices = numIndices = 0;
		}
	};

	struct L_TexCoord {
		float u, v;
	};
}