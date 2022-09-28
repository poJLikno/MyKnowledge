#include "main.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    try
    {
        Window window("MyGame", 100, 100, hInstance);

        while (GetMessage(&window.msg, NULL, 0, 0))
        {
            TranslateMessage(&window.msg);
            DispatchMessage(&window.msg);
        }
    }
    catch (runtime_error error)
    {
        MessageBox(NULL, error.what(), "Error", MB_OK);
    }

    return 0;
}