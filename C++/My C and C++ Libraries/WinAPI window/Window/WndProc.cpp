#include "Window.h"

PAINTSTRUCT ps;
ULONG_PTR gdiplusToken;

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        //GDI+
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        SetTimer(hWnd, 1, 10, NULL);
        result = 1;
    }
    else
    {
        if (message == WM_TIMER)
        {
            InvalidateRect(hWnd, NULL, /*TRUE*/FALSE);
            result = 0;
        }
        else if (message == WM_PAINT)
        {
            ps.hdc = BeginPaint(hWnd, &ps);
            // Example
            /*Gdiplus::Graphics g(ps.hdc);
            Gdiplus::Image image(L"exit.png");
            g.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());*/
            EndPaint(hWnd, &ps);
            result = 0;
        }
        else if (message == WM_KEYDOWN)
        {
            if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
            result = 0;
        }
        else if (message == WM_CLOSE)
        {
            DestroyWindow(hWnd);
            result = 0;
        }
        else if (message == WM_DESTROY)
        {
            KillTimer(hWnd, 1);
            Gdiplus::GdiplusShutdown(gdiplusToken);
            PostQuitMessage(0);
            result = 1;
        }
        else result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return result;
}