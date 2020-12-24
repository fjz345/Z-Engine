#pragma once

namespace ZE
{
	static LARGE_INTEGER s_Frequency;

	class Timer
	{
	public:
		Timer();
		~Timer();

		// Set's the frequency
		static void Init();

		// Timestamps start
		void Start();

		// Timestamps end
		void Stop();

		// Returns seconds
		double GetElapsedTime();

	private:
		LARGE_INTEGER _startTime, _endTime;
	};

}