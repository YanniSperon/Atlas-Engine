#include "L_ShapeGenerator.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "L_Vertex.h"
#include "Legacy/L_System/L_System.h"
#include <fstream>
#include <string>
#include <vector>
#include <strstream>
#include <iostream>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a);

namespace L_Atlas {

	L_ShapeData L_ShapeGenerator::makeCube(const glm::vec3& min, const glm::vec3& max)
	{

		L_ShapeData ret;

		L_Vertex positions[] = {
			glm::vec3(min.x, min.y, min.z), // 0
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),   // normal

			glm::vec3(max.x, min.y, min.z), // 1
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),   // normal

			glm::vec3(max.x, max.y, min.z), // 2
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),   // normal

			glm::vec3(min.x, max.y, min.z), // 3
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),   // normal



			glm::vec3(max.x, min.y, min.z), // 4
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, min.y, max.z), // 5
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 6
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, min.z), // 7
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),    // normal



			glm::vec3(min.x, max.y, min.z), // 8
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, min.z), // 9
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 10
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),    // normal

			glm::vec3(min.x, max.y, max.z), // 11
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),    // normal



			glm::vec3(max.x, min.y, max.z), // 12
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),    // normal

			glm::vec3(min.x, min.y, max.z), // 13
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),    // normal

			glm::vec3(min.x, max.y, max.z), // 14
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 15
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),    // normal



			glm::vec3(min.x, min.y, max.z), // 16
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, min.y, min.z), // 17
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, max.y, min.z), // 18
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, max.y, max.z), // 19
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),   // normal



			glm::vec3(min.x, min.y, max.z), // 20
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),   // normal

			glm::vec3(max.x, min.y, max.z), // 21
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),   // normal

			glm::vec3(max.x, min.y, min.z), // 22
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),   // normal

			glm::vec3(min.x, min.y, min.z), // 23
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f)    // normal
		};

		ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
		ret.vertices = new L_Vertex[ret.numVertices];
		memcpy(ret.vertices, positions, sizeof(positions));

		GLuint indices[] = {
			2, 1, 0, // Front face
			3, 2, 0,

			6, 5, 4, // Right face
			7, 6, 4,

			10, 9, 8, // Top face
			11, 10, 8,

			14, 13, 12, // Back face
			15, 14, 12,

			18, 17, 16, // Left face
			19, 18, 16,

			20, 23, 22, // Bottom face
			21, 20, 22
		};
		ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
		ret.indices = new GLuint[ret.numIndices];
		memcpy(ret.indices, indices, sizeof(indices));

		ret.min = min;
		ret.max = max;

		return ret;
	}

	L_ShapeData L_ShapeGenerator::makeInvertedLightingCube(const glm::vec3& min, const glm::vec3& max)
	{

		L_ShapeData ret;

		L_Vertex positions[] = {
			glm::vec3(min.x, min.y, min.z), // 0
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal

			glm::vec3(max.x, min.y, min.z), // 1
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal

			glm::vec3(max.x, max.y, min.z), // 2
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal

			glm::vec3(min.x, max.y, min.z), // 3
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal



			glm::vec3(max.x, min.y, min.z), // 4
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, min.y, max.z), // 5
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 6
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, min.z), // 7
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal



			glm::vec3(min.x, max.y, min.z), // 8
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, min.z), // 9
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 10
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal

			glm::vec3(min.x, max.y, max.z), // 11
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal



			glm::vec3(max.x, min.y, max.z), // 12
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal

			glm::vec3(min.x, min.y, max.z), // 13
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal

			glm::vec3(min.x, max.y, max.z), // 14
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 15
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal



			glm::vec3(min.x, min.y, max.z), // 16
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, min.y, min.z), // 17
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, max.y, min.z), // 18
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, max.y, max.z), // 19
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal



			glm::vec3(min.x, min.y, max.z), // 20
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),   // normal

			glm::vec3(max.x, min.y, max.z), // 21
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),   // normal

			glm::vec3(max.x, min.y, min.z), // 22
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),   // normal

			glm::vec3(min.x, min.y, min.z), // 23
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f)    // normal
		};

		ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
		ret.vertices = new L_Vertex[ret.numVertices];
		memcpy(ret.vertices, positions, sizeof(positions));

		GLuint indices[] = {
			2, 1, 0, // Front face
			3, 2, 0,

			6, 5, 4, // Right face
			7, 6, 4,

			10, 9, 8, // Top face
			11, 10, 8,

			14, 13, 12, // Back face
			15, 14, 12,

			18, 17, 16, // Left face
			19, 18, 16,

			20, 23, 22, // Bottom face
			21, 20, 22
		};
		ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
		ret.indices = new GLuint[ret.numIndices];
		memcpy(ret.indices, indices, sizeof(indices));

		ret.min = min;
		ret.max = max;

		return ret;
	}

	L_ShapeData L_ShapeGenerator::makeSkybox(const glm::vec3& min, const glm::vec3& max)
	{

		L_ShapeData ret;

		L_Vertex positions[] = {
			glm::vec3(min.x, min.y, min.z), // 0
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal

			glm::vec3(max.x, min.y, min.z), // 1
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal

			glm::vec3(max.x, max.y, min.z), // 2
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal

			glm::vec3(min.x, max.y, min.z), // 3
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, 1.0f),   // normal



			glm::vec3(max.x, min.y, min.z), // 4
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, min.y, max.z), // 5
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 6
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, min.z), // 7
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(-1.0f, 0.0f, 0.0f),    // normal



			glm::vec3(min.x, max.y, min.z), // 8
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, min.z), // 9
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 10
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal

			glm::vec3(min.x, max.y, max.z), // 11
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, -1.0f, 0.0f),    // normal



			glm::vec3(max.x, min.y, max.z), // 12
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal

			glm::vec3(min.x, min.y, max.z), // 13
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal

			glm::vec3(min.x, max.y, max.z), // 14
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal

			glm::vec3(max.x, max.y, max.z), // 15
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 0.0f, -1.0f),    // normal



			glm::vec3(min.x, min.y, max.z), // 16
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, min.y, min.z), // 17
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, max.y, min.z), // 18
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal

			glm::vec3(min.x, max.y, max.z), // 19
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(1.0f, 0.0f, 0.0f),   // normal



			glm::vec3(min.x, min.y, max.z), // 20
			glm::vec2(+0.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),   // normal

			glm::vec3(max.x, min.y, max.z), // 21
			glm::vec2(+1.0f, +0.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),   // normal

			glm::vec3(max.x, min.y, min.z), // 22
			glm::vec2(+1.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f),   // normal

			glm::vec3(min.x, min.y, min.z), // 23
			glm::vec2(+0.0f, +1.0f),        // texCoord
			glm::vec3(0.0f, 1.0f, 0.0f)    // normal
		};

		ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
		ret.vertices = new L_Vertex[ret.numVertices];
		memcpy(ret.vertices, positions, sizeof(positions));

		GLuint indices[] = {
			0, 1, 2, // Front face
			0, 2, 3,

			4, 5, 6, // Right face
			4, 6, 7,

			8, 9, 10, // Top face
			8, 10, 11,

			12, 13, 14, // Back face
			12, 14, 15,

			16, 17, 18, // Left face
			16, 18, 19,

			22, 23, 20, // Bottom face
			22, 20, 21
		};
		ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
		ret.indices = new GLuint[ret.numIndices];
		memcpy(ret.indices, indices, sizeof(indices));

		ret.min = min;
		ret.max = max;

		return ret;
	}

	L_ShapeData L_ShapeGenerator::loadShape(const std::string& fileName)
	{
		glm::vec3 minimums = glm::vec3(INFINITY, INFINITY, INFINITY);
		glm::vec3 maximums = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
		L_ShapeData ret;

		std::vector<L_Vertex> positions;
		std::vector<GLuint> indices;
		std::vector<glm::vec3> normals;

		std::ifstream f(L_System::ConvertFilePathToAbsolute(fileName));

		unsigned int positionsSize = 0;
		unsigned int indicesSize = 0;

		if (!f.is_open()) {
			L_System::Err("Invalid file - does not exist! \"" + L_System::ConvertFilePathToAbsolute(fileName) + "\"");
			return ret;
		}
		int temp = 0;
		while (!f.eof())
		{
			temp++;
			char line[128];
			f.getline(line, 128);

			std::strstream s;
			s << line;

			char junk;
			char slash = '/';

			if (line[0] == 'v' && line[1] == ' ')
			{
				glm::vec3 v;
				s >> junk >> v.x >> v.y >> v.z;
				if (v.x > maximums.x) {
					maximums.x = v.x;
				}
				else if (v.x < minimums.x) {
					minimums.x = v.x;
				}

				if (v.y > maximums.y) {
					maximums.y = v.y;
				}
				else if (v.y < minimums.y) {
					minimums.y = v.y;
				}
				
				if (v.z > maximums.z) {
					maximums.z = v.z;
				}
				else if (v.z < minimums.z) {
					minimums.z = v.z;
				}
				L_Vertex vert;
				vert.position = v;
				positions.push_back(vert);
				positionsSize += 1;
			}
			else if (line[0] == 'v' && line[1] == 'n') {
				glm::vec3 v;
				s >> junk >> junk >> v.x >> v.y >> v.z;
				normals.push_back(v);
			}
			else if (line[0] == 'f')
			{
				unsigned int f[3];
				unsigned int n[3];
				s >> junk >> f[0] >> slash >> slash >> n[0] >> f[1] >> slash >> slash >> n[1] >> f[2] >> slash >> slash >> n[2];
				indices.push_back(f[0] - 1);
				indices.push_back(f[1] - 1);
				indices.push_back(f[2] - 1);
				indicesSize += 3;
				positions.at(f[0] - 1).normal = normals.at(n[0] - 1);
				positions.at(f[1] - 1).normal = normals.at(n[1] - 1);
				positions.at(f[2] - 1).normal = normals.at(n[2] - 1);
			}
		}
		if (temp == 0) {
			L_System::Err("Corrupted file! \"" + L_System::ConvertFilePathToAbsolute(fileName) + "\"");
			return ret;
		}

		ret.numVertices = positionsSize;
		ret.vertices = new L_Vertex[positionsSize];
		for (unsigned int i = 0; i < positionsSize; i++) {
			ret.vertices[i] = positions.at(i);
		}

		ret.numIndices = indicesSize;
		ret.indices = new GLuint[indicesSize];
		for (unsigned int k = 0; k < indicesSize; k++) {
			ret.indices[k] = indices.at(k);
		}
		
		if (minimums.x > -0.01f) {
			minimums.x = -0.01f;
		}
		if (maximums.x < 0.01f) {
			maximums.x = 0.01f;
		}

		if (minimums.y > -0.01f) {
			minimums.y = -0.01f;
		}
		if (maximums.y < 0.01f) {
			maximums.y = 0.01f;
		}

		if (minimums.z > -0.01f) {
			minimums.z = -0.01f;
		}
		if (maximums.z < 0.01f) {
			maximums.z = 0.01f;
		}

		ret.min = minimums;
		ret.max = maximums;

		return ret;
	}

	L_ShapeData L_ShapeGenerator::loadTexturedShape(const std::string& directory, const std::string& name)
	{
		glm::vec3 minimums = glm::vec3(INFINITY, INFINITY, INFINITY);
		glm::vec3 maximums = glm::vec3(-INFINITY, -INFINITY, -INFINITY);

		L_ShapeData ret;

		std::vector<L_Vertex> positions;
		std::vector<GLuint> indices;
		std::vector<L_TexCoord> tempTex;
		std::vector<glm::vec3> normals;

		std::ifstream obj(L_System::ConvertFilePathToAbsolute(directory + name));

		unsigned int positionsSize = 0;
		unsigned int indicesSize = 0;

		if (!obj.is_open()) {
			L_System::Err("Invalid file - does not exist! \"" + L_System::ConvertFilePathToAbsolute(directory + name) + "\"");
			return ret;
		}

		std::string mtlName;
		int temp = 0;
		while (!obj.eof())
		{
			temp++;
			char line[128];
			obj.getline(line, 128);

			std::strstream s;
			s << line;

			std::string str(line);

			char junk;
			char slash = '/';

			// Load materials from mtl file
			/*if (str.find("mtllib") != std::string::npos)
			{
				mtlName = str.substr(str.find("mtllib") + 7);
				std::cout << mtlName << std::endl;
				std::ifstream mtl(mtlName);

				std::string mtlFileName = directory + mtlName;

				bool fileLoadedProperly = true;

				if (!mtl.is_open()) {
					std::cout << "Error loading mtl file: \"" << mtlFileName << "\"\n";
					fileLoadedProperly = false;
				}
				while (!mtl.eof() && fileLoadedProperly)
				{
					char lineMTL[128];
					mtl.getline(lineMTL, 128);

					std::strstream sMTL;
					sMTL << lineMTL;

					std::string str(lineMTL);

					char junk;
					std::cout << "Loaded mtl file and grabbed line: " << lineMTL << "\n";
				}
			}*/
			// finished loading materials from mtl, now scan obj file for information referencing that file.
			//else if (str.find())
			/*else*/ if (line[0] == 'v' && line[1] == ' ')
			{
				glm::vec3 v;
				s >> junk >> v.x >> v.y >> v.z;
				if (v.x > maximums.x) {
					maximums.x = v.x;
				}
				else if (v.x < minimums.x) {
					minimums.x = v.x;
				}

				if (v.y > maximums.y) {
					maximums.y = v.y;
				}
				else if (v.y < minimums.y) {
					minimums.y = v.y;
				}

				if (v.z > maximums.z) {
					maximums.z = v.z;
				}
				else if (v.z < minimums.z) {
					minimums.z = v.z;
				}
				L_Vertex vert;
				vert.position = v;
				positions.push_back(vert);
				positionsSize += 1;
			}
			else if (line[0] == 'v' && line[1] == 'n') {
				glm::vec3 v;
				s >> junk >> junk >> v.x >> v.y >> v.z;
				normals.push_back(v);
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{
				unsigned int f[3];
				unsigned int uv[3];
				unsigned int n[3];

				s >> junk >> f[0] >> slash >> uv[0] >> slash >> n[0] >> f[1] >> slash >> uv[1] >> slash >> n[1] >> f[2] >> slash >> uv[2] >> slash >> n[2];
				indices.push_back(f[0] - 1);
				indices.push_back(f[1] - 1);
				indices.push_back(f[2] - 1);
				indicesSize += 3;
				positions.at(f[0] - 1).texCoord = glm::vec2(tempTex.at(uv[0] - 1).u, tempTex.at(uv[0] - 1).v);
				positions.at(f[1] - 1).texCoord = glm::vec2(tempTex.at(uv[1] - 1).u, tempTex.at(uv[1] - 1).v);
				positions.at(f[2] - 1).texCoord = glm::vec2(tempTex.at(uv[2] - 1).u, tempTex.at(uv[2] - 1).v);
				positions.at(f[0] - 1).normal = normals.at(n[0] - 1);
				positions.at(f[1] - 1).normal = normals.at(n[1] - 1);
				positions.at(f[2] - 1).normal = normals.at(n[2] - 1);
			}
			else if (line[0] == 'v' && line[1] == 't') {
				float one;
				float two;
				std::string name;
				s >> name;
				s >> one;
				s >> two;
				L_TexCoord uv;
				uv.u = one;
				uv.v = two;
				tempTex.push_back(uv);
			}
		}
		if (temp == 0) {
			L_System::Err("Corrupted file! \"" + L_System::ConvertFilePathToAbsolute(directory + name) + "\"");
			return ret;
		}

		ret.numVertices = positionsSize;
		ret.vertices = new L_Vertex[positionsSize];
		for (unsigned int i = 0; i < positionsSize; i++) {
			ret.vertices[i] = positions.at(i);
		}

		ret.numIndices = indicesSize;
		ret.indices = new GLuint[indicesSize];
		for (unsigned int k = 0; k < indicesSize; k++) {
			ret.indices[k] = indices.at(k);
		}

		if (minimums.x > -0.01f) {
			minimums.x = -0.01f;
		}
		if (maximums.x < 0.01f) {
			maximums.x = 0.01f;
		}

		if (minimums.y > -0.01f) {
			minimums.y = -0.01f;
		}
		if (maximums.y < 0.01f) {
			maximums.y = 0.01f;
		}

		if (minimums.z > -0.01f) {
			minimums.z = -0.01f;
		}
		if (maximums.z < 0.01f) {
			maximums.z = 0.01f;
		}

		ret.max = maximums;
		ret.min = minimums;

		return ret;
	}

	L_ShapeData2D L_ShapeGenerator::makeSquare(const glm::vec2& min, const glm::vec2& max, const glm::vec2& minTexCoords, const glm::vec2& maxTexCoords)
	{
		L_ShapeData2D ret;

		L_Vertex2D positions[] = {
			glm::vec2(min.x, min.y), // 0
			glm::vec2(minTexCoords.x, minTexCoords.y),        // texCoord

			glm::vec2(max.x, min.y), // 1
			glm::vec2(maxTexCoords.x, minTexCoords.y),        // texCoord

			glm::vec2(max.x, max.y), // 2
			glm::vec2(maxTexCoords.x, maxTexCoords.y),        // texCoord

			glm::vec2(min.x, max.y), // 3
			glm::vec2(minTexCoords.x, maxTexCoords.y),        // texCoord
		};

		ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
		ret.vertices = new L_Vertex2D[ret.numVertices];
		memcpy(ret.vertices, positions, sizeof(positions));

		GLuint indices[] = {
			0, 1, 2, // Front face
			0, 2, 3,
		};

		ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
		ret.indices = new GLuint[ret.numIndices];
		memcpy(ret.indices, indices, sizeof(indices));

		return ret;
	}
}