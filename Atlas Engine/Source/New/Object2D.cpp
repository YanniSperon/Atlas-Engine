#include "Object2D.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"

Atlas::Object2D::Object2D()
	: ibo(0), vbo(0), mesh(), shader(nullptr), texture(nullptr), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{

}

Atlas::Object2D::Object2D(Mesh2D objectMesh, Shader* shdr, Texture* tex)
	: ibo(0), vbo(0), mesh(objectMesh), shader(shdr), texture(tex), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{
}

Atlas::Object2D::~Object2D()
{

}

void Atlas::Object2D::LoadIntoVRAM()
{
	printf("Loading into vram\n");
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.VertexBufferSize(), mesh.vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.IndexBufferSize(), mesh.indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glFinish();
}

void Atlas::Object2D::UnloadFromVRAM()
{
	printf("Unloading from VRAM");
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Atlas::Object2D::Draw(glm::mat4 model, glm::mat4 projection)
{
	Bind();
	shader->SetUniformMat4f("P", projection);
	shader->SetUniformMat4f("M", model);
	glDrawElements(GL_TRIANGLES, mesh.numIndices, GL_UNSIGNED_INT, 0);
}

void Atlas::Object2D::Bind()
{
	shader->Bind();

	texture->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Atlas::Object2D::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Atlas::Object2D::Update(float deltaTime)
{

}

glm::vec2 Atlas::Object2D::GetLocalTranslation()
{
	return localTranslation;
}

float Atlas::Object2D::GetLocalRotation()
{
	return localRotation;
}

glm::vec2 Atlas::Object2D::GetLocalScale()
{
	return localScale;
}

glm::mat4 Atlas::Object2D::GetTranslationMatrix()
{
	return glm::translate(glm::mat4(), glm::vec3(localTranslation, 0.0f));
}

glm::mat4 Atlas::Object2D::GetRotationMatrix()
{
	return glm::yawPitchRoll(0.0f, 0.0f, glm::radians(localRotation));
}

glm::mat4 Atlas::Object2D::GetScaleMatrix()
{
	return glm::scale(glm::mat4(), glm::vec3(localScale, 1.0f));
}

glm::mat4 Atlas::Object2D::GetTransformationMatrix()
{
	return glm::translate(glm::mat4(), glm::vec3(localTranslation, 0.0f)) * glm::yawPitchRoll(glm::radians(0.0f), glm::radians(0.0f), glm::radians(localRotation)) * glm::scale(glm::mat4(), glm::vec3(localScale, 1.0f));
}

glm::mat4 Atlas::Object2D::GetTranslationScaleMatrix()
{
	return glm::translate(glm::mat4(), glm::vec3(localTranslation, 0.0f)) * glm::scale(glm::mat4(), glm::vec3(localScale, 1.0f));
}

void Atlas::Object2D::SetLocalTranslation(glm::vec2 newTranslation)
{
	localTranslation = newTranslation;
}

void Atlas::Object2D::SetLocalRotation(float newRotation)
{
	localRotation = newRotation;
}

void Atlas::Object2D::SetLocalScale(glm::vec2 newScale)
{
	localScale = newScale;
}

void Atlas::Object2D::AddTranslationOffset(glm::vec2 addTranslation)
{
	localTranslation += addTranslation;
}

void Atlas::Object2D::AddRotationOffset(float addRotation)
{
	localRotation += addRotation;
}

void Atlas::Object2D::AddScaleOffset(glm::vec2 addScale)
{
	localScale += addScale;
}
