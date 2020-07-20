#pragma once

#include <string>
#include <unordered_map>
#include "New/Mesh/3D/Mesh3D.h"
#include "New/Mesh/Shared/VRAM/VRAMHandle.h"
#include "New/Scene/Shared/Updatable/Updatable.h"

namespace Atlas {
	class Mesh3DManager : public Updatable {
	private:
		std::unordered_map<const std::string&, Mesh3D*> loadedMeshes;
		std::unordered_map<Mesh3D*, VRAMHandle*> vramReference;

		VRAMHandle* LoadIntoVRAM(Mesh3D* mesh);
		void UnloadFromVRAM(VRAMHandle* handle);
	public:
		Mesh3DManager();
		~Mesh3DManager();

		virtual void Update(float deltaTime);

		Mesh3D* LoadMesh(const std::string& filepath);

		Mesh3D* GetMesh(Mesh3D* mesh);
		void DeleteReference(Object* obj);
		void AddReference(Object* obj);

		void DeleteMesh(const std::string& name);
		void DeleteMesh(Mesh3D* mesh);

		void SetMesh(Mesh3D* newMesh);
		void ReplaceMesh(Mesh3D* newMesh);

		VRAMHandle* GetVRAMHandle(Mesh3D* mesh);
	};
}