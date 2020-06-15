#include "Timer.h"


ZE::Timer::Timer()
{
	
}

ZE::Timer::~Timer()
{
}

void ZE::Timer::Init()
{
	QueryPerformanceFrequency(&Frequency);
}

void ZE::Timer::Start()
{
	QueryPerformanceCounter(&_startTime);
}

void ZE::Timer::Stop()
{
	QueryPerformanceCounter(&_endTime);
}

double ZE::Timer::GetElapsedTime()
{
	LARGE_INTEGER ElapsedMicroseconds;
	LARGE_INTEGER nowTime;

	QueryPerformanceCounter(&nowTime);

	ElapsedMicroseconds.QuadPart = nowTime.QuadPart - _startTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	double seconds = ElapsedMicroseconds.QuadPart / (double)1000000;

	return seconds;
}
