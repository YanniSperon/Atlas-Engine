#include "Mesh2DManager.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"
#include "New/Rendering/2D/Object/Object2D.h"
#include "New/System/Console/Console.h"

Atlas::VRAMHandle* Atlas::Mesh2DManager::LoadIntoVRAM(Mesh2D* mesh)
{
	VRAMHandle* handle = new VRAMHandle();
	glGenBuffers(1, &handle->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, handle->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->VertexBufferSize(), mesh->vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));

	glGenBuffers(1, &handle->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexBufferSize(), mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glFinish();
	return handle;
}

void Atlas::Mesh2DManager::UnloadFromVRAM(VRAMHandle* handle)
{
	glDeleteBuffers(1, &handle->vbo);
	glDeleteBuffers(1, &handle->vbo);
}

Atlas::Mesh2DManager::Mesh2DManager()
	: Updatable(60), loadedMeshes(), vramReference()
{

}

Atlas::Mesh2DManager::~Mesh2DManager()
{
	for (auto it : vramReference) {
		UnloadFromVRAM(it.second);
		delete it.second;
	}
	vramReference.clear();

	for (auto it : loadedMeshes) {
		it.second->DeleteMesh();
		delete it.second;
	}
	loadedMeshes.clear();
}

void Atlas::Mesh2DManager::Update(float deltaTime)
{
	Updatable::Update(deltaTime);
	if (Updatable::ShouldUpdate()) {
		for (auto it = loadedMeshes.begin(); it != loadedMeshes.end();) {
			Mesh2D* mesh = it->second;
			if (mesh->referencingObjects.size() == 0) {
				VRAMHandle* ref = vramReference[mesh];
				UnloadFromVRAM(ref);
				vramReference.erase(mesh);
				delete ref;
				mesh->DeleteMesh();
				it = loadedMeshes.erase(it);
				delete mesh;
			}
			else {
				it++;
			}
		}
	}
}

Atlas::Mesh2D* Atlas::Mesh2DManager::LoadMesh(const std::string& filepath)
{
	Mesh2D* tempMesh = nullptr;
	for (auto it : loadedMeshes) {
		if (it.second->filepath == filepath) {
			tempMesh = it.second;
		}
	}
	if (tempMesh) {
		return tempMesh;
	}
	else {
		return GetMesh(MeshGenerator::Generate2D(filepath));
	}
}

Atlas::Mesh2D* Atlas::Mesh2DManager::GetMesh(Mesh2D* mesh)
{
	if (loadedMeshes.find(mesh->name) == loadedMeshes.end()) {
		// doesnt exist
		loadedMeshes[mesh->name] = mesh;
	}
	else {
		// does exist
		int count = 0;
		while (loadedMeshes.find(mesh->name + std::to_string(count)) != loadedMeshes.end()) {
			count++;
		}
		std::string newName = mesh->name + std::to_string(count);
		mesh->name = newName;
		loadedMeshes[newName] = mesh;
	}
	return mesh;
}

void Atlas::Mesh2DManager::Delete(Object* obj)
{
	for (auto it : loadedMeshes) {
		Object2D* obj2d = (Object2D*)obj;
		if (it.second == obj2d->GetMesh()) {
			it.second->referencingObjects.erase(obj);
		}
	}
}

void Atlas::Mesh2DManager::DeleteMesh(const std::string& name)
{
	if (loadedMeshes.find(name) == loadedMeshes.end()) {
		// doesnt exist
		// do nothing
		Console::Warning("Attempting to delete mesh that does not exist");
	}
	else {
		Mesh2D* mesh = loadedMeshes[name];
		VRAMHandle* ref = vramReference[mesh];
		UnloadFromVRAM(ref);
		vramReference.erase(mesh);
		delete ref;
		mesh->DeleteMesh();
		loadedMeshes.erase(mesh->name);
		delete mesh;
	}
}

void Atlas::Mesh2DManager::DeleteMesh(Mesh2D* mesh)
{
	if (loadedMeshes.find(mesh->name) == loadedMeshes.end()) {
		Console::Warning("Attempting to delete unloaded mesh");
	}
	else {
		Mesh2D* mesh = loadedMeshes[mesh->name];
		VRAMHandle* ref = vramReference[mesh];
		UnloadFromVRAM(ref);
		vramReference.erase(mesh);
		delete ref;
		mesh->DeleteMesh();
		loadedMeshes.erase(mesh->name);
		delete mesh;
	}
}

void Atlas::Mesh2DManager::SetMesh(Mesh2D* newMesh)
{
	int count = 0;
	while (loadedMeshes.find(newMesh->name + std::to_string(count)) != loadedMeshes.end()) {
		count++;
	}
	std::string newName = newMesh->name + std::to_string(count);
	newMesh->name = newName;
	loadedMeshes[newName] = newMesh;
	vramReference[newMesh] = LoadIntoVRAM(newMesh);
}

void Atlas::Mesh2DManager::ReplaceMesh(Mesh2D* newMesh)
{
	if (loadedMeshes.find(newMesh->name) == loadedMeshes.end()) {
		// Does not exist
		loadedMeshes[newMesh->name] = newMesh;
		vramReference[newMesh] = LoadIntoVRAM(newMesh);
	}
	else {
		// Does exist
		Mesh2D* mesh = loadedMeshes[newMesh->name];
		VRAMHandle* ref = vramReference[mesh];
		UnloadFromVRAM(ref);
		vramReference.erase(mesh);
		delete ref;
		std::set<Object*> referencingObjects = std::set<Object*>(mesh->referencingObjects);
		mesh->DeleteMesh();
		loadedMeshes.erase(mesh->name);
		delete mesh;

		loadedMeshes[newMesh->name] = newMesh;
		newMesh->referencingObjects = referencingObjects;
		vramReference[newMesh] = LoadIntoVRAM(newMesh);
		for (auto obj : newMesh->referencingObjects) {
			Object2D* obj2d = (Object2D*)obj;
			obj2d->SetMesh(newMesh);
			obj2d->SetVRAMHandle(vramReference[newMesh]);
		}
	}
}

Atlas::VRAMHandle* Atlas::Mesh2DManager::GetVRAMHandle(Mesh2D* mesh)
{
	return vramReference[mesh];
}
