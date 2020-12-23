#include "Timer.h"

Timer::Timer(unsigned int type, bool reverse)
	:duration(0.0f), TimerName(""), type(type), reverse(reverse)
{
	start = std::chrono::high_resolution_clock::now();
}

Timer::Timer(bool reverse)
	:duration(0.0f), TimerName(""), type(0), reverse(reverse)
{
	start = std::chrono::high_resolution_clock::now();
}

Timer::Timer(std::string Name, bool reverse)
	: duration(0.0f), TimerName(Name), type(0), reverse(reverse)
{
	start = std::chrono::high_resolution_clock::now();
}

Timer::Timer(unsigned int type, std::string Name, bool reverse)
	: duration(0.0f), TimerName(Name), type(type), reverse(reverse)
{
	start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	double result = duration.count();

	if (reverse)
		result = 1 / result;

	if(type == CLog_Timer)
	std::cout << std::endl << ((TimerName != "") ? "[" + TimerName + "]: " : "") << result << (!reverse ? "s" : "") << std::endl;
	
}
