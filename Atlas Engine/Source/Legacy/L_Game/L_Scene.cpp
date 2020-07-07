#include "L_Scene.h"
#include "Legacy/L_System/L_IO.h"
#include "Legacy/L_System/L_System.h"
#include "L_Player.h"
#include "Legacy/L_Global/L_Global.h"

namespace L_Atlas {

	L_Scene::L_Scene()
	{

	}

	L_Scene::L_Scene(std::vector<L_Object*> preloadedObjects, std::vector<L_Object*> objects, std::vector<L_Light*> lightSource, std::vector<L_Camera*> cameras)
	{
		preloadedObjectsOnScene = preloadedObjects;
		objectsOnScene = objects;
		lightsOnScene = lightSource;
		camerasOnScene = cameras;
	}

	L_Scene::~L_Scene()
	{
		for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
			delete preloadedObjectsOnScene.at(i);
		}
		preloadedObjectsOnScene.clear();

		for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
			delete objectsOnScene.at(i);
		}
		objectsOnScene.clear();

		for (unsigned int i = 0; i < lightsOnScene.size(); i++) {
			delete lightsOnScene.at(i);
		}
		lightsOnScene.clear();


		for (unsigned int i = 0; i < camerasOnScene.size(); i++) {
			delete camerasOnScene.at(i);
		}
		camerasOnScene.clear();
	}

	void L_Scene::Submit(L_Renderer* renderer, L_Camera* camera)
	{
		for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
			renderer->Submit3D(preloadedObjectsOnScene[i], camera->GetTranslation());
		}

		for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
			renderer->Submit3D(objectsOnScene[i], camera->GetTranslation());
		}

		for (unsigned int i = 0; i < lightsOnScene.size(); i++) {
			renderer->Submit3D(lightsOnScene[i], camera->GetTranslation());
		}

		renderer->SubmitForceRender3D(L_Global::Variables.activeCamera->GetSkybox());

		//for (unsigned int i = 0; i < camerasOnScene.size(); i++) {
		//	Player* player = dynamic_cast<Player*>(camerasOnScene.at(i));
		//	if (player != nullptr) {
		//		renderer->Submit3D(player, camPos);
		//	}
		//}
	}

	void L_Scene::Save(std::string directory, std::string name)
	{
		L_System::Log("Saving");
		L_IO::SaveToFile(objectsOnScene, directory, name);
	}

	void L_Scene::Update()
	{
		//for (unsigned int i = 0; i < preloadedObjectsOnScene.size(); i++) {
		//	preloadedObjectsOnScene.at(i)->Update();
		//}
		//
		//for (unsigned int i = 0; i < objectsOnScene.size(); i++) {
		//	objectsOnScene.at(i)->Update();
		//}
		//
		//for (unsigned int i = 0; i < lightsOnScene.size(); i++) {
		//	lightsOnScene.at(i)->Update();
		//}

		//for (unsigned int i = 0; i < camerasOnScene.size(); i++) {
		//	Player* player = dynamic_cast<Player*>(camerasOnScene.at(i));
		//	if (player != nullptr) {
		//		player->Update();
		//	}
		//}
	}
}