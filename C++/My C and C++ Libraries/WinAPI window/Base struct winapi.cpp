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

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    {
        wc.style = CS_OWNDC;// or CS_VREDRAW | CS_HREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);// or wcl.hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);
        wc.lpszMenuName = 0;
        wc.lpszClassName = "class";
    }
    
    if (!RegisterClass(&wc))
	{
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }
	
	HWND hwnd;
	hwnd = CreateWindow(wc.lpszClassName, "MyApplication", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, NULL, NULL, NULL, NULL);
    
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

	return static_cast<int>(msg.wParam);
}
