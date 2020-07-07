#pragma once

#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "Legacy/L_Rendering/L_Scene/L_Object.h"
#include "Legacy/L_Rendering/L_Scene/L_Renderer.h"
#include "Legacy/L_Rendering/L_Scene/L_Light.h"
#include <string>
#include <vector>
#include "Shared/S_Vendor/S_Bullet/btBulletCollisionCommon.h"
#include "Legacy/L_Rendering/L_Scene/L_Camera.h"

namespace L_Atlas {

	class L_Scene {
	public:
		std::vector<L_Object*> objectsOnScene;
		std::vector<L_Object*> preloadedObjectsOnScene;
		std::vector<L_Light*> lightsOnScene;
		std::vector<L_Camera*> camerasOnScene;

		L_Scene();
		L_Scene(std::vector<L_Object*> preloadedObjects, std::vector<L_Object*> objects, std::vector<L_Light*> lightSource, std::vector<L_Camera*> cameras);
		~L_Scene();

		void Submit(L_Renderer* renderer, L_Camera* camera);
		void Save(std::string directory, std::string name);
		void Update();
	};
}