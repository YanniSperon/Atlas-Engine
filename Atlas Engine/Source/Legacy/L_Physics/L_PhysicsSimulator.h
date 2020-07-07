#pragma once
#include "Legacy/L_Game/L_Scene.h"

namespace L_Atlas {
	class L_PhysicsSimulator {
	public:
		static void LaunchSimulation(L_Scene* sceneToSimulate, double timeConstant);
	};
}