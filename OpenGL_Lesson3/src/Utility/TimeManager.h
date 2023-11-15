#pragma once
#include <chrono>

class CTimeManager
{
    using timeType = std::chrono::system_clock::time_point;
private:
    timeType m_BuildTime;
    timeType m_RememberedTime;
    timeType m_TimerStartTime;
    double m_TimerPeriod;

public:
    CTimeManager();

    timeType CurrentTime() const;

    long long DeltaTime( timeType prevTime );
    long long TimeFromBuild() const;
    void RememberCurrentTime();

    void StartTimer( double period );
    bool IsTimerEnded();
    
};