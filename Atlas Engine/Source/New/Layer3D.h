#pragma once

#include "Layer.h"

namespace Atlas {
	class Layer3D : public Layer {
	private:

	public:
		Layer3D();
		Layer3D(int w, int h, int xPos, int yPos);
		~Layer3D();
	};
}