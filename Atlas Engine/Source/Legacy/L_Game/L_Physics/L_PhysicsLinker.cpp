#include "L_PhysicsLinker.h"

void L_Atlas::L_PhysicsLinker::DeleteObjectFromScene(L_PhysicsScene* scene, L_PhysicsObject* obj)
{
	bool found = false;
	for (unsigned int i = 0; i < scene->physicsObjectsOnScene.size(); i++) {
		if (scene->physicsObjectsOnScene.at(i) == obj) {
			scene->physicsObjectsOnScene.erase(scene->physicsObjectsOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}

	for (unsigned int i = 0; i < scene->physicsL_LightsOnScene.size(); i++) {
		if (scene->physicsL_LightsOnScene.at(i) == obj) {
			scene->physicsL_LightsOnScene.erase(scene->physicsL_LightsOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}

	for (unsigned int i = 0; i < scene->playersOnScene.size(); i++) {
		if (scene->playersOnScene.at(i)->GetPlayerModel() == obj) {
			scene->playersOnScene.erase(scene->playersOnScene.begin() + i);
			found = true;
		}
		if (found) {
			break;
		}
	}
}
