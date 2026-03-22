#ifndef TIME_H
#define TIME_H

#include <windows.h>

class Time
{
public:
	float deltaTime;
	float totalGameTime;

	bool Initialize();
	void Update();
private:
	LONGLONG _lastTime;
	float _frequencyPerSeconds;
};

#endif

