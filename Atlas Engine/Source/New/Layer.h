#pragma once

#include "Renderer.h"
#include "Scene3D.h"

namespace Atlas {

	enum class E_LayerType
	{
		NONE = 0,
		TWODIMENSIONAL,
		THREEDIMENSIONAL

	};

	class Layer {
	private:
		int width;
		int height;
		int x;
		int y;
		Scene* scene;
		E_LayerType layerType;
	public:
		Layer();
		Layer(E_LayerType type, int w, int h, int xPos, int yPos);
		~Layer();
		
		void Draw(Renderer* renderer);
	};
}