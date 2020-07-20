#include "Mesh3DManager.h"
#include "New/Rendering/3D/Object/Object3D.h"
#include "New/System/Console/Console.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"

Atlas::VRAMHandle* Atlas::Mesh3DManager::LoadIntoVRAM(Mesh3D* mesh)
{
	VRAMHandle* handle = new VRAMHandle();
	glGenBuffers(1, &handle->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, handle->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->VertexBufferSize(), mesh->vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));

	glGenBuffers(1, &handle->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexBufferSize(), mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glFinish();
	return handle;
}

void Atlas::Mesh3DManager::UnloadFromVRAM(VRAMHandle* handle)
{
	glDeleteBuffers(1, &handle->vbo);
	glDeleteBuffers(1, &handle->vbo);
}

Atlas::Mesh3DManager::Mesh3DManager()
	: Updatable(60), loadedMeshes(), vramReference()
{
	
}

Atlas::Mesh3DManager::~Mesh3DManager()
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

void Atlas::Mesh3DManager::Update(float deltaTime)
{
	Updatable::Update(deltaTime);
	if (Updatable::ShouldUpdate()) {
		for (auto it = loadedMeshes.begin(); it != loadedMeshes.end();) {
			Mesh3D* mesh = it->second;
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

Atlas::Mesh3D* Atlas::Mesh3DManager::LoadMesh(const std::string& filepath)
{
	Mesh3D* tempMesh = nullptr;
	for (auto it : loadedMeshes) {
		if (it.second->filepath == filepath) {
			tempMesh = it.second;
		}
	}
	if (tempMesh) {
		return tempMesh;
	}
	else {
		Mesh3D* mesh = MeshGenerator::Generate3D(filepath);
		return GetMesh(mesh);
	}
}

Atlas::Mesh3D* Atlas::Mesh3DManager::GetMesh(Mesh3D* mesh)
{
	if (loadedMeshes.find(mesh->name) == loadedMeshes.end()) {
		// doesnt exist
		loadedMeshes[mesh->name] = mesh;
		vramReference[mesh] = LoadIntoVRAM(mesh);
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
		vramReference[mesh] = LoadIntoVRAM(mesh);
	}
	return mesh;
}

void Atlas::Mesh3DManager::DeleteReference(Object* obj)
{
	for (auto it : loadedMeshes) {
		Object3D* obj3d = (Object3D*)obj;
		if (it.second == obj3d->GetMesh()) {
			it.second->referencingObjects.erase(obj);
		}
	}
}

void Atlas::Mesh3DManager::AddReference(Object* obj)
{
	Object3D* obj3d = (Object3D*)obj;
	obj3d->GetMesh()->referencingObjects.insert(obj);
}

void Atlas::Mesh3DManager::DeleteMesh(const std::string& name)
{
	if (loadedMeshes.find(name) == loadedMeshes.end()) {
		// doesnt exist
		// do nothing
		Console::Warning("Attempting to delete mesh that does not exist");
	}
	else {
		Mesh3D* mesh = loadedMeshes[name];
		VRAMHandle* ref = vramReference[mesh];
		UnloadFromVRAM(ref);
		vramReference.erase(mesh);
		delete ref;
		mesh->DeleteMesh();
		loadedMeshes.erase(mesh->name);
		delete mesh;
	}
}

void Atlas::Mesh3DManager::DeleteMesh(Mesh3D* mesh)
{
	if (loadedMeshes.find(mesh->name) == loadedMeshes.end()) {
		Console::Warning("Attempting to delete unloaded mesh");
	}
	else {
		Mesh3D* mesh = loadedMeshes[mesh->name];
		VRAMHandle* ref = vramReference[mesh];
		UnloadFromVRAM(ref);
		vramReference.erase(mesh);
		delete ref;
		mesh->DeleteMesh();
		loadedMeshes.erase(mesh->name);
		delete mesh;
	}
}

void Atlas::Mesh3DManager::SetMesh(Mesh3D* newMesh)
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

void Atlas::Mesh3DManager::ReplaceMesh(Mesh3D* newMesh)
{
	if (loadedMeshes.find(newMesh->name) == loadedMeshes.end()) {
		// Does not exist
		loadedMeshes[newMesh->name] = newMesh;
		vramReference[newMesh] = LoadIntoVRAM(newMesh);
	}
	else {
		// Does exist
		Mesh3D* mesh = loadedMeshes[newMesh->name];
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
			Object3D* obj3d = (Object3D*)obj;
			obj3d->SetMesh(newMesh);
			obj3d->SetVRAMHandle(vramReference[newMesh]);
		}
	}
}

Atlas::VRAMHandle* Atlas::Mesh3DManager::GetVRAMHandle(Mesh3D* mesh)
{
	return vramReference[mesh];
}
