#ifndef GRAPHICS_2D_H
#define GRAPHICS_2D_H

#include <Windows.h>
#include <Gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

#include "../Settings/WindowSettingsExt.h"
#include "../Logic/Logic.h"

class Graphics2d
{
private:	
	ULONG_PTR gdiplusToken = {};
	HDC dc = {};
	HBITMAP bitmap = {};

	enum COLORS
	{
		BLACK = RGB(0, 0, 0),
		RED = RGB(255, 0, 0),
		GREEN = RGB(0, 255, 0),
		BLUE = RGB(0, 0, 255),
		WHITE = RGB(255, 255, 255)
	};

	void CreateBuffer(PAINTSTRUCT *ps);

	void SetBuffer(PAINTSTRUCT *ps);

	void SetBrushColor(COLORREF color);

	void SetPenColor(COLORREF color);

	int TranX(float x);

	int TranY(float y);

	void DrawRect(float x, float y, float width, float height);

	void DrawCircle(float x, float y, float radius);

	void DrawPixel(float x, float y, COLORREF color);

	void DrawLine(float x0, float y0, float x1, float y1);

public:
	Graphics2d();

	~Graphics2d();

	void DrawCanvas(HWND *hWnd, PAINTSTRUCT *ps);
};

#endif