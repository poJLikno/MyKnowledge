#include <stdio.h>
#include <iostream>
#include <windows.h>

int full = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    else if (message == WM_KEYDOWN)
    {
        if (wparam == VK_ESCAPE) PostQuitMessage(0);
        else if (wparam == '1')
        {
            if (full == 0)
            {
                SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
                SetWindowPos(hwnd, HWND_TOP, 0, 0, 1280, 720, SWP_SHOWWINDOW);
                full = 1;
            }
            else
            {
                SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
                SetWindowPos(hwnd, HWND_TOP, 100, 100, 600, 600, SWP_SHOWWINDOW);
                full = 0;
            }
        }
    }
    else if (message == WM_MOUSEMOVE)
    {
        //system("mspaint");
        //Sleep(1500);
    }
    else return DefWindowProcA(hwnd, message, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.style = CS_OWNDC;// or CS_VREDRAW | CS_HREDRAW;
    wcl.lpfnWndProc = WndProc;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hInstance = hInstance;
    wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);// or wcl.hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.hbrBackground = (HBRUSH)(6);
    wcl.lpszMenuName = 0;
    wcl.lpszClassName = "class";

    if (!RegisterClassA(&wcl))
    {
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }

    HWND hwnd;
    hwnd = CreateWindow(wcl.lpszClassName, "MyApplication", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, NULL, NULL, NULL, NULL);

    if (!hwnd)
    {
        MessageBox(NULL, "Can't create window", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    /*while (1)
    {
        if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
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

    return 0;
}
