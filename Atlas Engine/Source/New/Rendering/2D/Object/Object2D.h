#pragma once

#include "GL/glew.h"
#include "New/Mesh/2D/Mesh2D.h"
#include "New/Rendering/Shared/Texture/Texture.h"
#include "New/Rendering/Shared/Shader/Shader.h"
#include "New/Mesh/Shared/VRAM/VRAMHandle.h"
#include "New/Scene/Shared/Node/Node.h"

namespace Atlas {
	class Object2D {
	private:
		VRAMHandle* handle;
		Shader* shader;
		Texture* texture;
		Mesh2D* mesh;
		glm::vec2 localTranslation;
		float localRotation;
		glm::vec2 localScale;

		glm::mat4 finalTransformation;

		Node* referencingNode;
	public:
		Object2D();
		Object2D(Object2D* itemToCopy);
		Object2D(Mesh2D* objectMesh, Shader* shdr, Texture* tex);
		Object2D(Mesh2D* objectMesh, const std::string& shdr, Texture* tex);
		Object2D(Mesh2D* objectMesh, const std::string& shdr, const std::string& tex);
		Object2D(const std::string& objectMesh, const std::string& shdr, const std::string& tex);
		~Object2D();

		virtual void Draw(glm::mat4 projection);
		virtual void Bind();
		virtual void Unbind();

		void Update(float deltaTime);

		Mesh2D* GetMesh();
		VRAMHandle* GetVRAMHandle();
		Shader* GetShader();
		Texture* GetTexture();

		glm::mat4 GetFinalTransformation();
		glm::vec2 GetLocalTranslation();
		float GetLocalRotation();
		glm::vec2 GetLocalScale();

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::mat4 GetTransformationMatrix();
		glm::mat4 GetTranslationScaleMatrix();

		void SetMesh(Mesh2D* newMesh);
		void SetVRAMHandle(VRAMHandle* newVRAMHandle);
		void SetShader(Shader* newShader);
		void SetTexture(Texture* newTexture);

		void SetLocalTranslation(glm::vec2 newTranslation);
		void SetLocalRotation(float newRotation);
		void SetLocalScale(glm::vec2 newScale);

		void SetFinalTransformation(glm::mat4 trans);

		void AddTranslationOffset(glm::vec2 addTranslation);
		void AddRotationOffset(float addRotation);
		void AddScaleOffset(glm::vec2 addScale);

		Node* GetReferencingNode();
		void SetReferencingNode(Node* node);
	};
}