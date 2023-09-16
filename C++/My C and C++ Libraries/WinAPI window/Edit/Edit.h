#ifndef EDIT_H
#define EDIT_H

#include <iostream>
#include <windows.h>

class Edit
{
public:
	HWND hWnd = {};

	Edit(HWND hWnd, int x, int y, int width, int height, DWORD style = WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT);

	void SetText(const char *text);

	void GetText(char *buffer, size_t size);
};

#endif