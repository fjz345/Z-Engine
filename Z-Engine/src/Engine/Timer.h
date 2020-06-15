#pragma once

namespace ZE
{
	static LARGE_INTEGER Frequency;

	class Timer
	{
	public:
		Timer();
		~Timer();

		static void Init();
		void Start();
		void Stop();

		double GetElapsedTime();

	private:
		LARGE_INTEGER _startTime, _endTime;
	};

}