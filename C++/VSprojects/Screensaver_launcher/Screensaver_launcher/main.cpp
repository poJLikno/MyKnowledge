#include <windows.h>

int main(int argc, const char *argv[])
{
	HWND console_handle = GetConsoleWindow();
	ShowWindow(console_handle, SW_HIDE);

	while (true)
	{
		if (GetKeyState(VK_SNAPSHOT) < 0)
		{
			Sleep(250);
			system("start dialog_window.exe");
			Sleep(1000);
		}
		else if (GetKeyState('S') < 0 && GetKeyState('P') < 0) break;
		Sleep(5);
	}

	return EXIT_SUCCESS;
}