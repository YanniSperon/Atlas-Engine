#pragma once

#include "L_Mesh2D.h"

namespace L_Atlas {
	class L_Object2D : public L_Mesh2D {
	private:
		GLuint vertexBufferID;
		GLuint indexBufferID;
		GLuint texID;
		GLuint shaderID;
		GLsizei numIndices;
	public:
		L_Object2D();
		L_Object2D(glm::vec2 minCorner, glm::vec2 maxCorner, float rot, glm::vec2 trans, glm::vec2 s, GLuint tex, GLuint shader, glm::vec2 minTexCoord, glm::vec2 maxTexCoord);
		~L_Object2D();


		void Draw();
		void Bind();
		void Unbind();
		unsigned int GetNumIndices();
		void SetShader(GLuint id);
		void SetTexture(GLuint tex);
		GLuint GetShaderID();
		GLuint GetTextureID();

		virtual std::string GetType() override;
	};
}