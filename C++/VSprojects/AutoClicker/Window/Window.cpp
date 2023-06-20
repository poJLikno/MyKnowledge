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
    hWnd = CreateWindow(wc.lpszClassName, name, WS_OVERLAPPED | WS_SYSMENU, x, y, width, height, NULL, NULL, NULL, NULL);
    if (!hWnd)
        throw std::runtime_error("Can't create window");

    ShowWindow(hWnd, SW_SHOWNORMAL);
}

Window::Window(const char *name, const char *icon, int x, int y, int width, int height)
{
    // Get icon width & height
    /*HBITMAP hIcon = LoadBitmap(NULL, icon);
    BITMAP iconInfo = {};
    GetObject(hIcon, sizeof(BITMAP), &iconInfo);
    DeleteObject(hIcon);*/
    
    // Register window class
    WNDCLASS wc = {};
    {
        wc.style = CS_OWNDC;// or CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = HINST_THISCOMPONENT;
        wc.hIcon = (HICON)LoadIconA(HINST_THISCOMPONENT, MAKEINTRESOURCE(101/*Look icon definition in resource.h*/));//LoadImage(HINST_THISCOMPONENT, icon, IMAGE_ICON, iconInfo.bmWidth, iconInfo.bmHeight, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);//NULL
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "class";
    }
    if (!RegisterClass(&wc))
        throw std::runtime_error("Can't register class");

    // Create window
    hWnd = CreateWindow(wc.lpszClassName, name, WS_OVERLAPPED | WS_SYSMENU, x, y, width, height, NULL, NULL, NULL, NULL);
    if (!hWnd)
        throw std::runtime_error("Can't create window");

    ShowWindow(hWnd, SW_SHOWNORMAL);
}

void Window::SetLabel(const char *label)
{
    SetWindowText(this->hWnd, label);
}

void Window::GetLabel(char *buffer, size_t size)
{
    GetWindowText(this->hWnd, buffer, (int)size);
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