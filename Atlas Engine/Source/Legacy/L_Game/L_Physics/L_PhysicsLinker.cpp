#include "L_PhysicsLinker.h"

void L_Atlas::L_PhysicsLinker::DeleteObjectFromScene(L_PhysicsScene* Scene, L_PhysicsObject* obj)
{
	bool found = false;
	for (unsigned int i = 0; i < Scene->physicsObjectsOnScene.size(); i++) {
		if (Scene->physicsObjectsOnScene.at(i) == obj) {
			Scene->physicsObjectsOnScene.erase(Scene->physicsObjectsOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}

	for (unsigned int i = 0; i < Scene->physicsL_LightsOnScene.size(); i++) {
		if (Scene->physicsL_LightsOnScene.at(i) == obj) {
			Scene->physicsL_LightsOnScene.erase(Scene->physicsL_LightsOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}

	for (unsigned int i = 0; i < Scene->playersOnScene.size(); i++) {
		if (Scene->playersOnScene.at(i)->GetPlayerModel() == obj) {
			Scene->playersOnScene.erase(Scene->playersOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}
}
