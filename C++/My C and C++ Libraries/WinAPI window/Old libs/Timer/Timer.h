#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>
#include <windows.h>

class Timer
{
private:
	HWND hWnd_ = NULL;
	UINT_PTR timer_id_ = 0ULL;
	bool timer_flag_ = false;

public:
	~Timer();

	void Create(HWND hWnd, UINT_PTR timer_id, UINT elapse, TIMERPROC timer_func = NULL);

	void Create(UINT elapse, TIMERPROC timer_func = NULL);

	void Change(UINT elapse, TIMERPROC timer_func = NULL);

	UINT_PTR GetId() const;

	void Kill();
};

#endif