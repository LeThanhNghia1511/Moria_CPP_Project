#include "Time.h"

Time* Time::_instance = nullptr;

Time::Time()
{
    _deltaTime = 0;
    _totalGameTime = 0;
    _lastTime = 0;
    _frequencyPerSeconds = 0;
}

Time* Time::GetInstance()
{
    if (!_instance)
    {
        _instance = new Time();
        if (!_instance->Initialize())
        {
        }
    }
    return _instance;
}

bool Time::Initialize()
{
    LARGE_INTEGER freq;
    if (!QueryPerformanceFrequency(&freq))
        return false;

    _frequencyPerSeconds = (float)freq.QuadPart;

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    _lastTime = counter.QuadPart;

    return true;
}

void Time::Update()
{
    Time* instance = GetInstance();

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    double elapsedTime = (double)(counter.QuadPart - instance->_lastTime);
    //instance->_deltaTime = (float)(elapsedTime / (double)instance->_frequencyPerSeconds) * 300;
    instance->_deltaTime = 0.016f;

    instance->_lastTime = counter.QuadPart;
    instance->_totalGameTime += instance->_deltaTime;
}