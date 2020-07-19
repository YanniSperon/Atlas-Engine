#pragma once

#include "New/Rendering/Shared/Renderer/Renderer.h"

namespace Atlas {
	class Scene {
	private:
		int width;
		int height;
		bool isPaused;
		glm::vec4 backgroundColor;
	public:
		Scene();
		Scene(int initialWidth, int initialHeight);
		virtual ~Scene();
		virtual void Update(float deltaTime) = 0;
		virtual void Begin() = 0;
		virtual void Draw(Renderer* renderer) = 0;
		virtual void End() = 0;

		bool GetIsPaused();
		glm::vec4 GetBackgroundColor();
		int GetWidth();
		int GetHeight();

		void SetIsPaused(bool newValue);
		void SetBackgroundColor(glm::vec4 color);
		void SetWidth(int newWidth);
		void SetHeight(int newHeight);

		void ToggleIsPaused();
	};
}