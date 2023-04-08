#include "ImageManager.h"

void ImageManager::TakeScreenshot(HBITMAP &bmp, int width, int height)
{
    // Variables
    HDC hdc = NULL;
    HDC hdcMemDC = NULL;
    HBITMAP hbmScreen = NULL;

    // Get screen
    hdc = GetDC(NULL);

    // Create a compatible DC, which is used in a BitBlt from the window DC.
    hdcMemDC = CreateCompatibleDC(hdc);
    if (!hdcMemDC)
    {
        //DeleteObject(hbmScreen);
        DeleteDC(hdcMemDC);
        throw(std::runtime_error("CreateCompatibleDC has failed"));
    }

    // Create a compatible bitmap from the Window DC.
    hbmScreen = CreateCompatibleBitmap(hdc, width, height);
    if (!hbmScreen)
    {
        //DeleteObject(hbmScreen);
        DeleteDC(hdcMemDC);
        throw(std::runtime_error("CreateCompatibleBitmap Failed"));
    }

    // Select the compatible bitmap into the compatible memory DC.
    SelectObject(hdcMemDC, hbmScreen);

    // Bit block transfer into our compatible memory DC.
    if (!BitBlt(hdcMemDC,
        0, 0,
        width, height,
        hdc,
        0, 0,
        SRCCOPY))
    {
        //DeleteObject(hbmScreen);
        DeleteDC(hdcMemDC);
        throw(std::runtime_error("BitBlt has failed"));
    }    

    bmp = hbmScreen;
    
    DeleteDC(hdcMemDC);
}

void ImageManager::PinMouseCursor(HBITMAP &bmp)
{
    // Get Compatible DC
    HDC hdc = CreateCompatibleDC(GetDC(NULL));
    if (!hdc)
    {
        DeleteDC(hdc);
        throw(std::runtime_error("CreateCompatibleDC has failed"));
    }

    // Link DC to bmp
    SelectObject(hdc, bmp);

    // Get cursor position
    POINT pt = {};
    GetCursorPos(&pt);

    // Draw cursor
    Gdiplus::Image img(L"aero_arrow.png");
    Gdiplus::Graphics graphics(hdc);
    graphics.DrawImage(&img, (int)pt.x, (int)pt.y);

    // Clean up
    DeleteDC(hdc);
}
