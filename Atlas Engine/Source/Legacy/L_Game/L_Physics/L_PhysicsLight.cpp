#include "L_PhysicsLight.h"

namespace L_Atlas {

	L_PhysicsLight::L_PhysicsLight()
	{

	}

	L_PhysicsLight::L_PhysicsLight(L_Light* light)
		: L_PhysicsObject(light, 0.0f)
	{
		intensity = light->GetLightIntensity();
	}

	L_PhysicsLight::~L_PhysicsLight()
	{
		
	}

	void L_PhysicsLight::SetLightIntensity(L_LightIntensity newValue)
	{
		intensity = newValue;
	}

	L_LightIntensity L_PhysicsLight::GetL_LightIntensity()
	{
		return intensity;
	}
}