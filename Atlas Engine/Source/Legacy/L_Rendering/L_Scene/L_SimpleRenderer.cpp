#include "L_SimpleRenderer.h"
#include "Shared/S_Vendor/S_GLM/gtx/quaternion.hpp"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Legacy/L_Game/L_Player.h"

namespace L_Atlas {

	int GetUniformLocation(const std::string& name, GLuint shaderID)
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

	void UseProgram(GLuint program) {
		glUseProgram(program);
	}

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix, GLuint shaderID)
	{
		glUniformMatrix4fv(GetUniformLocation(name, shaderID), 1, GL_FALSE, &matrix[0][0]);
	}

	bool SetUniformVec3(const std::string& name, const glm::vec3& vector, GLuint shaderID)
	{
		int temp = GetUniformLocation(name, shaderID);
		if (temp >= 0) {
			glUniform3fv(temp, 1, &vector[0]);
			return true;
		} else {
			return false;
		}
	}

	void SetUniform1f(const std::string& name, const float& value, GLuint shaderID)
	{
		glUniform1f(GetUniformLocation(name, shaderID), value);
	}

	void L_SimpleRenderer::SubmitText(L_Sentence* renderable)
	{
		renderQueueText.push_back(renderable);
	}

	void L_SimpleRenderer::Submit2D(L_Object2D* renderable)
	{
		renderQueue2D.push_back(renderable);
	}

	void L_SimpleRenderer::Submit3D(L_Object* renderable, glm::vec3 camPos)
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

	void L_SimpleRenderer::SubmitForceRender3D(L_Object* renderable)
	{
		if (!renderable->GetGLInitialized()) {
			renderable->GLInit();
		}
		renderQueue3D.push_back(renderable);
	}

	// THIS IS THE ONE IM USING
	void L_SimpleRenderer::SimpleFlush(L_Camera* camera, int width, int height, float FOV, L_Light* light)
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
			L_Object* renderable = renderQueue3D.front();
			GLuint shaderID = renderable->GetShaderID();
			UseProgram(shaderID);
			SetUniformMat4f("P", projectionMatrix, shaderID);
			SetUniformMat4f("V", viewMatrix, shaderID);
			SetUniformMat4f("M", renderable->GetModelTransformMatrix(), shaderID);
			if (renderable->GetHasLighting()) {
				SetUniformVec3("camPos", camera->GetTranslation(), shaderID);
				SetUniformVec3("material.ambient", renderable->GetMaterial().ambient, shaderID);
				SetUniformVec3("material.diffuse", renderable->GetMaterial().diffuse, shaderID);
				SetUniformVec3("material.specular", renderable->GetMaterial().specular, shaderID);
				SetUniform1f("material.shininess", renderable->GetMaterial().shininess, shaderID);
				if (!SetUniformVec3("light.position", light->GetTranslation(), shaderID)) {
					renderable->SetHasLighting(false);
				}
				SetUniformVec3("light.ambient", light->GetLightIntensity().ambient, shaderID);
				SetUniformVec3("light.diffuse", light->GetLightIntensity().diffuse, shaderID);
				SetUniformVec3("light.specular", light->GetLightIntensity().specular, shaderID);
			}
			renderable->Draw();
			renderQueue3D.pop_front();
		}

		while (!renderQueue2D.empty())
		{
			L_Object2D* renderable = renderQueue2D.front();
			GLuint shaderID = renderable->GetShaderID();
			UseProgram(shaderID);
			SetUniformMat4f("P", orthographicMatrix, shaderID);
			SetUniformMat4f("M", renderable->GetModelTransformMatrix(), shaderID);
			renderable->Draw();
			renderQueue2D.pop_front();
		}

		glDisable(GL_DEPTH_TEST);
		while (!renderQueueText.empty())
		{
			L_Sentence* renderable = renderQueueText.front();
			renderable->GetFont()->RenderText(renderable->GetShader(), renderable->GetText(), renderable->GetPosition().x, renderable->GetPosition().y, renderable->GetScale(), renderable->GetColor(), orthographicMatrix);
			//renderable->Draw(projectionMatrix);
			renderQueueText.pop_front();
		}
		glEnable(GL_DEPTH_TEST);
	}

	//void SimpleRenderer::Flush(Camera* camera, int width, int height, float FOV)
	//{
	//	glm::mat4 viewMatrix = camera->GetViewTransformMatrix();
	//	if (width != localWidthBuffer || height != localHeightBuffer) {
	//		if (width > 0 && height > 0) {
	//			projectionMatrix = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
	//			orthographicMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
	//		}
	//	}
	//	GLuint pastShader = 0;
	//	while (!renderQueue3D.empty())
	//	{
	//		L_Object* renderable = renderQueue3D.front();
	//		GLuint shaderID = renderable->GetShaderID();
	//		if (shaderID != pastShader) {
	//			UseProgram(shaderID);
	//			SetUniformMat4f("V", viewMatrix, shaderID);
	//			SetUniformMat4f("P", projectionMatrix, shaderID);
	//			SetUniformVec3("camPos", camera->GetTranslation(), shaderID);
	//			if (!SetUniformVec3("lightPos", glm::vec3(0.0f, 5.0f, 0.0f), shaderID)) {
	//				renderable->SetHasLighting(false);
	//			}
	//			pastShader = shaderID;
	//		}
	//		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
	//		renderable->Draw();
	//		renderQueue3D.pop_front();
	//	}
	//	while (!renderQueue2D.empty())
	//	{
	//		Object2D* renderable = renderQueue2D.front();
	//		GLuint shaderID = renderable->GetShaderID();
	//		if (shaderID != pastShader) {
	//			UseProgram(shaderID);
	//			pastShader = shaderID;
	//			SetUniformMat4f("P", orthographicMatrix, pastShader);
	//		}
	//		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
	//		renderable->Draw();
	//		renderQueue2D.pop_front();
	//	}
	//	glDisable(GL_DEPTH_TEST);
	//	while (!renderQueueText.empty())
	//	{
	//		Sentence* renderable = renderQueueText.front();
	//		renderable->GetFont()->RenderText(renderable->GetShader(), renderable->GetText(), renderable->GetPosition().x, renderable->GetPosition().y, renderable->GetScale(), renderable->GetColor(), orthographicMatrix);
	//		//renderable->Draw(projectionMatrix);
	//		renderQueueText.pop_front();
	//	}
	//	glEnable(GL_DEPTH_TEST);
	//}
	//
	//void SimpleRenderer::Flush(Camera* camera, int width, int height, float FOV, L_Light* light)
	//{
	//	glm::mat4 viewMatrix = camera->GetViewTransformMatrix();
	//	if (width != localWidthBuffer || height != localHeightBuffer) {
	//		if (width > 0 && height > 0) {
	//			projectionMatrix = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
	//			orthographicMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
	//		}
	//	}
	//	GLuint pastShader = 0;
	//	while (!renderQueue3D.empty())
	//	{
	//		L_Object* renderable = renderQueue3D.front();
	//		GLuint shaderID = renderable->GetShaderID();
	//		if (shaderID != pastShader) {
	//			UseProgram(shaderID);
	//			SetUniformMat4f("V", viewMatrix, shaderID);
	//			SetUniformMat4f("P", projectionMatrix, shaderID);
	//			SetUniformVec3("camPos", camera->GetTranslation(), shaderID);
	//			pastShader = shaderID;
	//		}
	//		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
	//		renderable->Draw();
	//		renderQueue3D.pop_front();
	//	}
	//	GLuint shaderID = light->GetShaderID();
	//	if (shaderID != pastShader) {
	//		UseProgram(shaderID);
	//		SetUniformMat4f("V", viewMatrix, shaderID);
	//		SetUniformMat4f("P", projectionMatrix, shaderID);
	//		SetUniformVec3("camPos", camera->GetTranslation(), shaderID);
	//		SetUniformVec3("light.position", light->GetTranslation(), shaderID);
	//		pastShader = shaderID;
	//	}
	//	SetUniformMat4f("M", light->GetModelTransformMatrix(), pastShader);
	//	light->Draw();
	//	while (!renderQueue2D.empty())
	//	{
	//		Object2D* renderable = renderQueue2D.front();
	//		GLuint shaderID = renderable->GetShaderID();
	//		if (shaderID != pastShader) {
	//			UseProgram(shaderID);
	//			pastShader = shaderID;
	//			SetUniformMat4f("P", orthographicMatrix, pastShader);
	//		}
	//		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
	//		renderable->Draw();
	//		renderQueue2D.pop_front();
	//	}
	//	glDisable(GL_DEPTH_TEST);
	//	while (!renderQueueText.empty())
	//	{
	//		Sentence* renderable = renderQueueText.front();
	//		renderable->GetFont()->RenderText(renderable->GetShader(), renderable->GetText(), renderable->GetPosition().x, renderable->GetPosition().y, renderable->GetScale(), renderable->GetColor(), orthographicMatrix);
	//		//renderable->Draw(projectionMatrix);
	//		renderQueueText.pop_front();
	//	}
	//	glEnable(GL_DEPTH_TEST);
	//}
	//
	//void SimpleRenderer::SimpleFlush(Camera* camera, int width, int height, float FOV)
	//{
	//	glm::mat4 viewMatrix = camera->GetViewTransformMatrix();
	//	if (width != localWidthBuffer || height != localHeightBuffer) {
	//		if (width > 0 && height > 0) {
	//			projectionMatrix = glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
	//			orthographicMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
	//		}
	//	}
	//	while (!renderQueue3D.empty()) {
	//		L_Object* renderable = renderQueue3D.front();
	//		GLuint shaderID = renderable->GetShaderID();
	//		UseProgram(shaderID);
	//		SetUniformMat4f("P", projectionMatrix, shaderID);
	//		SetUniformMat4f("V", viewMatrix, shaderID);
	//		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), shaderID);
	//		SetUniformVec3("camPos", camera->GetTranslation(), shaderID);
	//		SetUniformVec3("material.ambient", renderable->GetMaterial().ambient, shaderID);
	//		SetUniformVec3("material.diffuse", renderable->GetMaterial().diffuse, shaderID);
	//		SetUniformVec3("material.specular", renderable->GetMaterial().specular, shaderID);
	//		SetUniform1f("material.shininess", renderable->GetMaterial().shininess, shaderID);
	//		if (SetUniformVec3("light.position", glm::vec3(0.0f, 5.0f, 0.0f), shaderID)) {
	//			renderable->SetHasLighting(false);
	//		}
	//		SetUniformVec3("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f), shaderID);
	//		SetUniformVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f), shaderID);
	//		SetUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f), shaderID);
	//		renderable->Draw();
	//		renderQueue3D.pop_front();
	//	}
	//	while (!renderQueue2D.empty())
	//	{
	//		Object2D* renderable = renderQueue2D.front();
	//		GLuint shaderID = renderable->GetShaderID();
	//		UseProgram(shaderID);
	//		SetUniformMat4f("P", orthographicMatrix, shaderID);
	//		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), shaderID);
	//		renderable->Draw();
	//		renderQueue2D.pop_front();
	//	}
	//	glDisable(GL_DEPTH_TEST);
	//	while (!renderQueueText.empty())
	//	{
	//		Sentence* renderable = renderQueueText.front();
	//		renderable->GetFont()->RenderText(renderable->GetShader(), renderable->GetText(), renderable->GetPosition().x, renderable->GetPosition().y, renderable->GetScale(), renderable->GetColor(), orthographicMatrix);
	//		//renderable->Draw(projectionMatrix);
	//		renderQueueText.pop_front();
	//	}
	//	glEnable(GL_DEPTH_TEST);
	//}
}