#pragma once

#include "New/Rendering/Shared/Renderer/Renderer.h"
#include "New/Scene/3D/Scene/Scene3D.h"

namespace Atlas {

	class Layer {
	private:
		int width;
		int height;
		int x;
		int y;
	protected:
		Scene* scene;
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