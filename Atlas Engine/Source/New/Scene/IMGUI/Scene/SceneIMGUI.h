#pragma once

#include "Scene.h"

namespace Atlas {
	class SceneIMGUI : public Scene {
	private:

	public:
		void Update(float deltaTime);
		void Begin();
		void Draw(Renderer* renderer);
		void End();
	};
}