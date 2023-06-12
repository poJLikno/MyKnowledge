#include "Window.h"
#include "../KeyboardListener/KeyboardListener.h"
#include "../ComboBox/ComboBox.h"
#include "../Label/Label.h"
#include "../Edit/Edit.h"
#include "../Button/Button.h"

extern ComboBox *mouse_buttons;
extern Label *cps_label;
extern Edit *cps;
extern Label *toggle_label;
extern Button *change_button;

KeyboardListener *kbl;
bool wait_key = false;

PAINTSTRUCT ps;

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        kbl = new KeyboardListener;
        kbl->StartListenKeyboard();

        result = 1;
    }
    else
    {
        if (message == WM_COMMAND)
        {
            if (lParam == (LPARAM)mouse_buttons->hWnd)
            {
                //...
            }
            else if (lParam == (LPARAM)cps->hWnd)
            {
                //...
            }
            else if (lParam == (LPARAM)change_button->hWnd)
            {
                toggle_label->SetText("Press any key...");
                wait_key = true;
            }

            result = 0;
        }
        else if (message == WM_CTLCOLORSTATIC)// !!! For transparent "Label" !!!
        {
            SetBkMode(ps.hdc, TRANSPARENT);
            result = 0;
        }
        else if (message == WM_KEYDOWN)
        {
            if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
            result = 0;
        }
        else if (message == WM_CLOSE)
        {
            DestroyWindow(hWnd);
            result = 0;
        }
        else if (message == WM_DESTROY)
        {
            delete mouse_buttons;
            delete cps_label;
            delete cps;
            delete toggle_label;
            delete change_button;

            kbl->StopListenKeyboard();

            PostQuitMessage(0);
            result = 1;
        }
        else result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return result;
}