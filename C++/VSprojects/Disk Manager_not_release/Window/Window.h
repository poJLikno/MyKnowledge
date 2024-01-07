#ifndef WINDOW_H
#define WINDOW_H

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <iostream>
#include <Windows.h>
//#include <Gdiplus.h>

//#pragma comment(lib, "gdiplus.lib")

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


class Window
{
private:
	char *class_name_ = nullptr;

	MSG msg = {};

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	HWND hWnd = {};

	Window(const char *name,
		   bool icon,
		   const char *class_name,
		   int x, int y,
		   int width, int height,
		   DWORD style = WS_OVERLAPPEDWINDOW);

	~Window();

	void RunMessageLoop();

	void RunMessageLoopAsync();
};

#endif