#pragma once
#include "Legacy/L_Game/L_Scene.h"
#include "L_PhysicsObject.h"
#include "L_PhysicsLight.h"
#include "Legacy/L_Game/L_Player.h"
#include "L_PhysicsRenderer.h"

namespace L_Atlas {
	
	class L_PhysicsScene {
	private:

	public:
		std::vector<L_PhysicsObject*> physicsObjectsOnScene;
		std::vector<L_PhysicsLight*> physicsL_LightsOnScene;
		std::vector<L_Player*> playersOnScene;

		L_PhysicsScene();
		L_PhysicsScene(L_Scene* scene);
		~L_PhysicsScene();

		void Submit(L_PhysicsRenderer* renderer, L_Player* camera);
		void Update();
	};
}