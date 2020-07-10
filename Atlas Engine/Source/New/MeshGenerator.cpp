#include "MeshGenerator.h"
#include <vector>
#include <fstream>
#include <strstream>

Atlas::Mesh3D Atlas::MeshGenerator::CreateCube(const glm::vec3& min, const glm::vec3& max)
{
	Mesh3D cube;

	Vertex3D positions[] = {
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

	cube.numVertices = NUM_ARRAY_ELEMENTS(positions);
	cube.vertices = new Vertex3D[cube.numVertices];
	memcpy(cube.vertices, positions, sizeof(positions));

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
	cube.numIndices = NUM_ARRAY_ELEMENTS(indices);
	cube.indices = new GLuint[cube.numIndices];
	memcpy(cube.indices, indices, sizeof(indices));

	return cube;
}


Atlas::Mesh3D Atlas::MeshGenerator::LoadTexturedShape(const std::string& modelDirAndName)
{

	Mesh3D ret;

	std::vector<Vertex3D> positions;
	std::vector<GLuint> indices;
	std::vector<glm::vec2> tempTex;
	std::vector<glm::vec3> normals;

	std::ifstream obj(modelDirAndName);

	unsigned int positionsSize = 0;
	unsigned int indicesSize = 0;

	if (!obj.is_open()) {
		printf("Invalid file - does not exist! \"%s\"", modelDirAndName.c_str());
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
			Vertex3D vert;
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
			positions.at(f[0] - 1).texCoord = glm::vec2(tempTex.at(uv[0] - 1).x, tempTex.at(uv[0] - 1).y);
			positions.at(f[1] - 1).texCoord = glm::vec2(tempTex.at(uv[1] - 1).x, tempTex.at(uv[1] - 1).y);
			positions.at(f[2] - 1).texCoord = glm::vec2(tempTex.at(uv[2] - 1).x, tempTex.at(uv[2] - 1).y);
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
			glm::vec2 uv;
			uv.x = one;
			uv.y = two;
			tempTex.push_back(uv);
		}
	}
	if (temp == 0) {
		printf("Corrupted file! \"%s\"", modelDirAndName.c_str());
		return ret;
	}

	ret.numVertices = positionsSize;
	ret.vertices = new Vertex3D[positionsSize];
	for (unsigned int i = 0; i < positionsSize; i++) {
		ret.vertices[i] = positions.at(i);
	}

	ret.numIndices = indicesSize;
	ret.indices = new GLuint[indicesSize];
	for (unsigned int k = 0; k < indicesSize; k++) {
		ret.indices[k] = indices.at(k);
	}

	return ret;
}
