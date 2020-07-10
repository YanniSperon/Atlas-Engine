#include "L_Player.h"
#include "Legacy/L_Other/L_Convert.h"
#include "Legacy/L_Physics/L_PhysicsEngine.h"
#include "Legacy/L_System/L_System.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"

namespace L_Atlas {

	L_Player::L_Player()
		: hasControls(false), movementSpeed(0.1f), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), cameraTranslation(0.0f, 0.0f, 0.0f), oldMouseX(36000000.0), oldMouseY(0.0), mouseSensitivity(0.0f), skybox(nullptr)
	{

	}

	L_Player::L_Player(L_Camera* camera)
		: hasControls(camera->GetHasControls()), movementSpeed(camera->GetMovementSpeed()), viewDirection(camera->GetViewDirection()), upDirection(camera->GetUpDirection()), skybox(camera->GetSkybox()), cameraTranslation(camera->GetTranslation()), oldMouseX(camera->GetOldMousePos().x), oldMouseY(camera->GetOldMousePos().y), mouseSensitivity(camera->GetMouseSensitivity())
	{
		playerModel = new L_PhysicsObject(new L_Object(L_Type::cubeModel, "", "", "Resources/images/textures/", "newcow.png", "Resources/shaders/", "Lighting.shader", true, true, L_System::GenerateUniqueID(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 2.0f, 1.0f)), 100.0f);
	}

	L_Player::~L_Player()
	{
		delete playerModel;
	}

	void L_Player::EnableMovementControls()
	{
		hasControls = true;
	}

	void L_Player::DisableMovementControls()
	{
		hasControls = false;
	}

	glm::mat4 L_Player::GetViewTransformMatrix()
	{
		return glm::lookAt(cameraTranslation, cameraTranslation + viewDirection, upDirection);
	}

	void L_Player::LookAt(double xpos, double ypos)
	{
		if (hasControls) {
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

	void L_Player::MoveForward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedViewDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != nullptr) {
				BringWith(playerModel);
			}
		}
	}

	void L_Player::MoveBackward(float delta)
	{
		if (hasControls) {
			glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(viewDirection.x, viewDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedViewDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedViewDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != nullptr) {
				BringWith(playerModel);
			}
		}
	}

	void L_Player::StrafeLeft(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += -movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += -movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != nullptr) {
				BringWith(playerModel);
			}
		}
	}

	void L_Player::StrafeRight(float delta)
	{
		if (hasControls) {
			glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
			glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
			cameraTranslation.x += movementSpeed * normalizedStrafeDirection.x * delta;
			cameraTranslation.z += movementSpeed * normalizedStrafeDirection.y * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != nullptr) {
				BringWith(playerModel);
			}
		}
	}

	void L_Player::MoveUp(float delta)
	{
		if (hasControls) {
			cameraTranslation += movementSpeed * upDirection * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != nullptr) {
				BringWith(playerModel);
			}
		}
	}

	void L_Player::MoveDown(float delta)
	{
		if (hasControls) {
			cameraTranslation += -movementSpeed * upDirection * delta;
			if (skybox != nullptr) {
				skybox->TranslateVec3(cameraTranslation);
			}
			if (playerModel != nullptr) {
				BringWith(playerModel);
			}
		}
	}

	void L_Player::Follow(L_PhysicsObject* obj)
	{
		cameraTranslation = obj->GetTranslation();
		if (skybox != nullptr) {
			skybox->TranslateVec3(cameraTranslation);
		}
		if (playerModel != nullptr) {
			BringWith(playerModel);
		}
	}
	
	void L_Player::FollowMesh(L_Mesh* obj)
	{
		cameraTranslation = obj->GetTranslation();
		if (skybox != nullptr) {
			skybox->TranslateVec3(cameraTranslation);
		}
	}

	void L_Player::ChangeMovementSpeed(float newSpeed)
	{
		movementSpeed = newSpeed;
	}

	void L_Player::BringWith(L_PhysicsObject* obj)
	{
		obj->TranslateVec3(cameraTranslation);
		btRigidBody* body = btRigidBody::upcast(obj->GetL_PhysicsObject());
		if (body != nullptr) {
			body->setLinearVelocity(btVector3(0.0, 0.0, 0.0));
		}
		obj->InverseUpdate();
	}

	void L_Player::BringWithL_Mesh(L_Mesh* obj)
	{
		obj->TranslateVec3(cameraTranslation);
	}

	void L_Player::SetYModelOffset(float value)
	{
		//YModelOffset = value;
	}

	glm::vec3 L_Player::GetTranslation()
	{
		return cameraTranslation;
	}

	glm::vec2 L_Player::GetOldMousePos()
	{
		return glm::vec2(oldMouseX, oldMouseY);
	}

	glm::vec3 L_Player::GetViewDirection()
	{
		return viewDirection;
	}

	void L_Player::SetSkybox(L_Object* newSkybox)
	{
		skybox = newSkybox;
	}

	L_Object* L_Player::GetSkybox()
	{
		return skybox;
	}

	void L_Player::SetPlayerModel(L_PhysicsObject* newModel)
	{
		playerModel = newModel;
	}

	L_PhysicsObject* L_Player::GetPlayerModel()
	{
		return playerModel;
	}
}