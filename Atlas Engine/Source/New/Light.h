#pragma once

namespace Atlas {
	class Light {
	private:
		// include data about color etc, make different types of lights extend this class
	public:
		Light();
		~Light();

		void Update(float deltaTime);
	};
}