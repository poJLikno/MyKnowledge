#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <gdiplus.h>

#include "Classes.h"
#include <irrKlang.h>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "irrKlang.lib")

using namespace Gdiplus;
using namespace irrklang;

//Global variables
HDC dc;
PAINTSTRUCT ps;
HANDLE soundsThread;
ULONG_PTR gdiplusToken;
bool menu = 0;
//------

//Objects
ISoundEngine* engine = createIrrKlangDevice();
ISound* fire_con;
//------

//Sounds names
const char* steps = "C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/sounds/steps.wav";
const char* run = "C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/sounds/run.wav";
const char* fire = "C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/sounds/ak-47_fire.wav";
//------

//Functions declarations

DWORD WINAPI Sounds(LPVOID param);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

//------

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    {
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);// or wcl.hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszMenuName = 0;
        wc.lpszClassName = "class";
    }

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }

    GetClientRect(GetDesktopWindow(), &Display);
    player.rays_num = Display.right;
    player.delta_angle = (float)player.FOV / player.rays_num;

    HWND hwnd;
    hwnd = CreateWindow(wc.lpszClassName, "RayCasting", WS_POPUP, 0, 0, Display.right, Display.bottom, NULL, NULL, NULL, NULL);

    if (!hwnd)
    {
        MessageBox(NULL, "Can't create window", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    ShowCursor(FALSE);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_CREATE)
    {
        //GDI+
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        SetTimer(hwnd, 1, 10, NULL);
        soundsThread = CreateThread(NULL, 0, Sounds, NULL, 0, NULL);
    }
    else if (message == WM_TIMER)
    {
        if (!menu && GetForegroundWindow() == hwnd)
        {
            player.keyboard();
            player.mouse_buttons();
        }
        InvalidateRect(hwnd, NULL, FALSE);
    }
    else if (message == WM_PAINT)
    {
        dc = BeginPaint(hwnd, &ps);

        HDC buferDC = CreateCompatibleDC(dc);
        HBITMAP bit = CreateCompatibleBitmap(dc, Display.right, Display.bottom);
        SelectObject(buferDC, bit);

        SelectObject(buferDC, GetStockObject(DC_BRUSH));
        SelectObject(buferDC, GetStockObject(DC_PEN));

        if (menu)
        {
            //DrawStartMenu(hwnd, buferDC);
        }
        else
        {
            DrawGame(buferDC);
        }

        //Draw bufer
        BitBlt(dc, 0, 0, Display.right, Display.bottom, buferDC, 0, 0, SRCCOPY);

        DeleteDC(buferDC);
        DeleteObject(bit);

        EndPaint(hwnd, &ps);
    }
    else if (message == WM_KEYDOWN)
    {
        if (wparam == VK_ESCAPE)
        {
            menu = 1;
            PlaySound(NULL, NULL, NULL);
            engine->stopAllSounds();
            ShowCursor(TRUE);
        }
    }
    else if (message == WM_MOUSEMOVE)
    {
        if (!menu && GetForegroundWindow() == hwnd) player.mouse_transition();
    }
    else if (message == WM_CLOSE)
    {
        DestroyWindow(hwnd);
    }
    else if (message == WM_DESTROY)
    {
        engine->drop();
        CloseHandle(soundsThread);

        GdiplusShutdown(gdiplusToken);

        KillTimer(hwnd, 1);
        PostQuitMessage(0);
    }
    else return DefWindowProc(hwnd, message, wparam, lparam);

    return TRUE;
}

DWORD WINAPI Sounds(LPVOID param)
{
    while (1)
    {
        Sleep(10);
        if (!menu)
        {
            //MouseButtons
            if (player.lbut != player.previous_lbut && player.lbut)
            {
                fire_con = engine->play2D(fire, true, false, true);

                player.previous_lbut = player.lbut;
                Sleep(160);
            }
            else if (player.lbut != player.previous_lbut && !player.lbut)
            {
                fire_con->stop();
                fire_con = 0;

                player.previous_lbut = player.lbut;
            }
            //------

            //Keyboard
            if (player.w_walk != player.previous_w_walk && player.w_walk && player.run)
            {
                PlaySound(run, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else if (player.w_walk != player.previous_w_walk && !player.w_walk && player.walk && player.run)
            {
                PlaySound(steps, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else if (player.walk != player.previous_walk && !player.walk && player.run)
            {
                PlaySound(NULL, NULL, NULL);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else if (player.walk != player.previous_walk && player.walk)
            {
                PlaySound(steps, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else if (player.run != player.previous_run && player.run && player.w_walk)
            {
                PlaySound(run, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else if (player.run != player.previous_run && !player.run && player.w_walk)
            {
                PlaySound(steps, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else if (player.walk != player.previous_walk && !player.walk && player.run)
            {
                PlaySound(NULL, NULL, NULL);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else if (player.walk != player.previous_walk && !player.walk)
            {
                PlaySound(NULL, NULL, NULL);

                player.previous_walk = player.walk;
                player.previous_w_walk = player.w_walk;
                player.previous_run = player.run;
            }
            else {}
            //------
        }
    }
}
