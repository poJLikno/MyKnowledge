#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <windows.h>

class Button
{
public:
	HWND hWnd = {};

	Button(HWND hWnd, const char *text, int x, int y, int width, int height, DWORD style = WS_VISIBLE | WS_CHILD);

	void SetText(const char *text);

	void GetText(char *buffer, size_t size);
};

#endif