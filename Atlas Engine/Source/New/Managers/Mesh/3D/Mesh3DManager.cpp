#include "Mesh3DManager.h"

Atlas::Mesh3DManager::Mesh3DManager()
	: loadedMeshes(), vramReference()
{

}

Atlas::Mesh3DManager::~Mesh3DManager()
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
