#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include <windows.h>

class Label
{
public:
	HWND hWnd = {};

	Label(HWND hWnd, const char *text, int x, int y, int width, int height, DWORD style = WS_VISIBLE | WS_CHILD);

	void SetText(const char *text);

	void GetText(char *buffer, size_t size);
};

#endif