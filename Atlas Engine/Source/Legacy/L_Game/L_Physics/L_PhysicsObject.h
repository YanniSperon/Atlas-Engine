#pragma once
#include "Legacy/L_Rendering/L_Scene/L_Mesh.h"
#include "Legacy/L_Rendering/L_Scene/L_Object.h"
#include "Shared/S_Vendor/S_Bullet/btBulletDynamicsCommon.h"

namespace L_Atlas {

	struct L_Collision {
		const btCollisionObject* obj1;
		const btCollisionObject* obj2;

		L_Collision() {
			obj1 = nullptr;
			obj2 = nullptr;
		}

		L_Collision(const btCollisionObject* object1, const btCollisionObject* object2)
			: obj1(object1), obj2(object2)
		{
			
		}
	};

	struct L_BulletPhysicsObject {
		unsigned long long int uid;
		L_Collision collisionData;
		bool shouldCollideWithPlayer;
		void* physicsObject;

		L_BulletPhysicsObject(void* parentL_PhysicsObject, unsigned long long int objectUID, bool shouldCollideWithPlayerBody)
			: uid(objectUID), collisionData(), physicsObject(parentL_PhysicsObject), shouldCollideWithPlayer(shouldCollideWithPlayerBody)
		{

		}

		~L_BulletPhysicsObject() {

		}
	};
	
	class L_PhysicsObject : public L_Mesh {
	private:
		unsigned long long int uid;
		GLuint vertexBufferID;
		GLuint indexBufferID;
		GLuint texID;
		GLuint shaderID;
		GLsizei numIndices;
		L_Material material;
		bool glInitialized;
		std::string textureDirectory;
		std::string textureName;
		std::string shaderDirectory;
		std::string shaderName;
		bool hasLighting;
		btCollisionObject* physicsObject;
	public:
		L_PhysicsObject();
		L_PhysicsObject(L_Object* obj, float mass);
		~L_PhysicsObject();

		void Update();
		void InverseUpdate();
		virtual glm::mat4 GetModelTransformMatrix() override;
		bool GetGLInitialized();
		L_Material GetMaterial();
		bool GetHasLighting();
		GLuint GetShaderID();
		GLuint GetTextureID();
		GLuint GetVBO();
		btCollisionObject* GetL_PhysicsObject();
		unsigned long long int GetUID();

		void SetHasLighting(bool newValue);

		void Launch(glm::vec3 viewDirection);

		void Draw();
		void Bind();
		void Unbind();

		void PrepareForDeletion();

		void GLInit();
	};
}