#pragma once

#include "L_Object.h"
#include "GL/glew.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "L_Camera.h"
#include "L_Shader.h"
#include "Legacy/L_Rendering/L_GUI/L_Primitives/L_Object2D.h"
#include "Legacy/L_Rendering/L_GUI/L_Primitives/L_Font.h"
#include "Legacy/L_Rendering/L_GUI/L_Primitives/L_Sentence.h"
#include "L_Light.h"

namespace L_Atlas {

	class L_Renderer {
	public:
		static int GetUniformLocation(const std::string& name, GLuint shaderID)
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
		static void UseProgram(GLuint program) {
			glUseProgram(program);
		}
		static void SetUniformMat4f(const std::string& name, const glm::mat4& matrix, GLuint shaderID)
		{
			glUniformMatrix4fv(GetUniformLocation(name, shaderID), 1, GL_FALSE, &matrix[0][0]);
		}
		static bool SetUniformVec3(const std::string& name, const glm::vec3& vector, GLuint shaderID)
		{
			int temp = GetUniformLocation(name, shaderID);
			if (temp >= 0) {
				glUniform3fv(temp, 1, &vector[0]);
				return true;
			}
			else {
				return false;
			}
		}
		static void SetUniform1f(const std::string& name, const float& value, GLuint shaderID)
		{
			glUniform1f(GetUniformLocation(name, shaderID), value);
		}

		virtual void SubmitText(L_Sentence* renderable) = 0;
		virtual void Submit2D(L_Object2D* renderable) = 0;
		virtual void Submit3D(L_Object* renderable, glm::vec3 camPos) = 0;
		virtual void SubmitForceRender3D(L_Object* renderable) = 0;
		//virtual void Flush(Camera* camera, int width, int height, float FOV) = 0;
		//virtual void Flush(Camera* camera, int width, int height, float FOV, L_Light* light) = 0;
		//virtual void SimpleFlush(Camera* camera, int width, int height, float FOV) = 0;
		virtual void SimpleFlush(L_Camera* camera, int width, int height, float FOV, L_Light* light) = 0;
	};
}