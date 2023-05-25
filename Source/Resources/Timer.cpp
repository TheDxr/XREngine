#include "Timer.h"


Timer::clock::time_point Timer::currentTime = clock::now();

long Timer::frameCount = 0;

Timer::FrameTime Timer::fixedDeltaTime(1/60.f);
Timer::FrameTime Timer::maxDeltaTime(1/60.f);

Timer::FrameTime Timer::elapsedTime(0.f);
Timer::FrameTime Timer::deltaTime(0.f);
Timer::FrameTime Timer::accumulator(0.f);

void Timer::preUpdate()
{
	frameCount++;
	const auto newTime = clock::now();
	deltaTime = newTime - currentTime;
	if (deltaTime > maxDeltaTime)
		deltaTime = maxDeltaTime;

	currentTime = newTime;
	accumulator += deltaTime;
}

void Timer::fixedUpdate()
{
	elapsedTime += fixedDeltaTime;
	accumulator -= fixedDeltaTime;
}

Timer::FrameTime& Timer::getFixedDeltaTime()
{
	return fixedDeltaTime;
}

Timer::FrameTime& Timer::getDeltaTime()
{
	return deltaTime;
}

Timer::FrameTime& Timer::getAccumulator()
{
	return accumulator;
}