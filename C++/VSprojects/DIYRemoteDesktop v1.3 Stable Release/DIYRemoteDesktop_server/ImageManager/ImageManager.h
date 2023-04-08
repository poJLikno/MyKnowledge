#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <iostream>
#include <Windows.h>
#include <Gdiplus.h>

class ImageManager
{
public:
	static void TakeScreenshot(HBITMAP &bmp, int width, int height);
	static void PinMouseCursor(HBITMAP &bmp);
};

#endif