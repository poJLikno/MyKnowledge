#include "Window.h"

Window::Window(const char *name,
               bool icon,
               const char *class_name,
               int x, int y, 
               int width, int height,
               DWORD style)// ---
               : class_name_((char *)class_name)
{
    // Get icon width & height
    /*HBITMAP hIcon = LoadBitmap(NULL, icon);
    BITMAP iconInfo = {};
    GetObject(hIcon, sizeof(BITMAP), &iconInfo);
    DeleteObject(hIcon);*/
	
	//(HICON)LoadImage(HINST_THISCOMPONENT, icon, IMAGE_ICON, iconInfo.bmWidth, iconInfo.bmHeight, LR_LOADFROMFILE);
    
    // Register window class
    WNDCLASS wc = {};
    {
        wc.style = CS_OWNDC;// or CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = HINST_THISCOMPONENT;
        wc.hIcon = icon ? LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(101)) : LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);//NULL
        wc.lpszMenuName = NULL;
        wc.lpszClassName = class_name_;
    }
    if (!RegisterClass(&wc))
        throw std::runtime_error("Can't register class");

    // Create window
    hWnd = CreateWindow(wc.lpszClassName, name, style, x, y, width, height, NULL, NULL, NULL, NULL);
    if (!hWnd)
        throw std::runtime_error("Can't create window");

    ShowWindow(hWnd, SW_SHOWNORMAL);
}

Window::~Window()
{
    UnregisterClass(class_name_, HINST_THISCOMPONENT);
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