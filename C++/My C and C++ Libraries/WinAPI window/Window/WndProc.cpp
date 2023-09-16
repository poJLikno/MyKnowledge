#include "Window.h"

PAINTSTRUCT ps;
ULONG_PTR gdiplusToken;

#define ID_TIMER1 1

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        //GDI+
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        SetTimer(hWnd, ID_TIMER1, 10, NULL);
        result = 1;
    }
    else
    {
        if (message == WM_TIMER)
        {
            if (wParam == ID_TIMER1)
            {
                InvalidateRect(hWnd, NULL, /*TRUE*/FALSE);
            }
            result = 0;
        }
        else if (message == WM_PAINT)
        {
            /* Draw image
            ps.hdc = BeginPaint(hWnd, &ps);

            Gdiplus::Graphics graphics(ps.hdc);
            Gdiplus::Image image(L"image.jpg");
            graphics.DrawImage(&image, 0, 0);

            EndPaint(hWnd, &ps);*/
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
            if (!KillTimer(hWnd, ID_TIMER1))
                MessageBox(NULL, std::string("Can't kill timer -> Error code: " + std::to_string(GetLastError())).c_str(), "Error", MB_OK);

            Gdiplus::GdiplusShutdown(gdiplusToken);

            PostQuitMessage(0);

            result = 1;
        }
        else result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return result;
}