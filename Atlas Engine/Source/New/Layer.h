#pragma once

#include "Renderer.h"
#include "Scene3D.h"

namespace Atlas {

	class Layer {
	private:
		int width;
		int height;
		int x;
		int y;
		Scene* scene;
		Object2D* 
	public:
		Layer();
		Layer(int w, int h, int xPos, int yPos);
		~Layer();
		
		void Draw(Renderer* renderer);

		void Update(float deltaTime);

		void SetScene(Scene* newScene);
		void SetSize(int w, int h);
		void SetPosition(int xPos, int yPos);
		Scene* GetScene();
	};
}