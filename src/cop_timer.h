#pragma once

namespace cop {
class Timer
{
public:
    Timer();

    void Start();
    void Stop();
    float GetElapsedTime() const;
    bool IsRunning() const;

private:
    std::chrono::high_resolution_clock::time_point m_startTime;
    float m_elapsedTime;
    bool m_running;
};

inline Timer::Timer() : m_elapsedTime(0.0), m_running(false)
{
}

inline bool Timer::IsRunning() const
{
    return m_running;
}

inline void Timer::Start()
{
    if (!m_running)
    {
        m_startTime = std::chrono::high_resolution_clock::now();
        m_running = true;
    }
}

inline void Timer::Stop()
{
    if (m_running)
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        m_elapsedTime = std::chrono::duration<float>(endTime - m_startTime).count();
        m_running = false;
    }
}

inline float Timer::GetElapsedTime() const
{
    if (m_running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<float>(currentTime - m_startTime).count();
    }
    else
    {
        return m_elapsedTime;
    }
}

} // namespace CP