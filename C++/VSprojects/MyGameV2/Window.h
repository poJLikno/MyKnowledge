#ifndef WINDOW_H_
#define WINDOW_H_


#include "main.h"

class Window
{
public:
	HWND hwnd{};

	MSG msg{};

	Window(const char* name, unsigned short pos_x, unsigned short pos_y, HINSTANCE& hInstance);
};


#endif