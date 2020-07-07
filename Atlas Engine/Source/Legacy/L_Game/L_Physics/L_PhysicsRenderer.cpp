#include "L_PhysicsRenderer.h"
#include "Shared/S_Vendor/S_GLM/gtx/quaternion.hpp"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Legacy/L_Game/L_Player.h"

namespace L_Atlas {

	int GetUniformLocationPhysicsRenderer(const std::string& name, GLuint shaderID)
	{
		int location = glGetUniformLocation(shaderID, name.c_str());
		if (location == -1) {
			if (name == "lightPos" || name == "light.position") {
				return -5;
			}
			printf("Warning: uniform '%s' doesn't exist!\n", name.c_str());
		}
		return location;
	}

	void UseProgramPhysicsRenderer(GLuint program) {
		glUseProgram(program);
	}

	void SetUniformMat4fPhysicsRenderer(const std::string& name, const glm::mat4& matrix, GLuint shaderID)
	{
		glUniformMatrix4fv(GetUniformLocationPhysicsRenderer(name, shaderID), 1, GL_FALSE, &matrix[0][0]);
	}

	bool SetUniformVec3PhysicsRenderer(const std::string& name, const glm::vec3& vector, GLuint shaderID)
	{
		int temp = GetUniformLocationPhysicsRenderer(name, shaderID);
		if (temp >= 0) {
			glUniform3fv(temp, 1, &vector[0]);
			return true;
		}
		else {
			return false;
		}
	}

	void SetUniform1fPhysicsRenderer(const std::string& name, const float& value, GLuint shaderID)
	{
		glUniform1f(GetUniformLocationPhysicsRenderer(name, shaderID), value);
	}

	void L_PhysicsRenderer::Submit2D(L_Object2D* renderable)
	{
		renderQueue2D.push_back(renderable);
	}

	void L_PhysicsRenderer::Submit3D(L_PhysicsObject* renderable, glm::vec3 camPos)
	{
		if (!renderable->GetGLInitialized()) {
			renderable->GLInit();
		}
		glm::vec3 changeInValues = renderable->GetTranslation() - camPos;
		float distanceSquared = changeInValues.x * changeInValues.x + changeInValues.y * changeInValues.y;
		if (distanceSquared < 100.0f * 100.0f) {
			renderQueue3D.push_back(renderable);
		}
	}

	void L_PhysicsRenderer::Submit3DObject(L_Object* renderable, glm::vec3 camPos)
	{
		if (!renderable->GetGLInitialized()) {
			renderable->GLInit();
		}
		glm::vec3 changeInValues = renderable->GetTranslation() - camPos;
		float distanceSquared = changeInValues.x * changeInValues.x + changeInValues.y * changeInValues.y;
		if (distanceSquared < 100.0f * 100.0f) {
			renderQueueObject3D.push_back(renderable);
		}
	}

	void L_PhysicsRenderer::SubmitForceRender3D(L_PhysicsObject* renderable)
	{
		if (!renderable->GetGLInitialized()) {
			renderable->GLInit();
		}
		renderQueue3D.push_back(renderable);
	}

	void L_PhysicsRenderer::SubmitForceRender3DObject(L_Object* renderable)
	{
		if (!renderable->GetGLInitialized()) {
			renderable->GLInit();
		}
		renderQueueObject3D.push_back(renderable);
	}

	// THIS IS THE ONE IM USING
	void L_PhysicsRenderer::SimpleFlush(L_Player* camera, int width, int height, float FOV, L_PhysicsLight* light)
	{
		// Add vr stuff here
		glm::mat4 viewMatrix = camera->GetViewTransformMatrix();
		if (width != localWidthBuffer || height != localHeightBuffer) {
			if (width > 0 && height > 0) {
				projectionMatrix = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
				orthographicMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
			}
		}

		while (!renderQueue3D.empty()) {
			L_PhysicsObject* renderable = renderQueue3D.front();
			GLuint shaderID = renderable->GetShaderID();
			UseProgramPhysicsRenderer(shaderID);
			SetUniformMat4fPhysicsRenderer("P", projectionMatrix, shaderID);
			SetUniformMat4fPhysicsRenderer("V", viewMatrix, shaderID);
			SetUniformMat4fPhysicsRenderer("M", renderable->GetModelTransformMatrix(), shaderID);
			if (renderable->GetHasLighting()) {
				SetUniformVec3PhysicsRenderer("camPos", camera->GetTranslation(), shaderID);
				SetUniformVec3PhysicsRenderer("material.ambient", renderable->GetMaterial().ambient, shaderID);
				SetUniformVec3PhysicsRenderer("material.diffuse", renderable->GetMaterial().diffuse, shaderID);
				SetUniformVec3PhysicsRenderer("material.specular", renderable->GetMaterial().specular, shaderID);
				SetUniform1fPhysicsRenderer("material.shininess", renderable->GetMaterial().shininess, shaderID);
				if (!SetUniformVec3PhysicsRenderer("light.position", light->GetTranslation(), shaderID)) {
					renderable->SetHasLighting(false);
				}
				SetUniformVec3PhysicsRenderer("light.ambient", light->GetL_LightIntensity().ambient, shaderID);
				SetUniformVec3PhysicsRenderer("light.diffuse", light->GetL_LightIntensity().diffuse, shaderID);
				SetUniformVec3PhysicsRenderer("light.specular", light->GetL_LightIntensity().specular, shaderID);
			}
			renderable->Draw();
			renderQueue3D.pop_front();
		}

		while (!renderQueueObject3D.empty()) {
			L_Object* renderable = renderQueueObject3D.front();
			GLuint shaderID = renderable->GetShaderID();
			UseProgramPhysicsRenderer(shaderID);
			SetUniformMat4fPhysicsRenderer("P", projectionMatrix, shaderID);
			SetUniformMat4fPhysicsRenderer("V", viewMatrix, shaderID);
			SetUniformMat4fPhysicsRenderer("M", renderable->GetModelTransformMatrix(), shaderID);
			if (renderable->GetHasLighting()) {
				SetUniformVec3PhysicsRenderer("camPos", camera->GetTranslation(), shaderID);
				SetUniformVec3PhysicsRenderer("material.ambient", renderable->GetMaterial().ambient, shaderID);
				SetUniformVec3PhysicsRenderer("material.diffuse", renderable->GetMaterial().diffuse, shaderID);
				SetUniformVec3PhysicsRenderer("material.specular", renderable->GetMaterial().specular, shaderID);
				SetUniform1fPhysicsRenderer("material.shininess", renderable->GetMaterial().shininess, shaderID);
				if (!SetUniformVec3PhysicsRenderer("light.position", light->GetTranslation(), shaderID)) {
					renderable->SetHasLighting(false);
				}
				SetUniformVec3PhysicsRenderer("light.ambient", light->GetL_LightIntensity().ambient, shaderID);
				SetUniformVec3PhysicsRenderer("light.diffuse", light->GetL_LightIntensity().diffuse, shaderID);
				SetUniformVec3PhysicsRenderer("light.specular", light->GetL_LightIntensity().specular, shaderID);
			}
			renderable->Draw();
			renderQueueObject3D.pop_front();
		}

		while (!renderQueue2D.empty())
		{
			L_Object2D* renderable = renderQueue2D.front();
			GLuint shaderID = renderable->GetShaderID();
			UseProgramPhysicsRenderer(shaderID);
			SetUniformMat4fPhysicsRenderer("P", orthographicMatrix, shaderID);
			SetUniformMat4fPhysicsRenderer("M", renderable->GetModelTransformMatrix(), shaderID);
			renderable->Draw();
			renderQueue2D.pop_front();
		}
	}
}