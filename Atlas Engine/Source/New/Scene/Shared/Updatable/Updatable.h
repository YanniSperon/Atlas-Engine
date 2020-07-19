#pragma once

namespace Atlas {
	class Updatable {
	private:
		int framesBetweenUpdates;
		int currentFrame;
	protected:
		bool ShouldUpdate();
	public:
		Updatable(int framesUntilUpdate);
		Updatable(int framesUntilUpdate, int startingFrame);
		virtual ~Updatable();
		virtual void Update(float deltaTime);
	};
}