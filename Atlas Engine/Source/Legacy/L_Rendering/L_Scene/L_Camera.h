#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "L_Object.h"

namespace L_Atlas {

	class L_Camera {
	public:
		bool hasControls;
		bool hasLookControls;
		float movementSpeed;
		glm::vec3 viewDirection;
		glm::vec3 upDirection;
		glm::vec3 cameraTranslation;
		double oldMouseX;
		double oldMouseY;
		float mouseSensitivity;
		L_Object* skybox;
	public:
		L_Camera();
		L_Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity, L_Object* skyboxObj);
		~L_Camera();

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
		void Follow(L_Mesh* obj);
		void BringWith(L_Mesh* obj);
		void ChangeMovementSpeed(float newSpeed);

		glm::vec3 GetTranslation();
		glm::vec2 GetOldMousePos();
		bool GetHasControls();
		bool GetHasLookControls();
		float GetMovementSpeed();
		glm::vec3 GetViewDirection();
		glm::vec3 GetUpDirection();
		float GetMouseSensitivity();

		void SetSkybox(L_Object* newSkybox);
		L_Object* GetSkybox();
		void SetHasLookControls(bool newValue);
		static void SetFocus(L_Camera* cam);
	};
}