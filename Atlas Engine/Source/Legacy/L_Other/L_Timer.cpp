#include "L_Timer.h"
#include <iostream>

namespace L_Atlas {
	L_Timer::L_Timer(float lengthInSeconds)
		: currentTime(0.0f), lengthTime(lengthInSeconds), isRunning(false)
	{

	}

	void L_Timer::ElapseTime(float deltaT)
	{
		if (isRunning) {
			currentTime += deltaT;
		}
	}

	bool L_Timer::HasFinished()
	{
		if (isRunning && currentTime >= lengthTime) {
			return true;
		}
		else {
			return false;
		}
	}

	void L_Timer::Reset(float lengthInSeconds)
	{
		currentTime = 0.0f;
		lengthTime = lengthInSeconds;
		isRunning = false;
	}

	bool L_Timer::IsRunning()
	{
		return isRunning;
	}

	void L_Timer::Start()
	{
		isRunning = true;
	}

	void L_Timer::Stop()
	{
		isRunning = false;
	}

	L_Timer::~L_Timer()
	{

	}
}