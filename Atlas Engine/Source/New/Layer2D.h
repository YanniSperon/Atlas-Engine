#pragma once

#include "Layer.h"

namespace Atlas {
	class Layer2D : public Layer {
	private:

	public:
		Layer2D();
		Layer2D(int w, int h, int xPos, int yPos);
		~Layer2D();
	};
}