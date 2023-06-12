#include "Window.h"

Window::Window(const char *name, int x, int y, int width, int height)
{
    // Register window class
    WNDCLASS wc = {};
    {
        wc.style = CS_OWNDC;// or CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = HINST_THISCOMPONENT;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//wc.hIcon = (HICON)LoadImage(HINST_THISCOMPONENT, "icon.ico", IMAGE_ICON, iconSize, iconSize, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);//NULL
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "class";
    }
    if (!RegisterClass(&wc))
        throw std::runtime_error("Can't register class");

    // Create window
    hwnd = CreateWindow(wc.lpszClassName, name, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, NULL, NULL);
    if (!hwnd)
        throw std::runtime_error("Can't create window");

    ShowWindow(hwnd, SW_SHOWNORMAL);
}

Window::Window(const char *name, const char *icon, int x, int y, int width, int height)
{
    // Get icon width & height
    HBITMAP hIcon = LoadBitmap(NULL, icon);
    BITMAP iconInfo = {};
    GetObject(hIcon, sizeof(BITMAP), &iconInfo);
    DeleteObject(hIcon);
    
    // Register window class
    WNDCLASS wc = {};
    {
        wc.style = CS_OWNDC;// or CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = HINST_THISCOMPONENT;
        wc.hIcon = (HICON)LoadImage(HINST_THISCOMPONENT, icon, IMAGE_ICON, iconInfo.bmWidth, iconInfo.bmHeight, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);//NULL
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "class";
    }
    if (!RegisterClass(&wc))
        throw std::runtime_error("Can't register class");

    // Create window
    hwnd = CreateWindow(wc.lpszClassName, name, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, NULL, NULL);
    if (!hwnd)
        throw std::runtime_error("Can't create window");

    ShowWindow(hwnd, SW_SHOWNORMAL);
}

void Window::RunMessageLoop()
{
    // Program main loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::RunMessageLoopAsync()
{
    // Program main loop
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Code
        }
    }
}