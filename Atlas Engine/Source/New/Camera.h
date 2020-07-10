#pragma once

#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	class Camera {
	private:
		// include forward vector, up vector, etc
		glm::vec3 forwardDirection;
		glm::vec3 upDirection;
		glm::vec3 translation;
		float FOV;
		float nearPlane;
		float farPlane;
		int height;
		int width;
		double oldMouseX;
		double oldMouseY;
	public:
		Camera();
		~Camera();

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		void LookAt(glm::vec3 position);
		void LookAtMouse(float sensitivity, double xpos, double ypos);
		void MoveForward(float speed, float deltaTime);
		void MoveBackward(float speed, float deltaTime);
		void StrafeLeft(float speed, float deltaTime);
		void StrafeRight(float speed, float deltaTime);
		void MoveUp(float speed, float deltaTime);
		void MoveDown(float speed, float deltaTime);

		glm::vec3 MoveForwardComponent(float speed, float deltaTime);
		glm::vec3 MoveBackwardComponent(float speed, float deltaTime);
		glm::vec3 StrafeLeftComponent(float speed, float deltaTime);
		glm::vec3 StrafeRightComponent(float speed, float deltaTime);
		glm::vec3 MoveUpComponent(float speed, float deltaTime);
		glm::vec3 MoveDownComponent(float speed, float deltaTime);

		glm::vec3 GetTranslation();
		glm::vec3 GetForwardDirection();
		glm::vec3 GetUpwardDirection();

		void SetTranslation(glm::vec3 newTranslation);
		void SetWidth(int newWidth);
		void SetHeight(int newHeight);

		void Update(float deltaTime);
	};
}