#include "Window.h"

HDC dc{};
PAINTSTRUCT ps{};
GraphGDI* paint = nullptr;
//World gameworld;
Player player1(250.f, 350.f, 0.f, 100, 300);
MiniMap worldmap;


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

//Initialization
Window::Window(const char* name, unsigned short pos_x, unsigned short pos_y, HINSTANCE& hInstance)
{
    WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    {
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, iconwidth, iconheight, LR_LOADFROMFILE);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(6);
        wc.lpszMenuName = 0;
        wc.lpszClassName = "my_game_class";
    }
    if (!RegisterClass(&wc)) throw runtime_error("Couldn't register class");

    Window::hwnd = CreateWindow(wc.lpszClassName, name, WS_POPUP, pos_x, pos_y, screenwidth, screenheight, NULL, NULL, NULL, NULL);
    if (!Window::hwnd) throw runtime_error("Couldn't create window");

    ShowWindow(Window::hwnd, SW_SHOWNORMAL);
}

//Message function
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_CREATE)
    {
        paint = new GraphGDI();
        SetTimer(hwnd, 1, 10, NULL);
        return 0;
    }
    else if (message == WM_TIMER)
    {
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }
    else if (message == WM_PAINT)
    {
        dc = BeginPaint(hwnd, &ps);

        paint->CreateDCBufer(dc);

        //gameworld.RayCasting(paint->bufer, player1.pos_x, player1.pos_y, player1.angle, player1.max_ray_depth);
        worldmap.ShowMap(paint->bufer, player1.pos_x, player1.pos_y, player1.angle, player1.max_ray_depth, 1.f);
        player1.angle += 0.25;

        paint->ShowDCBufer(dc);
        paint->DeleteDCBufer();

        EndPaint(hwnd, &ps);
        return 0;
    }
    else if (message == WM_KEYDOWN)
    {
        if (wparam == VK_ESCAPE) DestroyWindow(hwnd);
        return 0;
    }
    else if (message == WM_CLOSE)
    {
        DestroyWindow(hwnd);
        return 0;
    }
    else if (message == WM_DESTROY)
    {
        delete paint;
        paint = nullptr;
        ReleaseDC(hwnd, dc);
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        return 0;
    }
    else return DefWindowProc(hwnd, message, wparam, lparam);
}