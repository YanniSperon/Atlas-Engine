#pragma once
#include "Scene.h"
#include "Node2D.h"

namespace Atlas {
	class Scene2D : public Scene {
	private:
		Node2D* rootNode;
	public:
		Scene2D();
		Scene2D(int initialWidth, int initialHeight);
		~Scene2D();

		void Update(float deltaTime);
		void Begin();
		void Draw(Renderer* renderer);
		void End();

		Node2D* GetRootNode();
		Node2D* CreateChildNode();
		void AddNode(Node2D* object);
		Node2D* GetNodeByName(const std::string& nodeName);

		void SetRootNode(Node2D* newNode);
		void SetActiveCamera(Node2D* newCamera);
	};
}