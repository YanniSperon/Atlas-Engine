#include "Object3D.h"
#include "New/System/Global/Global.h"
#include "New/Mesh/Shared/Generator/MeshGenerator.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"

Atlas::Object3D::Object3D()
	: Object(E_ObjectType::THREEDIMENSIONAL), mesh(Global::Variables.mesh3DManager.LoadMesh("cube")), handle(Global::Variables.mesh3DManager.GetVRAMHandle(mesh)), shader(nullptr), texture(nullptr), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{
	Global::Variables.mesh3DManager.AddReference(this);
}

Atlas::Object3D::Object3D(Mesh3D* objectMesh, Shader* shdr, Texture* tex)
	: Object(E_ObjectType::THREEDIMENSIONAL), mesh(Global::Variables.mesh3DManager.GetMesh(objectMesh)), handle(Global::Variables.mesh3DManager.GetVRAMHandle(objectMesh)), shader(Global::Variables.shaderManager.GetShader(shdr)), texture(Global::Variables.textureManager.GetTexture(tex)), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{
	Global::Variables.mesh3DManager.AddReference(this);
	Global::Variables.shaderManager.AddReference(this);
	Global::Variables.textureManager.AddReference(this);
}

Atlas::Object3D::Object3D(const std::string& meshName, const std::string& shaderName, const std::string& textureName)
	: Object(E_ObjectType::THREEDIMENSIONAL), mesh(Global::Variables.mesh3DManager.LoadMesh(meshName)), handle(Global::Variables.mesh3DManager.GetVRAMHandle(mesh)), shader(Global::Variables.shaderManager.LoadShader(shaderName)), texture(Global::Variables.textureManager.LoadTexture(textureName)), localTranslation(0.0f), localRotation(0.0f), localScale(1.0f)
{
	Global::Variables.mesh3DManager.AddReference(this);
	Global::Variables.shaderManager.AddReference(this);
	Global::Variables.textureManager.AddReference(this);
}

Atlas::Object3D::Object3D(const Object3D& obj2)
	: Object(obj2), handle(obj2.handle), shader(obj2.shader), texture(obj2.texture), mesh(obj2.mesh), localTranslation(obj2.localTranslation), localRotation(obj2.localRotation), localScale(obj2.localScale), finalTransformation(obj2.finalTransformation), referencingNode(obj2.referencingNode)
{
	Global::Variables.mesh3DManager.AddReference(this);
	Global::Variables.shaderManager.AddReference(this);
	Global::Variables.textureManager.AddReference(this);
}

Atlas::Object3D::~Object3D()
{
	Global::Variables.mesh3DManager.DeleteReference(this);
	Global::Variables.shaderManager.DeleteReference(this);
	Global::Variables.textureManager.DeleteReference(this);
}

void Atlas::Object3D::Draw(glm::mat4 view, glm::mat4 projection)
{
	Bind();
	shader->SetUniformMat4f("P", projection);
	shader->SetUniformMat4f("V", view);
	shader->SetUniformMat4f("M", finalTransformation);
	glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, 0);
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

Atlas::Shader* Atlas::Object3D::GetShader()
{
	return shader;
}

Atlas::Texture* Atlas::Object3D::GetTexture()
{
	return texture;
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

void Atlas::Object3D::SetShader(Shader* newShader)
{
	shader = newShader;
}

void Atlas::Object3D::SetTexture(Texture* newTexture)
{
	texture = newTexture;
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

Atlas::Node* Atlas::Object3D::GetReferencingNode()
{
	return referencingNode;
}

void Atlas::Object3D::SetReferencingNode(Node* node)
{
	referencingNode = node;
}
