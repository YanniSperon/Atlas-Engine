#include "Object3D.h"
#include "New/System/Global/Global.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"

Atlas::Object3D::Object3D()
	: Object(E_ObjectType::THREEDIMENSIONAL), mesh(Global::Variables.GetLoadedMesh("cube")), handle(Global::Variables.GetVRAMReference(Global::Variables.GetLoadedMesh("cube"))), shader(nullptr), texture(nullptr), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{

}

Atlas::Object3D::Object3D(Mesh3D* objectMesh, Shader* shdr, Texture* tex)
	: Object(E_ObjectType::THREEDIMENSIONAL), mesh(objectMesh), handle(Global::Variables.GetVRAMReference(objectMesh)), shader(shdr), texture(tex), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{

}

Atlas::Object3D::Object3D(const std::string& meshName, const std::string& shaderName, const std::string& textureName)
	: Object(E_ObjectType::THREEDIMENSIONAL), mesh(Global::Variables.GetLoadedMesh(meshName)), handle(Global::Variables.GetVRAMReference(Global::Variables.GetLoadedMesh(meshName))), shader(Global::Variables.GetLoadedShader(shaderName)), texture(Global::Variables.GetLoadedTexture(textureName)), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{

}

Atlas::Object3D::Object3D(const Object3D& obj2)
	: Object(obj2), handle(obj2.handle), shader(obj2.shader), texture(obj2.texture), mesh(obj2.mesh), localTranslation(obj2.localTranslation), localRotation(obj2.localRotation), localScale(obj2.localScale), finalTransformation(obj2.finalTransformation), referencingNode(obj2.referencingNode)
{
	// ADD THIS OBJECT AS A REFERENCING OBJECT TO THE SHADER, MESH, AND TEXTURE
}

Atlas::Object3D::~Object3D()
{
	// check cache and see if it is being used anywhere and if it isnt then delete the mesh
}

void Atlas::Object3D::Draw(glm::mat4 view, glm::mat4 projection)
{
	//Bind(model, view, projection);
	Bind();
	shader->SetUniformMat4f("P", projection);
	shader->SetUniformMat4f("V", view);
	shader->SetUniformMat4f("M", finalTransformation);
	glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, 0);
	//glm::mat4 model, glm::mat4 view, glm::mat4 projection
}

void Atlas::Object3D::Bind()
{
	shader->Bind();
	texture->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, handle->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->ibo);
}

void Atlas::Object3D::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Atlas::Object3D::Update(float deltaTime)
{

}

Atlas::VRAMHandle* Atlas::Object3D::GetVRAMHandle()
{
	return handle;
}

Atlas::Mesh3D* Atlas::Object3D::GetMesh()
{
	return mesh;
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

void Atlas::Object3D::SetFinalTransformation(glm::mat4 trans)
{
	finalTransformation = trans;
}

void Atlas::Object3D::SetVRAMHandle(VRAMHandle* newHandle)
{
	handle = newHandle;
}

void Atlas::Object3D::SetMesh(Mesh3D* newMesh)
{
	mesh = newMesh;
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

void* Atlas::Object3D::GetReferencingNode()
{
	return referencingNode;
}

void Atlas::Object3D::SetReferencingNode(void* node)
{
	referencingNode = node;
}
