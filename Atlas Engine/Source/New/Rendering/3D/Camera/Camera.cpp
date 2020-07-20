#include "Camera.h"
#include "Shared/S_Vendor/S_GLM/gtx/quaternion.hpp"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"'
#include "New/System/Global/Global.h"

Atlas::Camera::Camera()
	: referencingNode(nullptr), forwardDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), translation(0.0f), nearPlane(0.1f), farPlane(100.0f), width(Global::Variables.screenWidth), height(Global::Variables.screenHeight), FOV(90.0f), oldMouseX(0.0), oldMouseY(0.0)
{

}

Atlas::Camera::Camera(const Camera& cam2)
	: referencingNode(cam2.referencingNode), forwardDirection(cam2.forwardDirection), upDirection(cam2.upDirection), translation(cam2.translation), FOV(cam2.FOV), nearPlane(cam2.nearPlane), farPlane(cam2.farPlane), height(cam2.height), width(cam2.width), oldMouseX(cam2.oldMouseX), oldMouseY(cam2.oldMouseY)
{

}

Atlas::Camera::~Camera()
{

}

glm::mat4 Atlas::Camera::GetViewMatrix()
{
	return glm::lookAt(translation, translation + forwardDirection, upDirection);
}

glm::mat4 Atlas::Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(FOV), ((float)width) / ((float)height), nearPlane, farPlane);
}

void Atlas::Camera::LookAt(glm::vec3 position)
{
	glm::vec3 resultingDirection = position - translation;
	forwardDirection = glm::normalize(resultingDirection);
}

void Atlas::Camera::LookAtMouse(float sensitivity, double xpos, double ypos)
{
	glm::vec2 mouseDelta(xpos - oldMouseX, ypos - oldMouseY);

	glm::vec3 toRotateAround = glm::cross(forwardDirection, upDirection);
	glm::vec3 vd;
	forwardDirection = glm::mat3(
		glm::rotate(glm::mat4(1.0f), -glm::radians(mouseDelta.x * sensitivity), upDirection) *
		glm::rotate(glm::mat4(1.0f), -glm::radians(mouseDelta.y * sensitivity), toRotateAround)
	) * forwardDirection;

	forwardDirection = glm::mat3() * forwardDirection;

	oldMouseX = xpos;
	oldMouseY = ypos;
}

void Atlas::Camera::MoveForward(float speed, float deltaTime)
{
	glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(forwardDirection.x, forwardDirection.z));
	translation.x += speed * normalizedViewDirection.x * deltaTime;
	translation.z += speed * normalizedViewDirection.y * deltaTime;
}

void Atlas::Camera::MoveBackward(float speed, float deltaTime)
{
	glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(forwardDirection.x, forwardDirection.z));
	translation.x += -speed * normalizedViewDirection.x * deltaTime;
	translation.z += -speed * normalizedViewDirection.y * deltaTime;
}

void Atlas::Camera::StrafeLeft(float speed, float deltaTime)
{
	glm::vec3 strafeDirection = glm::cross(forwardDirection, upDirection);
	glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
	translation.x += -speed * normalizedStrafeDirection.x * deltaTime;
	translation.z += -speed * normalizedStrafeDirection.y * deltaTime;
}

void Atlas::Camera::StrafeRight(float speed, float deltaTime)
{
	glm::vec3 strafeDirection = glm::cross(forwardDirection, upDirection);
	glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
	translation.x += speed * normalizedStrafeDirection.x * deltaTime;
	translation.z += speed * normalizedStrafeDirection.y * deltaTime;
}

void Atlas::Camera::MoveUp(float speed, float deltaTime)
{
	translation += speed * upDirection * deltaTime;
}

void Atlas::Camera::MoveDown(float speed, float deltaTime)
{
	translation += -speed * upDirection * deltaTime;
}

glm::vec3 Atlas::Camera::MoveForwardComponent(float speed, float deltaTime)
{
	glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(forwardDirection.x, forwardDirection.z));
	return glm::vec3(speed * normalizedViewDirection.x * deltaTime, 0.0f, speed * normalizedViewDirection.y * deltaTime);
}

glm::vec3 Atlas::Camera::MoveBackwardComponent(float speed, float deltaTime)
{
	glm::vec2 normalizedViewDirection = glm::normalize(glm::vec2(forwardDirection.x, forwardDirection.z));
	return glm::vec3(-speed * normalizedViewDirection.x * deltaTime, 0.0f, -speed * normalizedViewDirection.y * deltaTime);
}

glm::vec3 Atlas::Camera::StrafeLeftComponent(float speed, float deltaTime)
{
	glm::vec3 strafeDirection = glm::cross(forwardDirection, upDirection);
	glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
	return glm::vec3(-speed * normalizedStrafeDirection.x * deltaTime, 0.0f, -speed * normalizedStrafeDirection.y * deltaTime);
}

glm::vec3 Atlas::Camera::StrafeRightComponent(float speed, float deltaTime)
{
	glm::vec3 strafeDirection = glm::cross(forwardDirection, upDirection);
	glm::vec2 normalizedStrafeDirection = glm::normalize(glm::vec2(strafeDirection.x, strafeDirection.z));
	return glm::vec3(speed * normalizedStrafeDirection.x * deltaTime, 0.0f, speed * normalizedStrafeDirection.y * deltaTime);
}

glm::vec3 Atlas::Camera::MoveUpComponent(float speed, float deltaTime)
{
	return speed * upDirection * deltaTime;
}

glm::vec3 Atlas::Camera::MoveDownComponent(float speed, float deltaTime)
{
	return -speed * upDirection * deltaTime;
}

glm::vec3 Atlas::Camera::GetTranslation()
{
	return translation;
}

glm::vec3 Atlas::Camera::GetForwardDirection()
{
	return forwardDirection;
}

glm::vec3 Atlas::Camera::GetUpwardDirection()
{
	return upDirection;
}

void Atlas::Camera::SetTranslation(glm::vec3 newTranslation)
{
	translation = newTranslation;
}

void Atlas::Camera::SetWidth(int newWidth)
{
	width = newWidth;
}

void Atlas::Camera::SetHeight(int newHeight)
{
	height = newHeight;
}

void Atlas::Camera::Update(float deltaTime)
{

}

Atlas::Node* Atlas::Camera::GetReferencingNode()
{
	return referencingNode;
}

void Atlas::Camera::SetReferencingNode(Node* node)
{
	referencingNode = node;
}
