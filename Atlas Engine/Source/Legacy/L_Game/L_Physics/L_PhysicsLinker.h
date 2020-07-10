#pragma once
#include "L_PhysicsObject.h"
#include "L_PhysicsScene.h"

namespace L_Atlas {
	class L_PhysicsLinker {
	public:
		static void DeleteObjectFromScene(L_PhysicsScene* Scene, L_PhysicsObject* obj);
	};
}