#include <iostream>
#include <windows.h>

LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);

int main(int argc, const char *argv[])
{
	HHOOK keyboardHandle = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, NULL, NULL);

    MSG msg{};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    HHOOK hkb = 0;
    if (nCode < 0)
        return CallNextHookEx(hkb, nCode, wParam, lParam);

    if (HC_ACTION == nCode)
    {
        if (wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
            std::cout << p->vkCode << " : " << p->scanCode << '\n';
        }
    }
    return CallNextHookEx(hkb, nCode, wParam, lParam);
}