#pragma once

#include <vector>
#include <string>
#include "New/Scene/3D/Node/Node3D.h"
#include "New/Scene/Shared/Scene/Scene.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	class Scene3D : public Scene {
	private:
		Node3D* rootNode; // stores skybox
		Node3D* activeCameraNode;
	public:
		Scene3D();
		Scene3D(int initialWidth, int initialHeight);
		~Scene3D();

		void Update(float deltaTime);
		void Begin();
		void Draw(Renderer* renderer);
		void End();

		Node3D* GetRootNode();
		Node3D* CreateChildNode();
		void AddNode(Node3D* object);
		Node3D* GetNodeByName(const std::string& nodeName);

		void SetRootNode(Node3D* newNode);
		void SetActiveCamera(Node3D* newCamera);
	};
}