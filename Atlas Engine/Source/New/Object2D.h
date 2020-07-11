#pragma once

#include "GL/glew.h"
#include "Mesh2D.h"
#include "Texture.h"
#include "Shader.h"

namespace Atlas {
	class Object2D {
	private:
		GLuint vbo;
		GLuint ibo;
		Shader* shader;
		Texture* texture;
		Mesh2D mesh;
		glm::vec2 localTranslation;
		float localRotation;
		glm::vec2 localScale;
	public:
		Object2D();
		Object2D(Mesh2D objectMesh, Shader* shdr, Texture* tex);
		~Object2D();

		void LoadIntoVRAM();
		void UnloadFromVRAM();

		void Draw(glm::mat4 model, glm::mat4 projection);
		void Bind();
		void Unbind();

		void Update(float deltaTime);

		glm::vec2 GetLocalTranslation();
		float GetLocalRotation();
		glm::vec2 GetLocalScale();

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::mat4 GetTransformationMatrix();
		glm::mat4 GetTranslationScaleMatrix();

		void SetLocalTranslation(glm::vec2 newTranslation);
		void SetLocalRotation(float newRotation);
		void SetLocalScale(glm::vec2 newScale);

		void AddTranslationOffset(glm::vec2 addTranslation);
		void AddRotationOffset(float addRotation);
		void AddScaleOffset(glm::vec2 addScale);
	};
}