#pragma once

#include "Shared/S_Vendor/S_Bullet/btBulletDynamicsCommon.h"
#include "Shared/S_Vendor/S_Bullet/BulletCollision/CollisionShapes/btTriangleMesh.h"
#include "Legacy/L_Game/L_Physics/L_PhysicsObject.h"
#include "Legacy/L_Game/L_Physics/L_PhysicsScene.h"
#include "Legacy/L_Rendering/L_Primitives/L_ShapeData.h"

namespace L_Atlas {
	class L_PhysicsEngine {
	public:
		static void Initialize();
		static void Update(double deltaT);
		static void SetL_PhysicsScene(L_PhysicsScene* Scene);
		static btCollisionObject* AddPhysicsBody(btCollisionShape* shape, btTransform& transformation, float mass, L_PhysicsObject* pObj);
		static void Recalculate(btCollisionObject* object);
		static void DrawDebug();
		static void Cleanup();
		static void ToggleDebugger();
		static void RemovePhysicsBody(btCollisionObject* object);
		static void SetGravity(btVector3 newGravity);
		static btTriangleMesh* CreatePhysicsBodyMesh(L_ShapeData& data);
		static void SetPhysics(bool togglePhysics);
	};
}