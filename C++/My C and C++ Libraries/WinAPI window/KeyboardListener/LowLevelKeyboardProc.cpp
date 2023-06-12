#include "KeyboardListener.h"
#include "../Label/Label.h"

extern Label *toggle_label;
extern bool wait_key, flag;

int vk_code = 76;

LRESULT CALLBACK KeyboardListener::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    HHOOK hkb = 0;
    if (nCode < 0)
        return CallNextHookEx(hkb, nCode, wParam, lParam);

    if (HC_ACTION == nCode)
    {
        if (wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
            if (wait_key)
            {
                char buffer[21] = {};
                snprintf(buffer, sizeof(buffer), "Toggle key: %d", (int)p->vkCode);
                toggle_label->SetText(buffer);
                wait_key = false;
                vk_code = (int)p->vkCode;
            }
            else if (vk_code == (int)p->vkCode)
            {
                flag = !flag;
            }
            //delete p;
        }
        /*else if (wParam == WM_KEYUP)
        {
            KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
            char res[20] = {};
            snprintf(res, sizeof(res), "up%d", (int)p->vkCode);

        }*/
    }
    return CallNextHookEx(hkb, nCode, wParam, lParam);
}