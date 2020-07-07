#pragma once

#include "Shared/S_Vendor/S_GLM/glm.hpp"
#include "Legacy/L_Rendering/L_Primitives/L_ShapeData.h"
#include <string>

namespace L_Atlas {

	enum L_Type
	{
		cubeModel, normalModel, skyBox, cubeInvertedLighting
	};

	class L_Mesh {
	private:
		std::string directory;
		std::string fileName;
		glm::vec3 rotation;
		glm::vec3 translation;
		glm::vec3 scale;
		L_ShapeData shape;
		glm::vec3 minExtents;
		glm::vec3 maxExtents;
		L_Type objectType;
	public:
		L_Mesh();
		L_Mesh(L_Type type, std::string dir, std::string name);
		L_Mesh(L_Type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 s);
		~L_Mesh();

		virtual glm::mat4 GetModelTransformMatrix();
		glm::mat4 GetModelTransRotMatrix();
		void RotateX(float x);
		void RotateY(float y);
		void RotateZ(float z);
		void Rotate3f(float x, float y, float z);
		void RotateVec3(glm::vec3 rot);
		void RotateAdd3f(float x, float y, float z);
		void RotateAddVec3(glm::vec3 rot);
		void TranslateX(float x);
		void TranslateY(float y);
		void TranslateZ(float z);
		void Translate3f(float x, float y, float z);
		void TranslateVec3(glm::vec3 trans);
		void TranslateAdd3f(float x, float y, float z);
		void TranslateAddVec3(glm::vec3 trans);
		void ScaleX(float x);
		void ScaleY(float y);
		void ScaleZ(float z);
		void Scale3f(float x, float y, float z);
		void ScaleVec3(glm::vec3 s);
		void ScaleAdd3f(float x, float y, float z);
		void ScaleAddVec3(glm::vec3 s);

		glm::vec3 GetTranslation();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();
		L_ShapeData GetShape();
		std::string GetModelFileName();
		std::string GetModelFileDirectory();
		void SetShape(L_ShapeData newShape);

		std::string GetModelType();
		virtual std::string GetType();
		L_Type GetTypeEnum();

		void Cleanup();
		static void FlushCache();
	};
}