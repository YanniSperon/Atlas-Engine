#include "L_PhysicsEngine.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Other/L_Convert.h"
#include "Legacy/L_Game/L_Player.h"
#include "Legacy/L_Game/L_Physics/L_PhysicsLinker.h"
#include <iostream>

namespace L_Atlas {

	static btDefaultCollisionConfiguration* collisionConfiguration;
	static btCollisionDispatcher* dispatcher;
	static btBroadphaseInterface* overlappingPairCache;
	static btSequentialImpulseConstraintSolver* solver;
	static btDiscreteDynamicsWorld* dynamicsWorld;
	static bool physicsEnabled;

	static L_PhysicsScene* physicsScene;



	bool BulletCollisionCallbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2) {
		const btCollisionObject* obj1Object = obj1->getCollisionObject();
		const btCollisionObject* obj2Object = obj1->getCollisionObject();
		if (obj1Object == NULL || obj1Object == nullptr) {
			L_System::Err("This is our problem1");
		}
		L_BulletPhysicsObject* userPtr1 = (L_BulletPhysicsObject*)obj1Object->getUserPointer();
		L_BulletPhysicsObject* userPtr2 = (L_BulletPhysicsObject*)obj2Object->getUserPointer();
		if (userPtr1 == NULL || userPtr1 == nullptr) {
			L_System::Err("This is our problem ptr1");
		}
		userPtr1->collisionData.obj1 = obj1Object;
		userPtr2->collisionData.obj2 = obj2Object;
		L_System::Log("First object collided: " + std::to_string(userPtr1->uid) + ".");
		L_System::Log("Second object collided: " + std::to_string(userPtr2->uid) + ".");
		L_PhysicsObject* physObj1 = (L_PhysicsObject*)userPtr1->physicsObject;
		L_PhysicsObject* physObj2 = (L_PhysicsObject*)userPtr2->physicsObject;
		physObj1->PrepareForDeletion();
		physObj2->PrepareForDeletion();
		L_PhysicsLinker::DeleteObjectFromScene(physicsScene, physObj1);
		L_PhysicsLinker::DeleteObjectFromScene(physicsScene, physObj2);
		delete physObj1;
		delete physObj2;
		return false;
	}

	void L_PhysicsEngine::Initialize()
	{
		gContactAddedCallback=BulletCollisionCallbackFunc;
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -9.80665, 0));
		
		/*debugDrawer = new PhysicsDebugDrawer();
		debugDrawer->setDebugMode(0);
		dynamicsWorld->setDebugDrawer(debugDrawer);*/

		physicsEnabled = true;
	}

	void L_PhysicsEngine::Update(double deltaT)
	{
		if (physicsEnabled) {
			ToggleDebugger();
			// switch physics frame rate to 30 for better performance \/
			dynamicsWorld->stepSimulation(deltaT, 10/*, 0.033333333333333333f*/);
			L_Global::Variables.currentScene.Update();
		}
	}

	void L_PhysicsEngine::SetL_PhysicsScene(L_PhysicsScene* scene)
	{
		physicsScene = scene;
	}

	btCollisionObject* L_PhysicsEngine::AddPhysicsBody(btCollisionShape* shape, btTransform& transformation, float mass, L_PhysicsObject* pObj)
	{
		if (shape != NULL) {
			btScalar massOfObject(mass);
			bool isDynamic = (massOfObject != 0.0f);
			btVector3 localInertia(0.0, 0.0, 0.0);
			if (isDynamic) {
				shape->calculateLocalInertia(massOfObject, localInertia);
			}
			//printf("%f, %f, %f", transformation.getOrigin()[0], transformation.getOrigin()[1], transformation.getOrigin()[2]);
			if (&transformation == NULL) {
				L_System::Err("NULL transformation");
			}
			btDefaultMotionState* myMotionState = new btDefaultMotionState(transformation);
			if (myMotionState == NULL) {
				L_System::Err("NULL myMotionState");
			}
			btRigidBody::btRigidBodyConstructionInfo rbInfo(massOfObject, myMotionState, shape, localInertia);
			if (&rbInfo == NULL) {
				L_System::Err("NULL rbInfo");
			}
			btRigidBody* body = new btRigidBody(rbInfo);
			if (body == NULL) {
				L_System::Err("NULL body");
			}
			
			bool shouldCollideWithPlayerBody = true;

			if (mass > 45.0f) {
				body->setActivationState(DISABLE_DEACTIVATION);
				body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CollisionFlags::CF_CUSTOM_MATERIAL_CALLBACK);
				shouldCollideWithPlayerBody = false;
				//body->setCollisionFlags;
				//body->setIgnoreCollisionCheck;
				//body->setFlags;
			}
			//body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			//body->setActivationState(DISABLE_DEACTIVATION);
			//void* parentL_PhysicsObject, unsigned long long int objectUID, bool shouldCollideWithPlayerBody
			body->setUserPointer((void*)(new L_BulletPhysicsObject(pObj, pObj->GetUID(), shouldCollideWithPlayerBody)));
			dynamicsWorld->addRigidBody(body);
			return body;
		}
		else {
			L_System::Err("NULL shape!");
			return NULL;
		}
	}

	void L_PhysicsEngine::Recalculate(btCollisionObject* object)
	{
		dynamicsWorld->updateSingleAabb(object);
	}

	void L_PhysicsEngine::DrawDebug()
	{
		dynamicsWorld->debugDrawWorld();
	}

	void L_PhysicsEngine::Cleanup()
	{
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getCollisionShape();
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
		
		delete dynamicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
	}

	void L_PhysicsEngine::ToggleDebugger()
	{
		if (L_Global::Variables.keyIn.ninePressed) {
			L_System::Log("Toggling debug wireframe");
			//debugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
		}
		if (L_Global::Variables.keyIn.zeroPressed) {
			L_System::Log("Toggling debug AABB");
			//debugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
		}
	}

	void L_PhysicsEngine::RemovePhysicsBody(btCollisionObject* object)
	{
		btRigidBody* body = btRigidBody::upcast(object);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
			delete body->getCollisionShape();
		}
		dynamicsWorld->removeCollisionObject(object);
		delete object;
	}

	void L_PhysicsEngine::SetGravity(btVector3 newGravity)
	{
		dynamicsWorld->setGravity(newGravity);
	}

	btTriangleMesh* L_PhysicsEngine::CreatePhysicsBodyMesh(L_ShapeData& data)
	{
		btTriangleMesh* returnValue = new btTriangleMesh();
		for (int i = 0; i < data.numIndices / 3; i++)
		{
			int index0 = data.indices[i * 3];
			int index1 = data.indices[i * 3 + 1];
			int index2 = data.indices[i * 3 + 2];
			btVector3 vertex0(L_Convert::Vector3(data.vertices[index0].position));
			btVector3 vertex1(L_Convert::Vector3(data.vertices[index1].position));
			btVector3 vertex2(L_Convert::Vector3(data.vertices[index2].position));
			returnValue->addTriangle(vertex0, vertex1, vertex2);
		}
		return returnValue;
	}

	void L_PhysicsEngine::SetPhysics(bool togglePhysics)
	{
		physicsEnabled = togglePhysics;
	}
}