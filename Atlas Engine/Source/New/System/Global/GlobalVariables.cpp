#include "GlobalVariables.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"

Atlas::GlobalVariables::GlobalVariables()
{
	// Initialize default values

	consoleLog = std::vector<std::string>();
	systemStartTime = std::chrono::high_resolution_clock::now();
	screenWidth = 1920;
	screenHeight = 1080;

	keyIn = Input::KeyboardInput();
	mouseIn = Input::MouseInput();

	window = nullptr;
}

Atlas::VRAMHandle* Atlas::GlobalVariables::Load3DMeshToVRAM(const std::string& name)
{
	if (loadedMeshes.find(name) != loadedMeshes.end()) {
		// does exist
		if (vramReference3D.find(loadedMeshes[name]) == vramReference3D.end()) {
			// doesnt exist
			VRAMHandle* returnValue = new VRAMHandle();
			Mesh3D* mesh = loadedMeshes[name];
			vramReference3D[mesh] = returnValue;
			returnValue->referencingMesh = (void*)mesh;
			mesh->vramHandle = (void*)returnValue;

			glGenBuffers(1, &returnValue->vbo);
			glBindBuffer(GL_ARRAY_BUFFER, returnValue->vbo);
			glBufferData(GL_ARRAY_BUFFER, mesh->VertexBufferSize(), mesh->vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));

			glGenBuffers(1, &returnValue->ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, returnValue->ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexBufferSize(), mesh->indices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glFinish();
			return returnValue;
		}
		else {
			return vramReference3D[loadedMeshes[name]];
		}
	}
}

Atlas::Mesh3D* Atlas::GlobalVariables::GetLoadedMesh(const std::string& name)
{
	if (loadedMeshes.find(name) == loadedMeshes.end()) {
		// doesn't exist
		loadedMeshes[name] = MeshGenerator::Generate(name);
		return loadedMeshes[name];
	}
	else {
		return loadedMeshes[name];
	}
}

Atlas::Shader* Atlas::GlobalVariables::GetLoadedShader(const std::string& name)
{
	if (loadedShaders.find(name) == loadedShaders.end()) {
		// doesn't exist
		loadedShaders[name] = new Shader(name);
		return loadedShaders[name];
	}
	else {
		return loadedShaders[name];
	}
}

Atlas::Texture* Atlas::GlobalVariables::GetLoadedTexture(const std::string& name)
{
	if (loadedTextures.find(name) == loadedTextures.end()) {
		// doesn't exist
		loadedTextures[name] = new Texture(name);
		return loadedTextures[name];
	}
	else {
		return loadedTextures[name];
	}
}

Atlas::VRAMHandle* Atlas::GlobalVariables::GetVRAMReference(Mesh3D* mesh)
{
	VRAMHandle* returnValue;
	if (vramReference3D.find(mesh) == vramReference3D.end()) {
		// doesn't exist
		returnValue = new VRAMHandle();
		vramReference3D[mesh] = returnValue;
		returnValue->referencingMesh = (void*)mesh;
		mesh->vramHandle = (void*)returnValue;

		glGenBuffers(1, &returnValue->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, returnValue->vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh->VertexBufferSize(), mesh->vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));

		glGenBuffers(1, &returnValue->ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, returnValue->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexBufferSize(), mesh->indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glFinish();
	}
	else {
		// does exist
		returnValue = vramReference3D[mesh];
	}
	
	if (loadedMeshes.find(mesh->name) == loadedMeshes.end()) {
		// doesn't exist
		loadedMeshes[mesh->name] = mesh;
	}
	else {
		// does exist
		if (loadedMeshes[mesh->name] != mesh) {
			// different meshes
			Mesh3D* originalMesh = loadedMeshes[mesh->name];
			vramReference3D[originalMesh]->DeleteFromVRAM();
			if (vramReference3D.find(originalMesh) != vramReference3D.end()) {
				vramReference3D.erase(originalMesh);
			}
			for (int i = 0; i < originalMesh->referencingObjects.size(); i++) {
				Object3D* referencingObject = (Object3D*)originalMesh->referencingObjects.at(i);
				referencingObject->SetVRAMHandle(returnValue);
				referencingObject->SetMesh(mesh);
			}
			originalMesh->DeleteMesh();
			if (loadedMeshes.find(mesh->name) != loadedMeshes.end()) {
				loadedMeshes.erase(mesh->name);
			}
			delete originalMesh;
			loadedMeshes[mesh->name] = mesh;
		}
	}
	return returnValue;
}

Atlas::VRAMHandle* Atlas::GlobalVariables::GetVRAMReference(Mesh2D* mesh)
{
	VRAMHandle* returnValue;
	if (vramReference2D.find(mesh) == vramReference2D.end()) {
		// doesn't exist
		returnValue = new VRAMHandle();
		vramReference2D[mesh] = returnValue;
		returnValue->referencingMesh = (void*)mesh;
		mesh->vramHandle = (void*)returnValue;

		glGenBuffers(1, &returnValue->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, returnValue->vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh->VertexBufferSize(), mesh->vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));

		glGenBuffers(1, &returnValue->ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, returnValue->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexBufferSize(), mesh->indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glFinish();
	}
	else {
		// does exist
		returnValue = vramReference2D[mesh];
	}
}

Atlas::Mesh3D* Atlas::GlobalVariables::PrepareMesh3D(Mesh3D* mesh, Object3D* sender)
{
	if (loadedMeshes.find(mesh->name) == loadedMeshes.end()) {
		// doesnt exist
		loadedMeshes[mesh->name] = mesh;
	}
	mesh->AddReference(sender);
	return mesh;
}

Atlas::Shader* Atlas::GlobalVariables::PrepareShader(Shader* shader, Object3D* sender)
{
	if (loadedShaders.find(shader->GetName()) == loadedShaders.end()) {
		// doesnt exist
		loadedShaders[shader->GetName()] = shader;
	}
	shader->AddReference(sender);
}

Atlas::Texture* Atlas::GlobalVariables::PrepareTexture(Texture* texture, Object3D* sender)
{
	if (loadedTextures.find(texture->GetName()) == loadedTextures.end()) {
		// doesnt exist
		loadedTextures[texture->GetName()] = texture;
	}
	texture->AddReference(sender);
	return texture;
}

Atlas::Shader* Atlas::GlobalVariables::PrepareShader(Shader* shader, Object2D* sender)
{
	if (loadedShaders.find(shader->GetName()) == loadedShaders.end()) {
		// doesnt exist
		loadedShaders[shader->GetName()] = shader;
	}
	shader->AddReference(sender);
	return shader;
}

Atlas::Texture* Atlas::GlobalVariables::PrepareTexture(Texture* texture, Object2D* sender)
{
	if (loadedTextures.find(texture->GetName()) == loadedTextures.end()) {
		// doesnt exist
		loadedTextures[texture->GetName()] = texture;
	}
	texture->AddReference(sender);
	return texture;
}
