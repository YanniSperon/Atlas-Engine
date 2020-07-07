#include "L_Light.h"

namespace L_Atlas {
	L_Light::L_Light()
		: L_Object(), intensity()
	{
	}
	L_Light::L_Light(L_LightIntensity lightIntensity, L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s)
		: L_Object(type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, uid, rot, trans, s), intensity(lightIntensity)
	{

	}

	L_Light::L_Light(L_LightIntensity lightIntensity, L_Type type, std::string meshDir, std::string meshName, std::string texDir, std::string texName, std::string shaderDir, std::string shaderName, bool glInit, bool hasLighting, unsigned long long int uid, glm::vec3 rot, glm::vec3 trans, glm::vec3 s, L_Material mat)
		: L_Object(type, meshDir, meshName, texDir, texName, shaderDir, shaderName, glInit, hasLighting, uid, rot, trans, s, mat), intensity(lightIntensity)
	{

	}

	void L_Light::SetLightIntensity(L_LightIntensity newValue)
	{
		intensity = newValue;
	}

	L_LightIntensity L_Light::GetLightIntensity()
	{
		return intensity;
	}

	std::string L_Light::GetType()
	{
		return "L_Light";
	}
}