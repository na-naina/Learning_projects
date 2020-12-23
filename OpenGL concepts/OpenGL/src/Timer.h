#include <future>
#include <chrono>
#include <iostream>

#pragma once
struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;
	std::string TimerName;
	bool reverse;
	unsigned int type;

	enum TimerType{
		SampleTimer = 0, CLog_Timer = 1
	};


	Timer(unsigned int type, bool reverse = 0);
	Timer(bool reverse = 0);
	Timer(std::string Name, bool reverse = 0);
	Timer(unsigned int type, std::string Name, bool reverse = 0);
	~Timer();
};

