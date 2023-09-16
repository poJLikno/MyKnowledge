#include "Window.h"

Window::Window(const char *name, bool icon, int x, int y, int width, int height)
{
    // Get icon width & height
    /*HBITMAP hIcon = LoadBitmap(NULL, icon);
    BITMAP iconInfo = {};
    GetObject(hIcon, sizeof(BITMAP), &iconInfo);
    DeleteObject(hIcon);*/
	
	//(HICON)LoadImage(HINST_THISCOMPONENT, icon, IMAGE_ICON, iconInfo.bmWidth, iconInfo.bmHeight, LR_LOADFROMFILE);
    
    // Register window class
    snprintf(class_name_, 256, "%s_class", name);

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
        throw std::runtime_error("Can't register class -> Error code: " + std::to_string(GetLastError()));

    // Create window
    this->hWnd = CreateWindow(wc.lpszClassName, name, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, NULL, NULL);
    if (!this->hWnd)
        throw std::runtime_error("Can't create window -> Error code: " + std::to_string(GetLastError()));

    ShowWindow(this->hWnd, SW_SHOWNORMAL);
}

Window::~Window()
{
    if (!UnregisterClass(class_name_, HINST_THISCOMPONENT))
        MessageBox(NULL, std::string("Can't unregister class -> Error code: " + std::to_string(GetLastError())).c_str(), "Error", MB_OK);
    ZeroMemory(class_name_, 256);
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
    while (GetMessage(&msg_, NULL, 0, 0))
    {
        TranslateMessage(&msg_);
        DispatchMessage(&msg_);
    }
}

void Window::RunMessageLoopAsync()
{
    // Program main loop
    while (true)
    {
        if (PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE))
        {
            if (msg_.message == WM_QUIT) break;
            TranslateMessage(&msg_);
            DispatchMessage(&msg_);
        }
        else
        {
            // Code
        }
    }
}