#include "MeshGenerator.h"
#include <vector>
#include <fstream>
#include <strstream>
#include "New/System/Global/Global.h"

Atlas::Mesh3D* Atlas::MeshGenerator::CreateCube(const glm::vec3& min, const glm::vec3& max)
{
	Mesh3D* cube = new Mesh3D();

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

	cube->numVertices = NUM_ARRAY_ELEMENTS(positions);
	cube->vertices = new Vertex3D[cube->numVertices];
	memcpy(cube->vertices, positions, sizeof(positions));

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
	cube->numIndices = NUM_ARRAY_ELEMENTS(indices);
	cube->indices = new GLuint[cube->numIndices];
	memcpy(cube->indices, indices, sizeof(indices));

	cube->name = "cube";

	return cube;
}

Atlas::Mesh3D* Atlas::MeshGenerator::CreateSkybox()
{
	Mesh3D* cube = new Mesh3D();

	Vertex3D positions[] = {
		glm::vec3(-1.0f, -1.0f, -1.0f),   // 0 -- 9/1/1
		glm::vec2(+0.25f, +0.25f),        // texCoord
		glm::vec3(+1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(-1.0f, +1.0f, +1.0f),   // 1 -- 13/2/1
		glm::vec2(+0.5f, +0.0f),          // texCoord
		glm::vec3(+1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(-1.0f, -1.0f, +1.0f),   // 2 -- 11/3/1
		glm::vec2(+0.25f, +0.0f),         // texCoord
		glm::vec3(+1.0f, +0.0f, +0.0f),   // normal



		glm::vec3(+1.0f, -1.0f, -1.0f),   // 3 -- 17/4/2
		glm::vec2(+0.25f, +0.5f),         // texCoord
		glm::vec3(+0.0f, +0.0f, +1.0f),   // normal

		glm::vec3(-1.0f, +1.0f, -1.0f),   // 4 -- 16/5/2
		glm::vec2(+0.5f, +0.25f),         // texCoord
		glm::vec3(+0.0f, +0.0f, +1.0f),   // normal

		glm::vec3(-1.0f, -1.0f, -1.0f),   // 5 -- 10/6/2
		glm::vec2(+0.25f, +0.25f),        // texCoord
		glm::vec3(+0.0f, +0.0f, +1.0f),   // normal



		glm::vec3(+1.0f, -1.0f, +1.0f),   // 6 -- 21/7/3
		glm::vec2(+0.25f, +0.75f),        // texCoord
		glm::vec3(-1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(+1.0f, +1.0f, -1.0f),   // 7 -- 20/8/3
		glm::vec2(+0.5f, +0.5f),          // texCoord
		glm::vec3(-1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(+1.0f, -1.0f, -1.0f),   // 8 -- 18/9/3
		glm::vec2(+0.25f, +0.5f),         // texCoord
		glm::vec3(-1.0f, +0.0f, +0.0f),   // normal



		glm::vec3(-1.0f, -1.0f, +1.0f),   // 9 -- 12/10/4
		glm::vec2(+0.25f, +1.0f),         // texCoord
		glm::vec3(+0.0f, +0.0f, -1.0f),   // normal

		glm::vec3(+1.0f, +1.0f, +1.0f),   // 10 -- 24/11/4
		glm::vec2(+0.5f, +0.75f),         // texCoord
		glm::vec3(+0.0f, +0.0f, -1.0f),   // normal

		glm::vec3(+1.0f, -1.0f, +1.0f),   // 11 -- 22/12/4
		glm::vec2(+0.25f, +0.75f),        // texCoord
		glm::vec3(+0.0f, +0.0f, -1.0f),   // normal



		glm::vec3(-1.0f, -1.0f, +1.0f),   // 12 -- 1/13/5
		glm::vec2(+0.0f, +0.75f),         // texCoord
		glm::vec3(+0.0f, +1.0f, +0.0f),   // normal

		glm::vec3(+1.0f, -1.0f, -1.0f),   // 13 -- 7/14/5
		glm::vec2(+0.25f, +0.5f),         // texCoord
		glm::vec3(+0.0f, +1.0f, +0.0f),   // normal

		glm::vec3(-1.0f, -1.0f, -1.0f),   // 14 -- 3/15/5
		glm::vec2(+0.0f, +0.5f),          // texCoord
		glm::vec3(+0.0f, +1.0f, +0.0f),   // normal



		glm::vec3(+1.0f, +1.0f, +1.0f),   // 15 -- 6/16/6
		glm::vec2(+0.5f, +0.75f),         // texCoord
		glm::vec3(+0.0f, -1.0f, +0.0f),   // normal

		glm::vec3(-1.0f, +1.0f, -1.0f),   // 16 -- 4/17/6
		glm::vec2(+0.75f, +0.5f),         // texCoord
		glm::vec3(+0.0f, -1.0f, +0.0f),   // normal

		glm::vec3(+1.0f, +1.0f, -1.0f),   // 17 -- 8/18/6
		glm::vec2(+0.5f, +0.5f),          // texCoord
		glm::vec3(+0.0f, -1.0f, +0.0f),   // normal



		glm::vec3(-1.0f, -1.0f, -1.0f),   // 18 -- 9/1/1
		glm::vec2(+0.25f, +0.25f),        // texCoord
		glm::vec3(+1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(-1.0f, +1.0f, -1.0f),   // 19 -- 15/19/1
		glm::vec2(+0.5f, +0.25f),         // texCoord
		glm::vec3(+1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(-1.0f, +1.0f, +1.0f),   // 20 -- 13/2/1
		glm::vec2(+0.5f, +0.0f),          // texCoord
		glm::vec3(+1.0f, +0.0f, +0.0f),   // normal



		glm::vec3(+1.0f, -1.0f, -1.0f),   // 21 -- 17/4/2
		glm::vec2(+0.25f, +0.5f),         // texCoord
		glm::vec3(+0.0f, +0.0f, +1.0f),   // normal

		glm::vec3(+1.0f, +1.0f, -1.0f),   // 22 -- 19/20/2
		glm::vec2(+0.5f, +0.5f),          // texCoord
		glm::vec3(+0.0f, +0.0f, +1.0f),   // normal

		glm::vec3(-1.0f, +1.0f, -1.0f),   // 23 -- 16/5/2
		glm::vec2(+0.5f, +0.25f),          // texCoord
		glm::vec3(+0.0f, +0.0f, +1.0f),   // normal



		glm::vec3(+1.0f, -1.0f, +1.0f),   // 24 -- 21/7/3
		glm::vec2(+0.25f, +0.75f),          // texCoord
		glm::vec3(-1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(+1.0f, +1.0f, +1.0f),   // 25 -- 23/21/3
		glm::vec2(+0.5f, +0.75f),         // texCoord
		glm::vec3(-1.0f, +0.0f, +0.0f),   // normal

		glm::vec3(+1.0f, +1.0f, -1.0f),   // 26 -- 20/8/3
		glm::vec2(+0.5f, +0.5f),          // texCoord
		glm::vec3(-1.0f, +0.0f, +0.0f),   // normal



		glm::vec3(-1.0f, -1.0f, +1.0f),   // 27 -- 12/10/4
		glm::vec2(+0.25f, +1.0f),         // texCoord
		glm::vec3(+0.0f, +0.0f, -1.0f),   // normal

		glm::vec3(-1.0f, +1.0f, +1.0f),   // 28 -- 14/22/4
		glm::vec2(+0.5f, +1.0f),          // texCoord
		glm::vec3(+0.0f, +0.0f, -1.0f),   // normal

		glm::vec3(+1.0f, +1.0f, +1.0f),   // 29 -- 24/11/4
		glm::vec2(+0.5f, +0.75f),         // texCoord
		glm::vec3(+0.0f, +0.0f, -1.0f),   // normal



		glm::vec3(-1.0f, -1.0f, +1.0f),   // 30 -- 1/13/5
		glm::vec2(+0.0f, +0.75f),         // texCoord
		glm::vec3(+0.0f, +1.0f, +0.0f),   // normal

		glm::vec3(+1.0f, -1.0f, +1.0f),   // 31 -- 5/23/5
		glm::vec2(+0.25f, +0.75f),        // texCoord
		glm::vec3(+0.0f, +1.0f, +0.0f),   // normal

		glm::vec3(+1.0f, -1.0f, -1.0f),   // 32 -- 7/14/5
		glm::vec2(+0.25f, +0.5f),         // texCoord
		glm::vec3(+0.0f, +1.0f, +0.0f),   // normal



		glm::vec3(+1.0f, +1.0f, +1.0f),   // 33 -- 6/16/6
		glm::vec2(+0.5f, +0.75f),         // texCoord
		glm::vec3(+0.0f, -1.0f, +0.0f),   // normal

		glm::vec3(-1.0f, +1.0f, +1.0f),   // 34 -- 2/24/6
		glm::vec2(+0.75f, +0.75f),        // texCoord
		glm::vec3(+0.0f, -1.0f, +0.0f),   // normal

		glm::vec3(-1.0f, +1.0f, -1.0f),   // 35 -- 4/17/6
		glm::vec2(+0.75f, +0.5f),         // texCoord
		glm::vec3(+0.0f, -1.0f, +0.0f),   // normal
	};

	cube->numVertices = NUM_ARRAY_ELEMENTS(positions);
	cube->vertices = new Vertex3D[cube->numVertices];
	memcpy(cube->vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2,
		3, 4, 5,

		6, 7, 8,
		9, 10, 11,

		12, 13, 14,
		15, 16, 17,

		18, 19, 20,
		21, 22, 23,

		24, 25, 26,
		27, 28, 29,

		30, 31, 32,
		33, 34, 35
	};
	cube->numIndices = NUM_ARRAY_ELEMENTS(indices);
	cube->indices = new GLuint[cube->numIndices];
	memcpy(cube->indices, indices, sizeof(indices));

	cube->name = "skybox";

	return cube;
}

Atlas::Mesh3D* Atlas::MeshGenerator::LoadTexturedShape(const std::string& modelDirAndName)
{

	Mesh3D* ret = new Mesh3D();

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

	ret->numVertices = positionsSize;
	ret->vertices = new Vertex3D[positionsSize];
	for (unsigned int i = 0; i < positionsSize; i++) {
		ret->vertices[i] = positions.at(i);
	}

	ret->numIndices = indicesSize;
	ret->indices = new GLuint[indicesSize];
	for (unsigned int k = 0; k < indicesSize; k++) {
		ret->indices[k] = indices.at(k);
	}

	ret->name = modelDirAndName;

	return ret;
}

Atlas::Mesh3D* Atlas::MeshGenerator::Generate(const std::string& name)
{
	if (name == "cube") {
		return CreateCube(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
	}
	else if (name == "skybox") {
		return CreateSkybox();
	}
	else {
		return LoadTexturedShape(name);
	}
}

Atlas::Mesh2D* Atlas::MeshGenerator::CreateSquare()
{
	Mesh2D* ret = new Mesh2D();

	Vertex2D positions[] = {
		glm::vec2(0.0f, 0.0f), // 0
		glm::vec2(0.0f, 0.0f), // texCoord

		glm::vec2(1.0f, 0.0f), // 1
		glm::vec2(1.0f, 0.0f), // texCoord

		glm::vec2(1.0f, 1.0f), // 2
		glm::vec2(1.0f, 1.0f), // texCoord

		glm::vec2(0.0f, 1.0f), // 3
		glm::vec2(0.0f, 1.0f), // texCoord
	};

	ret->numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret->vertices = new Vertex2D[ret->numVertices];
	memcpy(ret->vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Right Face  | /|
		0, 2, 3, // Left Face   |/_|
	};

	ret->numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret->indices = new GLuint[ret->numIndices];
	memcpy(ret->indices, indices, sizeof(indices));

	return ret;
}

Atlas::Mesh2D* Atlas::MeshGenerator::CreateSquareCustom(const glm::vec2& minPos, const glm::vec2& maxPos, const glm::vec2& minTexCoord, const glm::vec2& maxTexCoord)
{
	Mesh2D* ret = new Mesh2D();

	Vertex2D positions[] = {
		glm::vec2(minPos.x, minPos.y), // 0
		glm::vec2(minTexCoord.x, minTexCoord.y), // texCoord

		glm::vec2(maxPos.x, minPos.y), // 1
		glm::vec2(maxTexCoord.x, minTexCoord.y), // texCoord

		glm::vec2(maxPos.x, maxPos.y), // 2
		glm::vec2(maxTexCoord.x, maxTexCoord.y), // texCoord

		glm::vec2(minPos.x, maxPos.y), // 3
		glm::vec2(minTexCoord.x, maxTexCoord.y), // texCoord
	};

	ret->numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret->vertices = new Vertex2D[ret->numVertices];
	memcpy(ret->vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Right Face  | /|
		0, 2, 3, // Left Face   |/_|
	};

	ret->numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret->indices = new GLuint[ret->numIndices];
	memcpy(ret->indices, indices, sizeof(indices));

	return ret;
}

Atlas::Mesh2D* Atlas::MeshGenerator::CreateSquareFixedSize(const glm::vec2& minTexCoord, const glm::vec2& maxTexCoord)
{
	Mesh2D* ret = new Mesh2D();

	Vertex2D positions[] = {
		glm::vec2(0.0f, 0.0f), // 0
		glm::vec2(minTexCoord.x, minTexCoord.y), // texCoord

		glm::vec2((float)Global::Variables.screenWidth, 0.0f), // 1
		glm::vec2(maxTexCoord.x, minTexCoord.y), // texCoord

		glm::vec2((float)Global::Variables.screenWidth, (float)Global::Variables.screenHeight), // 2
		glm::vec2(maxTexCoord.x, maxTexCoord.y), // texCoord

		glm::vec2(0.0f, (float)Global::Variables.screenHeight), // 3
		glm::vec2(minTexCoord.x, maxTexCoord.y), // texCoord
	};

	ret->numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret->vertices = new Vertex2D[ret->numVertices];
	memcpy(ret->vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Right Face  | /|
		0, 2, 3, // Left Face   |/_|
	};

	ret->numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret->indices = new GLuint[ret->numIndices];
	memcpy(ret->indices, indices, sizeof(indices));

	return ret;
}

Atlas::Mesh2D* Atlas::MeshGenerator::CreateScreenSizedSquare()
{
	Mesh2D* ret = new Mesh2D();

	Vertex2D positions[] = {
		glm::vec2(0.0f, 0.0f), // 0
		glm::vec2(0.0f, 0.0f), // texCoord

		glm::vec2((float)Global::Variables.screenWidth, 0.0f), // 1
		glm::vec2(1.0f, 0.0f), // texCoord

		glm::vec2((float)Global::Variables.screenWidth, (float)Global::Variables.screenHeight), // 2
		glm::vec2(1.0f, 1.0f), // texCoord

		glm::vec2(0.0f, (float)Global::Variables.screenHeight), // 3
		glm::vec2(0.0f, 1.0f), // texCoord
	};

	ret->numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret->vertices = new Vertex2D[ret->numVertices];
	memcpy(ret->vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Right Face  | /|
		0, 2, 3, // Left Face   |/_|
	};

	ret->numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret->indices = new GLuint[ret->numIndices];
	memcpy(ret->indices, indices, sizeof(indices));

	return ret;
}