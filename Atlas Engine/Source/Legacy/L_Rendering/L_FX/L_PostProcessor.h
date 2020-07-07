#pragma once
#include "Legacy/L_Rendering/L_Scene/L_Renderer.h"
#include "Legacy/L_Game/L_Physics/L_PhysicsRenderer.h"
#include "Legacy/L_Game/L_Physics/L_PhysicsScene.h"

namespace L_Atlas {

	struct L_MSAA {
		bool enabled;
		unsigned int value;

		L_MSAA() {
			enabled = false;
			value = 0;
		}
		L_MSAA(bool enableMSAA, int valueOfMSAA) {
			enabled = enableMSAA;
			value = valueOfMSAA;
		}
	};

	class L_PostProcessor {
	public:
		static void PrepareForInitialization(L_MSAA multisampling);
		static void Initialize(std::string postProcessingShaderAddress);
		static void PrepareForRendering();
		static void PrepareForRenderingPhysicsSimulation();
		static void Render(L_Renderer* renderer);
		static void RenderPhysicsRenderer(L_PhysicsRenderer* renderer, L_PhysicsScene* scene);

		static void ChangeEffect(std::string newShaderShortenedName);
		static void Cleanup();
	};
}