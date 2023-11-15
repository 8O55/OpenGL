#include "TimeManager.h"

CTimeManager::CTimeManager()
    : m_TimerPeriod{ 0 }
{
    m_BuildTime = std::chrono::system_clock::now();
}

CTimeManager::timeType CTimeManager::CurrentTime() const
{
    return std::chrono::system_clock::now();
}

long long CTimeManager::DeltaTime( timeType prevTime )
{
    return std::chrono::duration_cast< std::chrono::milliseconds >( CurrentTime() - prevTime ).count();
}

long long CTimeManager::TimeFromBuild() const
{
    return std::chrono::duration_cast< std::chrono::milliseconds >( CurrentTime() - m_BuildTime ).count();
}

void CTimeManager::RememberCurrentTime()
{
    m_RememberedTime = CurrentTime();
}

void CTimeManager::StartTimer( double period )
{
    m_TimerPeriod = period;
    m_TimerStartTime = CurrentTime();
}

bool CTimeManager::IsTimerEnded()
{
    return DeltaTime( m_TimerStartTime ) > m_TimerPeriod;
}