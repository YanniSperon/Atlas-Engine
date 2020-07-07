#include "L_PhysicsObject.h"
#include "Legacy/L_Global/L_Global.h"
#include <algorithm>
#include "Legacy/L_Other/L_Convert.h"
#include "Legacy/L_System/L_System.h"
#include "Legacy/L_Rendering/L_Scene/L_Loader.h"
#include "Shared/S_Vendor/S_GLM/gtc/matrix_transform.hpp"
#include "Shared/S_Vendor/S_GLM/gtx/euler_angles.hpp"
//#include "glm/gtx/quaternion.hpp"

namespace L_Atlas {

	L_PhysicsObject::L_PhysicsObject()
		: uid(0), vertexBufferID(0), indexBufferID(0), texID(0), shaderID(0), numIndices(0), material(), glInitialized(false), textureDirectory(""), textureName(""), shaderDirectory(""), shaderName(""), hasLighting(false), physicsObject(NULL)
	{
	}

	L_PhysicsObject::L_PhysicsObject(L_Object* obj, float mass)
		: L_Mesh(obj->GetTypeEnum(), obj->GetModelFileDirectory(), obj->GetModelFileName(), obj->GetRotation(), obj->GetTranslation(), obj->GetScale()), glInitialized(false)
	{
		textureDirectory = obj->GetTextureDirectory();
		textureName = obj->GetTextureName();
		shaderDirectory = obj->GetShaderDirectory();
		shaderName = obj->GetShaderName();
		hasLighting = obj->GetHasLighting();
		material = obj->GetMaterial();
		//if (Global::Variables.textureCache.find(obj->GetTextureDirectory() + obj->GetTextureName()) != Global::Variables.textureCache.end()) {
		//	texID = Global::Variables.textureCache[obj->GetTextureDirectory() + obj->GetTextureName()];
		//}
		//else {
		//	std::string file = obj->GetTextureDirectory() + obj->GetTextureName();
		//	std::replace(file.begin(), file.end(), '\\', '/');
		//	std::string physicalLocation = "";
		//
		//	file = System::ConvertFilePathToLocal(file);
		//	Filepath pathtemp = System::SeperateFilepath(file);
		//	std::string textureDir = pathtemp.directory;
		//	std::string texName = pathtemp.filename;
		//	physicalLocation = pathtemp.directory + pathtemp.filename;
		//
		//	Global::Variables.loadedTextureCache[texName] = physicalLocation;
		//
		//	Global::Variables.textureCache[textureDir + texName] = Loader::LoadTexture(textureDir, texName, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		//	texID = Global::Variables.textureCache[textureDir + texName];
		//}
		//
		//if (Global::Variables.shaderCache.find(obj->GetShaderDirectory() + obj->GetShaderName()) != Global::Variables.shaderCache.end()) {
		//	shaderID = Global::Variables.shaderCache[obj->GetShaderDirectory() + obj->GetShaderName()]->GetShaderID();
		//}
		//else {
		//	std::string file = obj->GetShaderDirectory() + obj->GetShaderName();
		//	std::replace(file.begin(), file.end(), '\\', '/');
		//	std::string physicalLocation = "";
		//
		//	file = System::ConvertFilePathToLocal(file);
		//	Filepath pathtemp = System::SeperateFilepath(file);
		//	std::string shadrDirectory = pathtemp.directory;
		//	std::string shadrName = pathtemp.filename;
		//	physicalLocation = pathtemp.directory + pathtemp.filename;
		//
		//	Global::Variables.loadedShaderCache[shadrName] = physicalLocation;
		//
		//	Global::Variables.shaderCache[shadrDirectory + shadrName] = new Shader(shadrDirectory + shadrName);
		//	shaderID = Global::Variables.shaderCache[shadrDirectory + shadrName]->GetShaderID();
		//}
		//numIndices = (GLsizei)GetShape().numIndices;

		vertexBufferID = obj->GetVBO();
		indexBufferID = obj->GetIBO();
		texID = obj->GetTextureID();
		shaderID = obj->GetShaderID();
		numIndices = obj->GetNumIndices();
		uid = obj->GetUID();
		
		btCollisionShape* physicsShape = new btBoxShape(L_Convert::Vector3(GetShape().max));
		physicsShape->setLocalScaling(L_Convert::Vector3(obj->GetScale()));
		btTransform shapeTransformation;
		shapeTransformation.setFromOpenGLMatrix(&GetModelTransRotMatrix()[0][0]);
		physicsObject = L_PhysicsEngine::AddPhysicsBody(physicsShape, shapeTransformation, mass, this);

		if (obj->GetGLInitialized()) {
			GLInit();
		}
	}

	L_PhysicsObject::~L_PhysicsObject()
	{

	}

	void L_PhysicsObject::Update()
	{
		if (physicsObject != NULL) {
			TranslateVec3(L_Convert::Vector3(physicsObject->getWorldTransform().getOrigin()));
			glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			physicsObject->getWorldTransform().getRotation().getEulerZYX(rotation.z, rotation.y, rotation.x);
			RotateVec3(rotation);
		}
	}

	void L_PhysicsObject::InverseUpdate()
	{
		if (physicsObject != NULL) {
			btTransform transform;
			transform.setIdentity();
			transform.setFromOpenGLMatrix(&GetModelTransRotMatrix()[0][0]);
			physicsObject->setWorldTransform(transform);
		}
	}

	glm::mat4 L_PhysicsObject::GetModelTransformMatrix()
	{
		glm::mat4 returnMat4;
		if (physicsObject != NULL) {
			physicsObject->getWorldTransform().getOpenGLMatrix(&returnMat4[0][0]);
		}
		else {
			returnMat4 = (glm::translate(glm::mat4(), GetTranslation()) * glm::yawPitchRoll(glm::radians(GetRotation().x), glm::radians(GetRotation().y), glm::radians(GetRotation().z)) * glm::scale(glm::mat4(), GetScale()));
		}
		return returnMat4 * glm::scale(glm::mat4(), GetScale());

	}

	bool L_PhysicsObject::GetGLInitialized()
	{
		return glInitialized;
	}

	L_Material L_PhysicsObject::GetMaterial()
	{
		return material;
	}

	bool L_PhysicsObject::GetHasLighting()
	{
		return hasLighting;
	}

	GLuint L_PhysicsObject::GetShaderID()
	{
		return shaderID;
	}

	GLuint L_PhysicsObject::GetTextureID()
	{
		return texID;
	}

	GLuint L_PhysicsObject::GetVBO()
	{
		return vertexBufferID;
	}

	btCollisionObject* L_PhysicsObject::GetL_PhysicsObject()
	{
		return physicsObject;
	}

	unsigned long long int L_PhysicsObject::GetUID()
	{
		return uid;
	}

	void L_PhysicsObject::SetHasLighting(bool newValue)
	{
		hasLighting = newValue;
	}

	void L_PhysicsObject::Launch(glm::vec3 viewDirection)
	{
		btRigidBody* body = btRigidBody::upcast(physicsObject);
		if (body != NULL) {
			body->setLinearVelocity(L_Convert::Vector3(50.0f * viewDirection));
			glm::normalize(viewDirection);
		}
	}

	void L_PhysicsObject::Draw()
	{
		Bind();
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	}

	void L_PhysicsObject::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	}

	void L_PhysicsObject::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void L_PhysicsObject::PrepareForDeletion()
	{
		L_BulletPhysicsObject* userPtr = (L_BulletPhysicsObject*)physicsObject->getUserPointer();
		delete userPtr;
		physicsObject->setUserPointer(NULL);
		L_PhysicsEngine::RemovePhysicsBody(physicsObject);
	}

	void L_PhysicsObject::GLInit()
	{
		glInitialized = true;

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 5));



		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);



		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glFinish();
	}
}