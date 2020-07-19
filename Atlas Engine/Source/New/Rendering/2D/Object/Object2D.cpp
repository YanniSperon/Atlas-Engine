#include "Object2D.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"
#include "New/System/Global/Global.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"

Atlas::Object2D::Object2D()
	: handle(nullptr), mesh(nullptr), shader(nullptr), texture(nullptr), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f), finalTransformation(1.0f)
{

}

Atlas::Object2D::Object2D(Object2D* itemToCopy)
	: handle(itemToCopy->GetVRAMHandle()), mesh(itemToCopy->GetMesh()), shader(itemToCopy->GetShader()), texture(itemToCopy->GetTexture()), localTranslation(itemToCopy->GetLocalTranslation()), localRotation(itemToCopy->GetLocalRotation()), localScale(itemToCopy->GetLocalScale()), finalTransformation(itemToCopy->GetFinalTransformation())
{

}

Atlas::Object2D::Object2D(Mesh2D* objectMesh, Shader* shdr, Texture* tex)
	: handle(Global::Variables.GetVRAMReference(objectMesh)), mesh(objectMesh), shader(shdr), texture(tex), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f), finalTransformation(1.0f)
{

}

Atlas::Object2D::Object2D(Mesh2D* objectMesh, const std::string& shader, const std::string& texture)
	: handle(Global::Variables.GetVRAMReference(objectMesh)), mesh(objectMesh), shader(Global::Variables.GetLoadedShader(shader)), texture(Global::Variables.GetLoadedTexture(texture)), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f), finalTransformation(1.0f)
{

}

Atlas::Object2D::Object2D(Mesh2D* objectMesh, const std::string& shader, Texture* tex)
	: handle(Global::Variables.GetVRAMReference(objectMesh)), mesh(objectMesh), shader(Global::Variables.GetLoadedShader(shader)), texture(Global::Variables.PrepareTexture(tex, this)), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f), finalTransformation(1.0f)
{

}

Atlas::Object2D::~Object2D()
{

}

void Atlas::Object2D::LoadIntoVRAM()
{
	printf("Loading into vram\n");
	glGenBuffers(1, &handle->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, handle->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->VertexBufferSize(), mesh->vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));

	glGenBuffers(1, &handle->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexBufferSize(), mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glFinish();
}

void Atlas::Object2D::UnloadFromVRAM()
{
	printf("Unloading from VRAM");
	glDeleteBuffers(1, &handle->vbo);
	glDeleteBuffers(1, &handle->ibo);
}

void Atlas::Object2D::Draw(glm::mat4 projection)
{
	Bind();
	shader->SetUniformMat4f("P", projection);
	shader->SetUniformMat4f("M", finalTransformation);
	glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, 0);
}

void Atlas::Object2D::Bind()
{
	shader->Bind();

	texture->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, handle->vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->ibo);
}

void Atlas::Object2D::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Atlas::Object2D::Update(float deltaTime)
{

}

Atlas::VRAMHandle* Atlas::Object2D::GetVRAMHandle()
{
	return handle;
}

Atlas::Shader* Atlas::Object2D::GetShader()
{
	return shader;
}

Atlas::Texture* Atlas::Object2D::GetTexture()
{
	return texture;
}

Atlas::Mesh2D* Atlas::Object2D::GetMesh()
{
	return mesh;
}

glm::mat4 Atlas::Object2D::GetFinalTransformation()
{
	return finalTransformation;
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

void Atlas::Object2D::SetFinalTransformation(glm::mat4 trans)
{
	finalTransformation = trans;
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

void* Atlas::Object2D::GetReferencingNode()
{
	return referencingNode;
}

void Atlas::Object2D::SetReferencingNode(void* node)
{
	referencingNode = node;
}
