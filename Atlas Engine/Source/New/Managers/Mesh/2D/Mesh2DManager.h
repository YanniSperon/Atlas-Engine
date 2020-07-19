#pragma once

#include <string>
#include <unordered_map>
#include "New/Rendering/2D/Object/Object2D.h"
#include "New/Mesh/2D/Mesh2D.h"
#include "New/Mesh/Shared/VRAM/VRAMHandle.h"
#include "New/Scene/Shared/Updatable/Updatable.h"

namespace Atlas {
	class Mesh2DManager : public Updatable {
	private:
		std::unordered_map<const std::string&, Mesh2D*> loadedMeshes;
		std::unordered_map<Mesh2D*, VRAMHandle*> vramReference;
	public:
		Mesh2DManager();
		~Mesh2DManager();

		virtual void Update(float deltaTime);

		Mesh2D* GetMesh(Mesh2D* mesh);
		void Delete(Object2D* obj);

		void DeleteMesh(const std::string& name);
		void DeleteMesh(Mesh2D* mesh);

		void SetMesh(Mesh2D* newMesh);
		void ReplaceMesh(Mesh2D* newMesh);
	};
}