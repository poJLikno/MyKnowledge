#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

UINT colvo = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY) PostQuitMessage(0);
    else if (message == WM_CHAR)
    {
        if (wparam == 13)
        {
            if (colvo == 20)
            {
                cout << " Enter " << endl;
                colvo = 0;
            }
            else
            {
                cout << " Enter ";
            }
            colvo++;
        }
        else if (wparam == 8)
        {
            if (colvo == 20)
            {
                cout << " Backspace " << endl;
                colvo = 0;
            }
            else
            {
                cout << " Backspace ";
            }
            colvo++;
        }
        else if (wparam == 9)
        {
            if (colvo == 20)
            {
                cout << " Tab " << endl;
                colvo = 0;
            }
            else
            {
                cout << " Tab ";
            }
            colvo++;
        }
        else
        {
            if (colvo == 20)
            {
                cout << (char)wparam << endl;
                colvo = 0;
            }
            else
            {
                cout << (char)wparam;
            }
            colvo++;
        }
    }
    else return DefWindowProcA(hwnd, message, wparam, lparam);
}


int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "ready" << endl;

    WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.lpszClassName = "keyloger";
    wcl.lpfnWndProc = WndProc;
    RegisterClassA(&wcl);

	HWND hwnd;
	hwnd = CreateWindow(wcl.lpszClassName, "MyApplication", WS_OVERLAPPEDWINDOW/*WS_POPUP*/, 100, 100, 600, 600, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
	}


    return 0;
}
