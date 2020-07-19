#pragma once

#include <string>
#include <unordered_map>
#include "New/Mesh/Shared/VRAM/VRAMHandle.h"
#include "New/Mesh/3D/Mesh3D.h"

namespace Atlas {
	class Mesh3DManager {
	private:
		std::unordered_map<const std::string&, Mesh3D*> loadedMeshes;
		std::unordered_map<Mesh3D*, VRAMHandle*> vramReference;
	public:
		Mesh3DManager();
		~Mesh3DManager();



		VRAMHandle* Load3DMeshToVRAM(const std::string& name);
		Mesh3D* GetLoadedMesh(const std::string& name);
		Shader* GetLoadedShader(const std::string& name);
		Texture* GetLoadedTexture(const std::string& name);
		VRAMHandle* GetVRAMReference(Mesh3D* mesh);
		VRAMHandle* GetVRAMReference(Mesh2D* mesh);

		Mesh3D* PrepareMesh3D(Mesh3D* mesh, Object3D* sender);
		Shader* PrepareShader(Shader* shader, Object3D* sender);
		Texture* PrepareTexture(Texture* texture, Object3D* sender);

		Shader* PrepareShader(Shader* shader, Object2D* sender);
		Texture* PrepareTexture(Texture* texture, Object2D* sender);
	};
}