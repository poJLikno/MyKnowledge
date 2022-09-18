#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    HWND hwnd;
    hwnd = FindWindow((LPCSTR)"ZSystemClass000", NULL);//ZSystemClass000//Valve001

    cout << "Ready\n";

    SetForegroundWindow(hwnd);
    while (true)
    {
        if (GetKeyState('J') < 0 && GetForegroundWindow() == hwnd)
        {
            keybd_event(0x57, MapVirtualKey(0x57, 0), 0, 0);// press W    !!!!it works!!!!!
            while (GetKeyState('J') < 0 && GetForegroundWindow() == hwnd);// <= press and remember, < just press
            keybd_event(0x57, MapVirtualKey(0x57, 0), KEYEVENTF_KEYUP, 0);// release W    !!!!it works!!!!!
            //keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//    !!!!it works!!!!!
            //keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), KEYEVENTF_KEYUP, 0);//    !!!!it works!!!!!
        }
    }


    return 0;
}
