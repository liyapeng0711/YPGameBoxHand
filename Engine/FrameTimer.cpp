#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
	pre = std::chrono::steady_clock::now();
}

float FrameTimer::Mark()
{
	const auto current = std::chrono::steady_clock::now();
	const std::chrono::duration<float> runtime = current - pre;
	pre = current;
	return runtime.count();
}
