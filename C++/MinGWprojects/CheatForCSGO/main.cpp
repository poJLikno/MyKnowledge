#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

UINT full = 0;
UINT fell = 0;
UINT clicks = 0;

HWND myhwnd;
HDC mydc;
HWND chwnd;
HDC cdc;
LPPOINT point;

LPRECT rec;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    else if (message == WM_KEYDOWN && wparam == '5')
    {
        Sleep(100);
        ReleaseDC(chwnd, cdc);
        ReleaseDC(myhwnd, mydc);
        DeleteObject(rec);
        DeleteObject(point);
        PostQuitMessage(0);
        return 0;
    }
    else if (message == WM_KEYDOWN && wparam == '6')
    {
        if (full == 0)
        {
            SetWindowLongPtr(chwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
            SetWindowPos(chwnd, HWND_TOP, 0, 0, 1280, 1024, SWP_SHOWWINDOW);
            full = 1;
        }
        else
        {
            SetWindowLongPtr(chwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
            SetWindowPos(chwnd, HWND_TOP, 400, 200, 1280, 1024, SWP_SHOWWINDOW);
            full = 0;
        }
        Sleep(500);
    }
    else if (message == WM_KEYDOWN && wparam == '7')
    {
        if (fell == 0)
        {
            DEVMODE deviseMode;
            {
                deviseMode.dmSize = sizeof(deviseMode);
                deviseMode.dmPelsWidth = 1280;
                deviseMode.dmPelsHeight = 1024;
                deviseMode.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;
            }
            ChangeDisplaySettings(&deviseMode, CDS_FULLSCREEN);
            fell = 1;
        }
        else
        {
            ChangeDisplaySettings(0, 0);
            fell = 0;
        }
        Sleep(500);
    }
    else if (clicks == 1 && message == WM_KEYDOWN && wparam == VK_LBUTTON)
    {
        for (int i = 0; i < 10; i++)
        {
            Sleep(100);
            mouse_event(MOUSEEVENTF_LEFTDOWN, point->x, point->y, 0, 0);
            Sleep(100);
            mouse_event(MOUSEEVENTF_LEFTUP, point->x, point->y, 0, 0);
        }
    }
    else if (message == WM_KEYDOWN && wparam == 'N')
    {
        if (clicks == 0)
        {
            clicks = 1;
            Sleep(300);
        }
        else if (clicks == 1)
        {
            clicks = 0;
            Sleep(300);
        }
    }
    else return DefWindowProc(hwnd, message, wparam, lparam);
}

DWORD WINAPI MyThread(LPVOID param)
{
    while (1)
    {
        SelectObject(cdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(cdc, RGB(0, 255, 0));
        Rectangle(cdc, rec->right / 2 - 2, rec->bottom / 2 - 2, rec->right / 2 + 2, rec->bottom / 2 + 2);
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPTSTR lpCmdLine, int nCmdShow)
{
    chwnd = FindWindow((LPCSTR)"Valve001", NULL);

    cdc = GetDC(chwnd);

    rec = (LPRECT)malloc(sizeof(*rec));

    point = (LPPOINT)malloc(sizeof(*point));

    HANDLE mythread = CreateThread(NULL,0, MyThread, NULL, 0, NULL);
	//CloseHandle(mythread);


    WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.lpszClassName = "MyApp";
    wcl.lpfnWndProc = WndProc;
    RegisterClassA(&wcl);

	myhwnd = CreateWindow(wcl.lpszClassName, "MyApplication", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, NULL, NULL, NULL, NULL);

	ShowWindow(myhwnd, SW_SHOWNORMAL);

    mydc = GetDC(myhwnd);

	MSG msg;

    do
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        GetClientRect(chwnd, rec);
        GetCursorPos(point);

        if (clicks == 1 && GetKeyState(VK_LBUTTON) < 0)
        {
            for (int i = 0; i < 10; i++)
            {
                Sleep(100);
                mouse_event(MOUSEEVENTF_LEFTDOWN, point->x, point->y, 0, 0);
                Sleep(100);
                mouse_event(MOUSEEVENTF_LEFTUP, point->x, point->y, 0, 0);
            }
        }

        /*if (GetKeyState('6') < 0)
        {
            if (full == 0)
            {
                SetWindowLongPtr(chwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
                SetWindowPos(chwnd, HWND_TOP, 0, 0, 1280, 720, SWP_SHOWWINDOW);
                full = 1;
            }
            else
            {
                SetWindowLongPtr(chwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
                SetWindowPos(chwnd, HWND_TOP, 400, 200, 1280, 720, SWP_SHOWWINDOW);
                full = 0;
            }
            Sleep(500);
        }
        else if (GetKeyState('7') < 0)
        {
            if (fell == 0)
            {
                DEVMODE deviseMode;
                {
                    deviseMode.dmSize = sizeof(deviseMode);
                    deviseMode.dmPelsWidth = 1280;
                    deviseMode.dmPelsHeight = 720;
                    deviseMode.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;
                }
                ChangeDisplaySettings(&deviseMode, CDS_FULLSCREEN);
                fell = 1;
            }
            else
            {
                ChangeDisplaySettings(0, 0);
                fell = 0;
            }
            Sleep(500);
        }
        else if (GetKeyState('5') < 0)
        {
            cout << "Cheat finished" << endl;
            Sleep(1000);
            ReleaseDC(chwnd, cdc);
            ReleaseDC(myhwnd, mydc);
            DeleteObject(rec);
            DeleteObject(point);
            PostQuitMessage(0);
            return 0;
        }
        else if (clicks == 1 && GetKeyState(VK_LBUTTON) < 0)
        {
            for (int i = 0; i < 10; i++)
            {
                Sleep(100);

                mouse_event(MOUSEEVENTF_LEFTDOWN, point->x, point->y, 0, 0);
                Sleep(100);
                mouse_event(MOUSEEVENTF_LEFTUP, point->x, point->y, 0, 0);
            }
        }
        else if (GetKeyState('N') < 0)
        {
            if (clicks == 0)
            {
                clicks = 1;
                Sleep(300);
            }
            else if (clicks == 1)
            {
                clicks = 0;
                Sleep(300);
            }
        }*/
    }while(GetMessage(&msg, NULL, 0, 0));

    ReleaseDC(chwnd, cdc);
    ReleaseDC(myhwnd, mydc);
    DeleteObject(rec);
    DeleteObject(point);


    return 0;
}
