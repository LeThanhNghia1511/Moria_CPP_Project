#ifndef TIME_H
#define TIME_H

#include <windows.h>

class Time
{
private:
    static Time* _instance;

    float _deltaTime;
    float _totalGameTime;
    LONGLONG _lastTime;
    float _frequencyPerSeconds;

    Time(); // Constructor để private để không ai 'new' bậy bạ được
    bool Initialize();

public:
    static Time* GetInstance();
    static void Update(); // Gọi ở Game::Run()

    // Hàm này để lấy DeltaTime ở mọi nơi
    static float GetDeltaTime() {
        return GetInstance()->_deltaTime;
    }

    static float GetTotalTime() {
        return GetInstance()->_totalGameTime;
    }
};

#endif

