#include <iostream>
#include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	bool flag = false;
	HWND hWnd = FindWindow(NULL, (LPCSTR)"STATMAN");
	
	while (true)
	{
		if (GetKeyState('L') < 0)
		{
			if (!flag)
				SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			else if (flag)
				SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			flag = !flag;
			Sleep(500);
		}
		else if (GetKeyState('K') < 0) break;
		Sleep(1);
	}

	return 0;
}