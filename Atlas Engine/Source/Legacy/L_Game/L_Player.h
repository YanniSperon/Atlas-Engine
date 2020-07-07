#pragma once
#include "Legacy/L_Rendering/L_Scene/L_Camera.h"
#include "Legacy/L_Game/L_Physics/L_PhysicsObject.h"

namespace L_Atlas {
	class L_Player {
	private:
		bool hasControls;
		float movementSpeed;
		glm::vec3 viewDirection;
		glm::vec3 upDirection;
		glm::vec3 cameraTranslation;
		double oldMouseX;
		double oldMouseY;
		float mouseSensitivity;
		//float YModelOffset;
		L_Object* skybox;
		L_PhysicsObject* playerModel;

	public:
		L_Player();
		L_Player(L_Camera* camera);
		~L_Player();

		void EnableMovementControls();
		void DisableMovementControls();
		glm::mat4 GetViewTransformMatrix();
		void LookAt(double xpos, double ypos);
		void MoveForward(float delta);
		void MoveBackward(float delta);
		void StrafeLeft(float delta);
		void StrafeRight(float delta);
		void MoveUp(float delta);
		void MoveDown(float delta);
		void Follow(L_PhysicsObject* obj);
		void FollowMesh(L_Mesh* obj);
		void BringWith(L_PhysicsObject* obj);
		void BringWithL_Mesh(L_Mesh* obj);
		void ChangeMovementSpeed(float newSpeed);

		void SetYModelOffset(float value);

		void SetSkybox(L_Object* newSkybox);
		void SetPlayerModel(L_PhysicsObject* newModel);

		L_Object* GetSkybox();
		L_PhysicsObject* GetPlayerModel();
		glm::vec3 GetTranslation();
		glm::vec2 GetOldMousePos();
		glm::vec3 GetViewDirection();
	};
}