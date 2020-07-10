#include "Object3D.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"

Atlas::Object3D::Object3D()
	: ibo(0), vbo(0), mesh(), shader(NULL), texture(NULL), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{

}

Atlas::Object3D::Object3D(Mesh3D objectMesh, Shader* shdr, Texture* tex)
	: ibo(0), vbo(0), mesh(objectMesh), shader(shdr), texture(tex), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{

}

Atlas::Object3D::~Object3D()
{
	// check cache and see if it is being used anywhere and if it isnt then delete the mesh
}

void Atlas::Object3D::LoadIntoVRAM()
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

void Atlas::Object3D::UnloadFromVRAM()
{
	printf("Unloading from VRAM");
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Atlas::Object3D::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	//Bind(model, view, projection);
	Bind();
	shader->SetUniformMat4f("P", projection);
	shader->SetUniformMat4f("V", view);
	shader->SetUniformMat4f("M", model);
	glDrawElements(GL_TRIANGLES, mesh.numIndices, GL_UNSIGNED_INT, 0);
	//glm::mat4 model, glm::mat4 view, glm::mat4 projection
}

void Atlas::Object3D::Bind()
{
	shader->Bind();

	texture->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Atlas::Object3D::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Atlas::Object3D::Update(float deltaTime)
{

}

glm::vec3 Atlas::Object3D::GetLocalTranslation()
{
	return localTranslation;
}

glm::vec3 Atlas::Object3D::GetLocalRotation()
{
	return localRotation;
}

glm::vec3 Atlas::Object3D::GetLocalScale()
{
	return localScale;
}

glm::mat4 Atlas::Object3D::GetTranslationMatrix()
{
	return glm::translate(glm::mat4(), localTranslation);
}

glm::mat4 Atlas::Object3D::GetRotationMatrix()
{
	return glm::yawPitchRoll(glm::radians(localRotation.x), glm::radians(localRotation.y), glm::radians(localRotation.z));
}

glm::mat4 Atlas::Object3D::GetScaleMatrix()
{
	return glm::scale(glm::mat4(), localScale);
}

glm::mat4 Atlas::Object3D::GetTransformationMatrix()
{
	return glm::translate(glm::mat4(), localTranslation) * glm::yawPitchRoll(glm::radians(localRotation.x), glm::radians(localRotation.y), glm::radians(localRotation.z)) * glm::scale(glm::mat4(), localScale);
}

glm::mat4 Atlas::Object3D::GetTranslationScaleMatrix()
{
	return glm::translate(glm::mat4(), localTranslation) * glm::scale(glm::mat4(), localScale);
}

void Atlas::Object3D::SetLocalTranslation(glm::vec3 newTranslation)
{
	localTranslation = newTranslation;
}

void Atlas::Object3D::SetLocalRotation(glm::vec3 newRotation)
{
	localRotation = newRotation;
}

void Atlas::Object3D::SetLocalScale(glm::vec3 newScale)
{
	localScale = newScale;
}

void Atlas::Object3D::AddTranslationOffset(glm::vec3 addTranslation)
{
	localTranslation += addTranslation;
}

void Atlas::Object3D::AddRotationOffset(glm::vec3 addRotation)
{
	localRotation += addRotation;
}

void Atlas::Object3D::AddScaleOffset(glm::vec3 addScale)
{
	localScale += addScale;
}
