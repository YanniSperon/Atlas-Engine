#pragma once

#include "New/Mesh/Shared/VRAM/VRAMHandle.h"
#include "New/Mesh/3D/Mesh3D.h"
#include "New/Rendering/Shared/Shader/Shader.h"
#include "New/Scene/Shared/Node/Node.h"
#include "New/Rendering/Shared/Texture/Texture.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include <string>

namespace Atlas {
	class Object3D : public Object {
	private:
		VRAMHandle* handle;
		Shader* shader;
		Texture* texture;
		Mesh3D* mesh;

		glm::vec3 localTranslation;
		glm::vec3 localRotation;
		glm::vec3 localScale;

		glm::mat4 finalTransformation;

		Node* referencingNode;
	public:
		Object3D();
		Object3D(Mesh3D* objectMesh, Shader* shdr, Texture* tex);
		Object3D(Mesh3D* objectMesh, Shader* shdr, Texture* tex);
		Object3D(const std::string& meshName, const std::string& shaderName, const std::string& textureName);
		Object3D(const Object3D& obj2);
		virtual ~Object3D();

		void Draw(glm::mat4 view, glm::mat4 projection);
		void Bind();
		void Unbind();

		void Update(float deltaTime);

		VRAMHandle* GetVRAMHandle();
		Mesh3D* GetMesh();

		glm::vec3 GetLocalTranslation();
		glm::vec3 GetLocalRotation();
		glm::vec3 GetLocalScale();

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::mat4 GetTransformationMatrix();
		glm::mat4 GetTranslationScaleMatrix();

		void SetFinalTransformation(glm::mat4 trans);

		void SetVRAMHandle(VRAMHandle* newHandle);
		void SetMesh(Mesh3D* newMesh);

		void SetLocalTranslation(glm::vec3 newTranslation);
		void SetLocalRotation(glm::vec3 newRotation);
		void SetLocalScale(glm::vec3 newScale);

		void AddTranslationOffset(glm::vec3 addTranslation);
		void AddRotationOffset(glm::vec3 addRotation);
		void AddScaleOffset(glm::vec3 addScale);

		void* GetReferencingNode();
		void SetReferencingNode(void* node);
	};
}