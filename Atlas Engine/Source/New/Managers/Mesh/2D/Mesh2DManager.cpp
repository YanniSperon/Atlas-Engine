#include "Mesh2DManager.h"

#include "New/System/Console/Console.h"

Atlas::Mesh2DManager::Mesh2DManager()
	: Updatable(60), loadedMeshes(), vramReference()
{

}

Atlas::Mesh2DManager::~Mesh2DManager()
{
	for (auto it : vramReference) {
		it.second->DeleteFromVRAM();
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
		if (mesh != loadedMeshes[mesh->name]) {
			// the stored one is different than the new one
			int count = 0;
			while (loadedMeshes.find(mesh->name + std::to_string(count)) != loadedMeshes.end()) {
				count++;
			}
			std::string newName = mesh->name + std::to_string(count);
			mesh->name = newName;
			loadedMeshes[newName] = mesh;
		}
	}
	return mesh;
}

void Atlas::Mesh2DManager::DeleteMesh(const std::string& name)
{
	if (loadedMeshes.find(name) == loadedMeshes.end()) {
		// doesnt exist
		// do nothing
		Console::Warning("Attempting to delete mesh that does not exist");
	}
	else {
		if (vramReference.find(loadedMeshes[name]) == vramReference.end()) {
			// no vram reference, dont do anything
			Console::FatalError("VRAM REFERENCE OUT OF SYNC WITH LOADED MESHES");
			exit(-2);
		}
		else {
			// vram reference, destroy it
			VRAMHandle* ref = vramReference[loadedMeshes[name]];
			ref->DeleteFromVRAM();
			if (((void*) ref != loadedMeshes[name]->vramHandle) || (ref->referencingMesh != (void*) loadedMeshes[name])) {
				Console::FatalError("VRAM HANDLE AND MESH OUT OF SYNC");
				exit(-4);
			}
			delete ref;
			vramReference.erase(loadedMeshes[name]);
		}

		loadedMeshes[name]->DeleteMesh();
		delete loadedMeshes[name];
		loadedMeshes.erase(name);
	}
}

void Atlas::Mesh2DManager::DeleteMesh(Mesh2D* mesh)
{
	if (loadedMeshes.find(mesh->name) == loadedMeshes.end()) {
		// doesnt exist
		Console::Warning("Mesh requested for deletion does not exist in the loaded meshes map");
	}
	else {
		if (loadedMeshes[mesh->name] == mesh) {
			if (vramReference.find(mesh) == vramReference.end()) {
				// vram reference doesnt, exist
				Console::FatalError("VRAM REFERENCE OUT OF SYNC WITH LOADED MESHES");
				exit(-8);
			} else {
				// same meshes
				VRAMHandle* ref = vramReference[mesh];
				ref->DeleteFromVRAM();
				if (((void*)ref != mesh->vramHandle) || (ref->referencingMesh != (void*)mesh)) {
					Console::FatalError("VRAM HANDLE AND MESH OUT OF SYNC");
					exit(-16);
				}
				delete ref;
				vramReference.erase(mesh);
			}

			mesh->DeleteMesh();
			loadedMeshes.erase(mesh->name);
			delete mesh;
		}
		else {
			// different meshes
			Console::FatalError("MESH NAMES OUT OF SYNC");
		}
	}
}

void Atlas::Mesh2DManager::SetMesh(Mesh2D* newMesh)
{

}

void Atlas::Mesh2DManager::ReplaceMesh(Mesh2D* newMesh)
{
}
