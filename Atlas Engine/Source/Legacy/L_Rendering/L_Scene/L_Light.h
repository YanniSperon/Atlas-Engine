#pragma once

#include "Legacy/L_Rendering/L_Scene/L_Object.h"

namespace L_Atlas {

	struct L_LightIntensity {
		glm::vec3 ambient, diffuse, specular;

		L_LightIntensity()
			: ambient(1.0f, 1.0f, 1.0f), diffuse(1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f)
		{
		}

		L_LightIntensity(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
			: ambient(amb), diffuse(diff), specular(spec)
		{
		}
	};

	class L_Light : public L_Object {
	private:
		L_LightIntensity intensity;
	public:
		L_Light();
		L_Light(L_LightIntensity lightIntensity, L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s);
		L_Light(L_LightIntensity lightIntensity, L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, L_Material mat);

		void SetLightIntensity(L_LightIntensity newValue);
		L_LightIntensity GetLightIntensity();

		virtual std::string GetType() override;
	};
}