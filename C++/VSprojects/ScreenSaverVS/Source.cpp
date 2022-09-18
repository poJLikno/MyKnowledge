#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include "HeaderMain.h"

#pragma comment(lib, "gdi32.lib")

#pragma warning(disable : 4996)

using namespace std;

PAINTSTRUCT ps;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    {
        wc.style = CS_VREDRAW | CS_HREDRAW/*CS_OWNDC*/;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);
        wc.lpszMenuName = 0;
        wc.lpszClassName = "class";
        wc.hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
    }

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }

    //Display size if < 1600x900, default program resolution
    GetClientRect(GetDesktopWindow(), &rect);
    //------------
    sizex = (rect.right < 1600) ? 1600 : rect.right;
    sizey = (rect.bottom < 900) ? 900 : rect.bottom;

    HWND hwnd = CreateWindow(wc.lpszClassName, "ScreenSaver", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX, rect.right / 4, rect.bottom / 2 - rect.bottom / 6, sizex / 1.96 /*815*/, sizey / 2.662 /*338*/, NULL, NULL, NULL, NULL);

    if (!hwnd)
    {
        MessageBox(NULL, "Can't create window", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_HIDE);

    //bt_quit = CreateWindow("button", "X", WS_VISIBLE | WS_CHILD, sizex / 2 - sizex / 38.4, 1, sizex / 38.4, sizey / 21.6, hwnd, NULL, NULL, NULL);
    bt_save = CreateWindow("button", "Save", WS_VISIBLE | WS_CHILD, sizex / 2 - sizex / 19.2, sizey / 3 - sizey / 21.6, sizex / 19.2, sizey / 21.6, hwnd, NULL, NULL, NULL);
    edit = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT, sizex / 2.9538, sizey / 21.6, sizex / 8.727, sizey / 54, hwnd, NULL, NULL, NULL);

    int fontSize = (rect.right > 1440) ? 16 * (int)rect.right / 1440 : 16;

    myFont = CreateFont(fontSize, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, "Arial");
    //SendMessage(bt_quit, WM_SETFONT, (WPARAM)myFont, TRUE);
    SendMessage(bt_save, WM_SETFONT, (WPARAM)myFont, TRUE);
    SendMessage(edit, WM_SETFONT, (WPARAM)myFont, TRUE);

    MSG msg;

    while (1)
    {
        Sleep(10);

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            WaitingPress(hwnd, st);
        }
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_PAINT)
    {
        dc = BeginPaint(hwnd, &ps);

        DrawWindow();

        EndPaint(hwnd, &ps);
    }
    else if (message == WM_COMMAND)
    {
        /*if (lparam == (LPARAM)bt_quit)
        {
            ShowWindow(hwnd, SW_HIDE);
            delete[] way;
            DeleteDC(hdc);
            DeleteObject(bitmap);
        }*/
        if (lparam == (LPARAM)bt_save)
        {
            SavePicture(hwnd);
        }
    }
    else if (message == WM_CLOSE)
    {
        ShowWindow(hwnd, FALSE);
        //DestroyWindow(hwnd);
    }
    else if (message == WM_DESTROY)
    {
        DeleteObject(myFont);
        delete[] way;
        DeleteDC(hdc);
        DeleteObject(bitmap);
        ReleaseDC(hwnd, dc);
        PostQuitMessage(0);
    }
    else return DefWindowProcA(hwnd, message, wparam, lparam);
}
