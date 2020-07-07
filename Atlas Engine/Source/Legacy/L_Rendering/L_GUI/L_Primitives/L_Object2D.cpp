#include "L_Object2D.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Global/L_Global.h"

namespace L_Atlas {
	L_Object2D::L_Object2D()
		: L_Mesh2D(), vertexBufferID(0), indexBufferID(0), numIndices(0), texID(0), shaderID(0)
	{

	}

	L_Object2D::L_Object2D(glm::vec2 minCorner, glm::vec2 maxCorner, float rot, glm::vec2 trans, glm::vec2 s, GLuint tex, GLuint shader, glm::vec2 minTexCoord, glm::vec2 maxTexCoord)
		: L_Mesh2D(minCorner, maxCorner, rot, trans, s, minTexCoord, maxTexCoord), shaderID(shader), texID(0)
	{
		texID = tex;

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));


		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

		numIndices = (GLsizei)GetShape().numIndices;

		GetShape().cleanUp();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	L_Object2D::~L_Object2D()
	{
		Unbind();
		glDeleteBuffers(1, &vertexBufferID);
		glDeleteBuffers(1, &indexBufferID);
	}

	void L_Object2D::Draw()
	{
		Bind();
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	}

	void L_Object2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	}

	void L_Object2D::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int L_Object2D::GetNumIndices()
	{
		return numIndices;
	}

	void L_Object2D::SetShader(GLuint id)
	{
		shaderID = id;
	}

	void L_Object2D::SetTexture(GLuint tex)
	{
		texID = tex;
	}

	GLuint L_Object2D::GetShaderID()
	{
		return shaderID;
	}

	GLuint L_Object2D::GetTextureID()
	{
		return texID;
	}

	std::string L_Object2D::GetType()
	{
		return "Object2D";
	}
}