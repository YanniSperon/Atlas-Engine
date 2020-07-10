#include "L_Camera.h"
#include "Legacy/L_Global/L_Global.h"
#include "Legacy/L_System/L_Config.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"

namespace L_Atlas {

	L_Camera::L_Camera()
		: hasControls(false), movementSpeed(0.1f), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), cameraTranslation(0.0f, 0.0f, 0.0f), oldMouseX(36000000.0), oldMouseY(0.0), mouseSensitivity(0.0f), skybox(nullptr), hasLookControls(true)
	{

	}

	L_Camera::L_Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity, L_Object* skyboxObj)
		: hasControls(canControl), movementSpeed(movementSpeed), viewDirection(startingLookDirection), upDirection(startingUpDirection), skybox(skyboxObj), cameraTranslation(startingCameraTranslation), oldMouseX(36000000.0), oldMouseY(0.0), mouseSensitivity(mouseSensitivity), hasLookControls(true)
	{

	}

	L_Camera::~L_Camera()
	{
		delete skybox;
	}

	void L_Camera::EnableMovementControls()
	{
		hasControls = true;
	}

	void L_Camera::DisableMovementControls()
	{
		hasControls = false;
	}

	glm::mat4 L_Camera::GetViewTransformMatrix()
	{
		return glm::lookAt(cameraTranslation, cameraTranslation + viewDirection, upDirection);
	}

	void L_Camera::LookAt(double xpos, double ypos)
	{
		if (hasLookControls) {
			glm::vec2 mouseDelta(xpos - oldMouseX, ypos - oldMouseY);

			glm::vec3 toRotateAround = glm::cross(viewDirection, upDirection);
			glm::vec3 vd;
			viewDirection = glm::mat3(
				glm::rotate(glm::mat4(1.0f), -glm::radians(mouseDelta.x * mouseSensitivity), upDirection) *
				glm::rotate(glm::mat4(1.0f), -glm::radians(mouseDelta.y * mouseSensitivity), toRotateAround)
			) * viewDirection;

			viewDirection = glm::mat3() * viewDirection;

			oldMouseX = xpos;
			oldMouseY = ypos;
		}
	}

	void L_Camera::MoveForward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedViewDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void L_Camera::MoveBackward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedViewDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void L_Camera::StrafeLeft(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void L_Camera::StrafeRight(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void L_Camera::MoveUp(float delta)
	{
		if (hasControls) {
			cameraTranslation += movementSpeed * upDirection * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void L_Camera::MoveDown(float delta)
	{
		if (hasControls) {
			cameraTranslation += -movementSpeed * upDirection * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
		}
	}

	void L_Camera::Follow(L_Mesh* obj)
	{
		cameraTranslation = obj->GetTranslation();
		if (skybox != nullptr) {
			skybox->TranslateVec3(cameraTranslation);
		}
	}

	void L_Camera::ChangeMovementSpeed(float newSpeed)
	{
		movementSpeed = newSpeed;
	}

	void L_Camera::BringWith(L_Mesh* obj)
	{
		obj->TranslateVec3(cameraTranslation);
	}

	glm::vec3 L_Camera::GetTranslation()
	{
		return cameraTranslation;
	}

	glm::vec2 L_Camera::GetOldMousePos()
	{
		return glm::vec2(oldMouseX, oldMouseY);
	}

	void L_Camera::SetSkybox(L_Object* newSkybox)
	{
		skybox = newSkybox;
	}

	L_Object* L_Camera::GetSkybox()
	{
		return skybox;
	}

	void L_Camera::SetHasLookControls(bool newValue)
	{
		hasLookControls = newValue;
	}

	void L_Camera::SetFocus(L_Camera* cam)
	{
		L_Object* tempSkybox = L_Global::Variables.activeCamera->GetSkybox();
		cam->SetSkybox(tempSkybox);
		L_Global::Variables.activeCamera->SetSkybox(nullptr);
		L_Global::Variables.activeCamera = cam;
		cam->SetSkybox(tempSkybox);
		glm::vec2 temp = L_Global::Variables.activeCamera->GetOldMousePos();
		glfwSetCursorPos(L_Global::Variables.window, temp.x, temp.y);
	}
	bool L_Camera::GetHasControls()
	{
		return hasControls;
	}
	bool L_Camera::GetHasLookControls()
	{
		return hasLookControls;
	}
	float L_Camera::GetMovementSpeed()
	{
		return movementSpeed;
	}
	glm::vec3 L_Camera::GetViewDirection()
	{
		return viewDirection;
	}
	glm::vec3 L_Camera::GetUpDirection()
	{
		return upDirection;
	}
	float L_Camera::GetMouseSensitivity()
	{
		return mouseSensitivity;
	}
}