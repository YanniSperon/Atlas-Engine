#pragma once

#include "GL/glew.h"
#include "Mesh3D.h"
#include "Shader.h"
#include "Texture.h"
#include "Shared/S_Vendor/S_GLM/glm.hpp"

namespace Atlas {
	class Object3D {
	private:
		GLuint vbo;
		GLuint ibo;
		Shader* shader;
		Texture* texture;
		Mesh3D mesh;
		glm::vec3 localTranslation;
		glm::vec3 localRotation;
		glm::vec3 localScale;
	public:
		Object3D();
		Object3D(Mesh3D objectMesh, Shader* shdr, Texture* tex);
		~Object3D();

		void LoadIntoVRAM();
		void UnloadFromVRAM();

		void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
		//void Bind(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
		void Bind();
		void Unbind();


		void Update(float deltaTime);
		// this will contain a mesh, a physics body and much more customizable information such as
		// texture, shader, etc


		glm::vec3 GetLocalTranslation();
		glm::vec3 GetLocalRotation();
		glm::vec3 GetLocalScale();

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::mat4 GetTransformationMatrix();

		void SetLocalTranslation(glm::vec3 newTranslation);
		void SetLocalRotation(glm::vec3 newRotation);
		void SetLocalScale(glm::vec3 newScale);

		void AddTranslationOffset(glm::vec3 addTranslation);
		void AddRotationOffset(glm::vec3 addRotation);
		void AddScaleOffset(glm::vec3 addScale);
	};
}