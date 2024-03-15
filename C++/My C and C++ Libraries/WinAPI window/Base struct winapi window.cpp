#include <windows.h>
#include <gdiplus.h>

//#pragma comment(linker, "/subsystem:WINDOWS")
//#pragma comment(linker, "/entry:mainCRTStartup")

//#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "gdiplus.lib")

//#pragma comment(linker,"\"/manifestdependency:type='win32' \
//name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
//processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//using namespace Gdiplus;

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

PAINTSTRUCT ps;
ULONG_PTR gdiplusToken;
const int iconSize = 64;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

    // Register window class
    WNDCLASS wc = {};
    {
        wc.style = CS_OWNDC;// or CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = HINST_THISCOMPONENT;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);// or wc.hIcon = (HICON)LoadImage(HINST_THISCOMPONENT, "icon.ico", IMAGE_ICON, iconSize, iconSize, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);//NULL
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "class";
    }
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }

    // Create window
    HWND hwnd = CreateWindow(wc.lpszClassName, "MyApplication", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, NULL, NULL, NULL, NULL);
    if (!hwnd)
    {
        MessageBox(NULL, "Can't create window", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);

    // Program main loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    /*while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            ...
        }
    }*/

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
            Gdiplus::Graphics g(ps.hdc);
            Gdiplus::Image image(L"exit.png");
            g.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
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