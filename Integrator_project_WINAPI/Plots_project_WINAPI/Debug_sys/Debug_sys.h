#pragma once
#include <chrono>
#include <iostream>

void PrintGlobal_mainfunc_cpp();
void PrintGlobal_WndProc_cpp();
void PrintGlobal_integral_wnd_cpp();
void PrintGlobal_winplot_proc_cpp();

class SimpleTimer

{
public:
	SimpleTimer() {
		start = std::chrono::high_resolution_clock::now();
	}
	
	~SimpleTimer() {

		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float result = duration.count();
		std::cout << "FPS: " << int(1.0 / result) << std::endl;
		//std::cout << "Time: " << result << std::endl;
	}
	std::chrono::duration<float> duration;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
};

