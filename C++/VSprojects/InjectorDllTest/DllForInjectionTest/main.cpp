#include <iostream>
#include <string>
#include <windows.h>

BOOL WINAPI mainThread() {
    while (true) {
        if (GetAsyncKeyState('M') < 0)
        {
            std::wcout << L"M has been pressed!\r\n";
            Sleep(1000);
        }
        Sleep(1);
    }

    return TRUE;
}

BOOL WINAPI DllMain(HMODULE dllModule, DWORD reasonCode, LPVOID lpvReserved) {
    switch (reasonCode)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(dllModule);
            MessageBox(NULL, L"Dll has been Attached", L"Dll Message", MB_OK);

            {// Create console
                AllocConsole();
                FILE *f = nullptr;
                freopen_s(&f, "CONOUT$", "w", stdout);
            }

            setlocale(LC_ALL, "");
            _wsetlocale(LC_ALL, L"");
            SetConsoleCP(1251);
            SetConsoleOutputCP(1251);

            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mainThread, NULL, NULL, NULL);
            break;

        case DLL_PROCESS_DETACH:
            HWND hWnd = GetConsoleWindow();
            FreeConsole();
            SendMessage(hWnd, WM_CLOSE, NULL, NULL);
            break;
    }

    return TRUE;
}