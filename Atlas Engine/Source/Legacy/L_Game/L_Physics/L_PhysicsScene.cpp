#include "L_PhysicsScene.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_System.h"

namespace L_Atlas {

	L_PhysicsScene::L_PhysicsScene()
	{

	}

	L_PhysicsScene::L_PhysicsScene(L_Scene* scene)
	{
		for (unsigned int i = 0; i < scene->preloadedObjectsOnScene.size(); i++) {
			physicsObjectsOnScene.push_back(new L_PhysicsObject(scene->preloadedObjectsOnScene.at(i), 0.0f));
		}
		for (unsigned int i = 0; i < scene->objectsOnScene.size(); i++) {
			physicsObjectsOnScene.push_back(new L_PhysicsObject(scene->objectsOnScene.at(i), 1.0f));
		}
		for (unsigned int i = 0; i < scene->preloadedObjectsOnScene.size(); i++) {
			physicsL_LightsOnScene.push_back(new L_PhysicsLight(scene->lightsOnScene.at(i)));
		}
		for (unsigned int i = 0; i < scene->camerasOnScene.size(); i++) {
			playersOnScene.push_back(new L_Player(scene->camerasOnScene.at(i)));
		}
		if (playersOnScene.size() == 0) {
			L_System::Err("Error initializing player!");
		}
	}

	L_PhysicsScene::~L_PhysicsScene()
	{
		// MAKE SURE TO SWITCH OUT CAMERA BEFORE THIS GETS DESTROYED BECAUSE THEN ACTIVECAMERA = NULL
		for (unsigned int i = 0; i < physicsObjectsOnScene.size(); i++) {
			delete physicsObjectsOnScene.at(i);
		}
		physicsObjectsOnScene.clear();

		for (unsigned int i = 0; i < physicsL_LightsOnScene.size(); i++) {
			delete physicsL_LightsOnScene.at(i);
		}
		physicsL_LightsOnScene.clear();

		for (unsigned int i = 0; i < playersOnScene.size(); i++) {
			delete playersOnScene.at(i);
		}
		playersOnScene.clear();
	}

	void L_PhysicsScene::Submit(L_PhysicsRenderer* renderer, L_Player* camera)
	{
		for (unsigned int i = 0; i < physicsObjectsOnScene.size(); i++) {
			renderer->Submit3D(physicsObjectsOnScene.at(i), camera->GetTranslation());
		}

		for (unsigned int i = 0; i < physicsL_LightsOnScene.size(); i++) {
			renderer->Submit3D(physicsL_LightsOnScene.at(i), camera->GetTranslation());
		}

		for (unsigned int i = 0; i < playersOnScene.size(); i++) {
			renderer->Submit3D(playersOnScene.at(i)->GetPlayerModel(), camera->GetTranslation());
		}

		renderer->SubmitForceRender3DObject(camera->GetSkybox());
	}

	void L_PhysicsScene::Update()
	{
		for (unsigned int i = 0; i < physicsObjectsOnScene.size(); i++) {
			physicsObjectsOnScene.at(i)->Update();
		}
		
		for (unsigned int i = 0; i < physicsL_LightsOnScene.size(); i++) {
			physicsL_LightsOnScene.at(i)->Update();
		}

		for (unsigned int i = 0; i < playersOnScene.size(); i++) {
			playersOnScene.at(i)->GetPlayerModel()->Update();
		}
	}
}