#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <Windows.h>
#include <Gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


class Window
{
private:
	MSG msg = {};

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	HWND hwnd = {};

	Window(const char *name, int x, int y, int width, int height);

	Window(const char *name, const char *icon, int x, int y, int width, int height);

	void RunMessageLoop();

	void RunMessageLoopAsync();
};

#endif