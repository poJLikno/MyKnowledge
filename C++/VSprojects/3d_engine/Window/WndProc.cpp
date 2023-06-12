#include "Windowsx.h"
#include "Window.h"
#include "../Graphics2d/Graphics2d.h"

extern Player *player;
extern Rect *my_rect;

PAINTSTRUCT ps;
Graphics2d *graphics_2d;

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        SetCursorPos(WinPosX + WinWidth / 2, WinPosY + WinHeight / 2);

        graphics_2d = new Graphics2d();
        Logic::GameInit();

        SetTimer(hWnd, 1, 10, NULL);
        result = 1;
    }
    else
    {
        if (message == WM_TIMER)
        {
            if (GetForegroundWindow() == hWnd)
            {
                player->Walk();
            }

            InvalidateRect(hWnd, NULL, FALSE);
            result = 0;
        }
        else if (message == WM_PAINT)
        {
            graphics_2d->DrawCanvas(&hWnd, &ps);
            result = 0;
        }
        else if (message == WM_MOUSEMOVE)
        {
            if (GetForegroundWindow() == hWnd)
            {
                player->Look(&hWnd, WinWidth, WinHeight);
                SetCursorPos(WinPosX + WinWidth / 2, WinPosY + WinHeight / 2);
            }
        }
        else if (message == WM_MOVE)
        {
            WinPosX = (int)LOWORD(lParam);
            WinPosY = (int)HIWORD(lParam);
            result = 0;
        }
        else if (message == WM_SIZE)
        {
            WinWidth = (int)LOWORD(lParam);
            WinHeight = (int)HIWORD(lParam);
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
            Logic::GameClose();
            delete graphics_2d;
            PostQuitMessage(0);
            result = 1;
        }
        else result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return result;
}