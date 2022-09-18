#include <stdio.h>
#include <iostream>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR lpCmdLine, int nCmdShow)
{
    setlocale(LC_ALL, "Russian");

	WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.lpszClassName = "MyApp";
    RegisterClassA(&wcl);

	HWND hwnd;
	hwnd = GetConsoleWindow();

	char symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char essymbols[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char rsymbols[] = "ÔÈÑÂÓÀÏÐØÎËÄÜÒÙÇÉÊÛÅÃÌÖ×ÍßÁ¨ÆÕÚÝÞ";

	while (true)
	{
	    LOWORD(GetKeyboardLayout(0));
        for (int i = 0; i < sizeof(symbols); i++)
        {
            if (GetKeyState(symbols[i]) < 0)
            {
                if (LOWORD(GetKeyboardLayout(0)) == 0x0409)
                {
                    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 ^ (GetKeyState(VK_SHIFT) & 0x8000) != 0)
                    {
                        printf("Pressed key: %c\n", symbols[i]);
                        Sleep(200);
                    }
                    else
                    {
                        printf("Pressed key: %c\n", essymbols[i]);
                        Sleep(200);
                    }
                }
                else if (LOWORD(GetKeyboardLayout(0)) == 0x0419)
                {
                    printf("Pressed key: %c\n", rsymbols[i]);
                    Sleep(200);
                }
            }
        }

        if (GetKeyState(VK_MENU) < 0 && GetKeyState(VK_SHIFT) < 0)
        {
            printf("Pressed key: ALT + SHIFT\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_SPACE) < 0)
        {
            printf("Pressed key: SPACE\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_CAPITAL) < 0)
        {
            printf("Pressed key: CAPS\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_TAB) < 0)
        {
            printf("Pressed key: TAB\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_RETURN) < 0)
        {
            printf("Pressed key: ENTER\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_CONTROL) < 0)
        {
            printf("Pressed key: CTRL\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_MENU) < 0)
        {
            printf("Pressed key: ALT\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_ESCAPE) < 0)
        {
            printf("Pressed key: ESC\n");
            Sleep(200);
        }
        else if (GetKeyState(VK_BACK) < 0)
        {
            printf("Pressed key: BACKSPACE\n");
            Sleep(200);
        }
	}

	return 0;
}
