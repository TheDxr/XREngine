#pragma once
#include <algorithm>
#include <cstdint>

class Stopwatch
{
public:
    static int64_t GetTimestamp();

    Stopwatch() noexcept;

    [[nodiscard]] double GetDeltaTime() const noexcept;
    [[nodiscard]] double GetTotalTime() const noexcept;
    [[nodiscard]] double GetTotalTimePrecise() const noexcept;
    [[nodiscard]] bool IsPaused() const noexcept;

    void Resume() noexcept;
    void Pause() noexcept;
    void Signal() noexcept;
    void Restart() noexcept;

    static const int64_t Frequency; // Ticks per second

private:
    int64_t StartTime    = {};
    int64_t TotalTime    = {};
    int64_t PausedTime   = {};
    int64_t StopTime     = {};
    int64_t PreviousTime = {};
    int64_t CurrentTime  = {};
    double Period        = 0.0;
    double DeltaTime     = 0.0;

    bool Paused = false;
};

template <typename TCallback>
class ScopedTimer
{
public:
    ScopedTimer(TCallback &&Callback)
        : Callback(std::move(Callback)), Start(Stopwatch::GetTimestamp())
    {}
    ~ScopedTimer()
    {
        int64_t End                 = Stopwatch::GetTimestamp();
        int64_t Elapsed             = End - Start;
        int64_t ElapsedMilliseconds = Elapsed * 1000 / Stopwatch::Frequency;
        Callback(ElapsedMilliseconds);
    }

private:
    TCallback Callback;
    int64_t Start;
};
