#include "KeyboardListener.h"

KeyboardListener::~KeyboardListener()
{
    UnhookWindowsHookEx(keyboardHandle);
}

void KeyboardListener::StartListenKeyboard()
{
    keyboardHandle = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, NULL, NULL);
    if (!keyboardHandle)
        throw std::runtime_error("Couldn't create hook");
}

void KeyboardListener::StopListenKeyboard()
{
    UnhookWindowsHookEx(keyboardHandle);
}