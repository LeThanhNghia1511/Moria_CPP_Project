#include "Time.h"

bool Time::Initialize()
{
	LARGE_INTEGER i;
	// Get frequency from counter, the frequency can not change while the system is running, so we just need to do this once
	if (!QueryPerformanceFrequency(&i))
	{
		return false;
	}
	_frequencyPerSeconds = (float)(i.QuadPart);

	// Get the current value of the counter
	QueryPerformanceCounter(&i);
	_lastTime = i.QuadPart;
	deltaTime = 0;
	totalGameTime = 0;

	return true;
}

void Time::Update()
{
	LARGE_INTEGER i;

	QueryPerformanceCounter(&i);
	deltaTime = (float)(i.QuadPart - _lastTime) / _frequencyPerSeconds;

	_lastTime = i.QuadPart;
	totalGameTime += deltaTime;
}