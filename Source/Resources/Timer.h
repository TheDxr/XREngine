#pragma once

#include <chrono>

class Timer
{
public:
    Timer()  = delete;
    ~Timer() = delete;

    using clock = std::chrono::high_resolution_clock;
    using ms    = std::chrono::duration<double, std::milli>;
    using sec   = std::chrono::duration<double>;

    using FrameTime = sec;

    static long frameCount;

    static FrameTime fixedDeltaTime;
    static FrameTime maxDeltaTime;

    static clock::time_point currentTime;
    static FrameTime elapsedTime;
    static FrameTime deltaTime;
    static FrameTime accumulator;

    static void preUpdate();
    static void fixedUpdate();

    static FrameTime &getFixedDeltaTime();
    static FrameTime &getDeltaTime();
    static FrameTime &getAccumulator();
};
