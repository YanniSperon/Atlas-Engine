#pragma once
#include "L_PhysicsObject.h"
#include "Legacy/L_Rendering/L_Scene/L_Light.h"

namespace L_Atlas {

	class L_PhysicsLight : public L_PhysicsObject {
	private:
		L_LightIntensity intensity;
	public:
		L_PhysicsLight();
		L_PhysicsLight(L_Light* light);
		~L_PhysicsLight();

		void SetLightIntensity(L_LightIntensity newValue);
		L_LightIntensity GetL_LightIntensity();
	};
}