#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <windows.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

//#pragma comment(linker,"\"/manifestdependency:type='win32' \
//name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
//processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


class Window
{
private:
	char class_name_[256] = { 0 };
	MSG msg_ = { 0 };

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	HWND hWnd = {};
	
	Window(const char *name, bool icon, int x, int y, int width, int height);

	~Window();

	void SetLabel(const char *label);

	void GetLabel(char *buffer, size_t size);

	void RunMessageLoop();

	void RunMessageLoopAsync();
};

#endif