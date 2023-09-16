#include "Timer.h"

Timer::~Timer()
{
    if (timer_flag_) Timer::Kill();
}

void Timer::Create(HWND hWnd, UINT_PTR timer_id, UINT elapse, TIMERPROC timer_func)
{
    if (!timer_flag_)
    {
        if (hWnd && timer_id)
        {
            hWnd_ = hWnd;
            timer_id_ = SetTimer(hWnd, timer_id, elapse, timer_func);
            if (!timer_id_)
                MessageBox(NULL, std::string("Can't set timer -> Error code: " + std::to_string(GetLastError())).c_str(), "Error", MB_OK);
            else
                timer_flag_ = true;
        }
        if (!hWnd)
            MessageBox(NULL, "Timer hWnd can't be NULL", "Error", MB_OK);
        if (!timer_id)
            MessageBox(NULL, "Timer ID can't be 0", "Error", MB_OK);
    }
    else
        MessageBox(NULL, "Timer already exist", "Error", MB_OK);
}

void Timer::Create(UINT elapse, TIMERPROC timer_func)
{
    if (!timer_flag_)
    {
        timer_id_ = SetTimer(NULL, 0, elapse, timer_func);
        if (!timer_id_)
            MessageBox(NULL, std::string("Can't set timer -> Error code: " + std::to_string(GetLastError())).c_str(), "Error", MB_OK);
        else
            timer_flag_ = true;
    }
    else
        MessageBox(NULL, "Timer already exist", "Error", MB_OK);
}

void Timer::Change(UINT elapse, TIMERPROC timer_func)
{
    if (timer_flag_)
    {
        timer_id_ = SetTimer(hWnd_, Timer::GetId(), elapse, timer_func);
        if (!timer_id_)
            MessageBox(NULL, std::string("Can't set timer -> Error code: " + std::to_string(GetLastError())).c_str(), "Error", MB_OK);
    }
    else
        MessageBox(NULL, "Timer doesn't exist", "Error", MB_OK);
}

UINT_PTR Timer::GetId() const
{
    return timer_id_;
}

void Timer::Kill()
{
    if (timer_flag_)
    {
        if (!KillTimer(hWnd_, Timer::GetId()))
            MessageBox(NULL, std::string("Can't kill timer -> Error code: " + std::to_string(GetLastError())).c_str(), "Error", MB_OK);
        else
            timer_flag_ = false;
    }
    else
        MessageBox(NULL, "Timer doesn't exist", "Error", MB_OK);
}