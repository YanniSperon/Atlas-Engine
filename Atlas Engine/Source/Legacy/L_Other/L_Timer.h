#pragma once

namespace L_Atlas {
	class L_Timer {
	private:
		float currentTime;
		float lengthTime;
		bool isRunning;
	public:
		L_Timer(float lengthInSeconds);
		void ElapseTime(float deltaT);
		bool HasFinished();
		void Reset(float lengthInSeconds);
		bool IsRunning();
		void Start();
		void Stop();
		~L_Timer();
	};
}