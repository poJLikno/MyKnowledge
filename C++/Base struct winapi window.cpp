#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <gdiplus.h>

//#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

HDC dc;
PAINTSTRUCT ps;
ULONG_PTR gdiplusToken;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;
	
	//Register window class
    memset(&wc, 0, sizeof(WNDCLASS));
    {
        wc.style = CS_OWNDC;// or CS_VREDRAW | CS_HREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);// or wcl.hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);
        wc.lpszMenuName = 0;
        wc.lpszClassName = "class";
    }
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }

	//Create window
    hwnd = CreateWindow(wc.lpszClassName, "MyApplication", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, NULL, NULL, NULL, NULL);
	if (!hwnd)
    {
        MessageBox(NULL, "Can't create window", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);

	//Program main loop
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        //GDI+
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        SetTimer(hwnd, 1, 10, NULL);
    }
    else if (uMsg == WM_TIMER)
    {
        InvalidateRect(hwnd, NULL, /*TRUE*/FALSE);
    }
    else if (uMsg == WM_PAINT)
    {
        dc = BeginPaint(hwnd, &ps);
        /*Graphics g(dc);
        Image image(L"exit.png");
        g.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());*/
        EndPaint(hwnd, &ps);
    }
    else if (uMsg == WM_KEYDOWN)
    {
        if (wParam == VK_ESCAPE) DestroyWindow(hwnd);
    }
    else if (uMsg == WM_CLOSE)
    {
        DestroyWindow(hwnd);
    }
    else if (uMsg == WM_DESTROY)
    {
        KillTimer(hwnd, 1);
        GdiplusShutdown(gdiplusToken);
        PostQuitMessage(0);
    }
    else return DefWindowProc(hwnd, uMsg, wParam, lParam);
}