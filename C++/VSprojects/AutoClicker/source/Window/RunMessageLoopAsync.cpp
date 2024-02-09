#include "Window.h"

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
            //...
        }
    }
}