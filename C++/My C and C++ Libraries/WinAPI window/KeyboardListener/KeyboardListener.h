#ifndef KB_LISTENER_H
#define KB_LISTENER_H

#include <iostream>
#include <Windows.h>

class KeyboardListener
{
private:
	HHOOK keyboardHandle;

    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

public:
	~KeyboardListener();

	void StartListenKeyboard();

	void StopListenKeyboard();
};

#endif