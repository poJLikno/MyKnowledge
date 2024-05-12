#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, const char **argv) {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	for (int i = 0; i < argc; ++i) {
		printf("%s\n", argv[i]);
	}
	system("pause");

	HWND hwnd = NULL;
	char key = '\0';
	char state_flag = 0;

	if (argc > 2) {
		hwnd = FindWindowA(NULL, (LPCSTR)argv[1]);
		key = argv[2][0];
	}
	else {
		char app_name[32] = { 0 };

		printf("Enter app window name: ");
		fgets(app_name, sizeof(app_name), stdin);// String contains \n
		app_name[strlen(app_name) - 1] = '\0';
		hwnd = FindWindowA(NULL, (LPCSTR)app_name);

		printf("Enter hot-key (CAPS-only): ");
		key = fgetc(stdin);
		fgetc(stdin);// Skip \n
	}

	if (!hwnd || !key) {
		perror("Couldn't get window and/or hot-key");
		exit(1);
	}
	
	printf("Start loop (esc to close)...\n");
	while (1) {
		if (GetAsyncKeyState('L') < 0) {
			SetWindowPos(hwnd, (state_flag ? HWND_NOTOPMOST : HWND_TOPMOST), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			printf(state_flag ? "Top most - OFF\n" : "Top most = ON\n");
			state_flag = ~state_flag;
			Sleep(500);
		}
		else if (GetAsyncKeyState(VK_ESCAPE) < 0 && GetForegroundWindow() == GetConsoleWindow()) {
			break;
		}
		Sleep(1);
	}
	printf("Close programm\n");

	return 0;
}