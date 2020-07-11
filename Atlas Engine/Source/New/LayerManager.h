#pragma once

#include "Layer.h"
#include <vector>

namespace Atlas {
	class LayerManager {
	private:
		std::vector<Layer*> layers;
	public:
		LayerManager();
		~LayerManager();

		void AddLayer(Layer* layer);

		void Draw(Renderer* renderer);
		void Update(float deltaTime);
	};
}