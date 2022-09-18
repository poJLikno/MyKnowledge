#include <iostream>
#include <fstream>
#include <Windows.h>
#include <winsock2.h>
#include <gdiplus.h>
#include <fstream>

using namespace std;
using namespace Gdiplus;

int sign[106];
//char symbols[101] = {Lbutton, Rbutton, Mbutton, BACKSPACE, TAB, ENTER, SHIFT, CTRL, ALT, CAPSLOCK, ESC, SPACE, PAGE_UP, PAGE_DOWN, END, HOME, LEFT_ARROW, UP_ARROW, RIGHT_ARROW, DOWN_ARROW, PRT_SCREEN, INSERT, DELETE, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, `~, -_, =+, [{, ]}, ;:, '", \|, <,, >., /?, LWIN, RWIN, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, NUM_LOCK, SCROLL_LOCK, NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_*, NUM_+, NUM_-, NUM_., NUM_/};
int codes[101] = {0x01, 0x02, 0x04, 0x08, 0x09, 0x0D, 0x10, 0x11, 0x12, 0x14, 0x1B, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x2C, 0x2D, 0x2E, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0xC0, 0xBD, 0xBB, 0xDB, 0xDD, 0xBA, 0xDE, 0xDC, 0xBC, 0xBE, 0xBF, 0x5B, 0x5C, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x90, 0x91, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E};
HDC dc;
LPPOINT point;
LPRECT lpRect;
SOCKET netSocket;
PAINTSTRUCT ps;
bool winmode = 0;
ULONG_PTR gdiplusToken;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR lpCmdLine, int nCmdShow)//            CLIENT
{
    //check IP
    char *ip;
    int fsize = 0;
    ifstream filer;
    ofstream filew;
    filer.open("configs.txt", ios_base::binary);
    if (filer.is_open())
    {
        filer.seekg(0, ios_base::end);
        fsize = filer.tellg();
        ip = new char[fsize];
        filer.seekg(0, ios_base::beg);
        filer.read(ip, fsize);
    }
    else
    {
        filew.open("configs.txt", ios_base::binary | ios_base::trunc);
        if (filew.is_open())
        {
            filew.write("Enter server's IP", 17);
            MessageBox(NULL, "Server's IP wasn't found.\nMight it wasn't entered in \"configs.txt\" file.\nCheck it.", "Error", MB_OK);
            return 0;
        }
        filew.close();
    }
    filer.close();


	//connection
    WSADATA wsData;
    WSAStartup(MAKEWORD(2,2), &wsData);

    netSocket = socket(AF_INET, SOCK_STREAM, 0);

    HOSTENT *host = gethostbyname(ip);

    delete[] ip;

    struct sockaddr_in netInfo;
    ZeroMemory(&netInfo, sizeof(netInfo));
    netInfo.sin_family = AF_INET;
    netInfo.sin_port = htons(8000);
    memcpy(&netInfo.sin_addr.S_un.S_addr, host -> h_addr_list[0], sizeof(netInfo.sin_addr.S_un.S_addr));

    connect(netSocket, (struct sockaddr *)&netInfo, sizeof(netInfo));


    //GDI+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //display size
    lpRect = (LPRECT)malloc(sizeof(*lpRect));
    GetClientRect(GetDesktopWindow(), lpRect);


    //create window
	WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.style = CS_OWNDC;
    wcl.lpfnWndProc = WndProc;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hInstance = hInstance;
    wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.hbrBackground = (HBRUSH)(6);
    wcl.lpszMenuName = 0;
    wcl.lpszClassName = "class";
    RegisterClassA(&wcl);

    HWND hwnd;
	hwnd = CreateWindow(wcl.lpszClassName, "WirelessGameInput_client", WS_POPUP, 0, 0, lpRect[0].right, lpRect[0].bottom, NULL, NULL, NULL, NULL);

	dc = GetDC(hwnd);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;


    memset(&sign, 0, sizeof(sign));

    sign[104] = lpRect[0].right / 2;
    sign[105] = lpRect[0].bottom / 2;

    point = (LPPOINT)malloc(sizeof(*point));

	while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        send(netSocket, (const char*)sign, sizeof(sign), 0);

        if (winmode == 0)
        {
            SetCursorPos(lpRect[0].right / 2, lpRect[0].bottom / 2);
        }

        sign[101] = 0;
    }

	closesocket(netSocket);

	GdiplusShutdown(gdiplusToken);


    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_KEYDOWN && wparam == 'V')
    {
        if (winmode == 0)
        {
            winmode = 1;
            //SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
            SetWindowPos(hwnd, HWND_TOP, lpRect[0].right / 4, lpRect[0].bottom / 4, lpRect[0].right / 2, lpRect[0].bottom / 2, SWP_SHOWWINDOW);
            //sign[8] = 0;
            //sign[50] = 0;
        }
        else
        {
            winmode = 0;
            //SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
            SetWindowPos(hwnd, HWND_TOP, 0, 0, lpRect[0].right, lpRect[0].bottom, SWP_SHOWWINDOW);
            //sign[8] = 0;
            //sign[50] = 0;
        }
        Sleep(500);
    }

    if (message == WM_DESTROY)
    {
		free(lpRect);
        KillTimer(hwnd, 1);
        closesocket(netSocket);
        ReleaseDC(hwnd, dc);
        GdiplusShutdown(gdiplusToken);
        PostQuitMessage(0);
    }
    if (message == WM_CREATE)
    {
        SetTimer(hwnd, 1, 500, NULL);
    }
    if (message == WM_TIMER)
    {
        InvalidateRect(hwnd, NULL, /*TRUE*/FALSE);
    }
    if (message == WM_PAINT)
    {
        dc = BeginPaint(hwnd, &ps);
        Image image(L"screenshot_recived.jpg");
        Graphics graphics(dc);
        graphics.DrawImage(&image, 0, 0, lpRect[0].right, lpRect[0].bottom);

        /*char *user = getenv("USERNAME");
        char *way = (char*)malloc(100);
        snprintf(way, 100, "cd \"C:\\Users\\%s\\Desktop\"", user);
        system(way);
        snprintf(way, 100, "C:\\Users\\%s\\Desktop\\screenshot_recived.bmp", user);*/
        //BITMAP Bitmap;
        //HDC hdc = CreateCompatibleDC(dc);
        //system("magick mogrify -format bmp *.jpg");
        //HBITMAP bitmap = (HBITMAP)LoadImage(NULL, "picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        //GetObject(bitmap, sizeof(BITMAP), &Bitmap);
        //SelectObject(hdc, bitmap);
        //BitBlt(dc, 0, 0, lpRect[0].right, lpRect[0].bottom, hdc, 0, 0, SRCCOPY);

        //free(way);
        //DeleteDC(hdc);
        //DeleteObject(bitmap);

        EndPaint(hwnd, &ps);
    }

    if (winmode == 0)
    {
        if (GetKeyState(0x12) < 0 && GetKeyState(0x43) < 0)
        {
			free(lpRect);
            sign[8] = 0;
            sign[35] = 0;
            KillTimer(hwnd, 1);
            closesocket(netSocket);
            ReleaseDC(hwnd, dc);
            GdiplusShutdown(gdiplusToken);
            PostQuitMessage(0);
            return 0;
        }

        for (int i = 0; i < 101; i++)
        {
            if (GetKeyState(codes[i]) < 0 && sign[i] != 1)
            {
                sign[i] = 1;
            }
            else if (GetKeyState(codes[i]) >= 0 && sign[i] != 0)
            {
                sign[i] = 0;
            }
        }

        if (message == WM_MOUSEMOVE)
        {
            GetCursorPos(point);

            if (point[0].x != sign[102] || point[0].y != sign[103])
            {
                sign[102] = point[0].x;
                sign[103] = point[0].y;
            }
        }
        if (message == WM_MOUSEWHEEL)
        {
            sign[101] = GET_WHEEL_DELTA_WPARAM(wparam);
        }
        else return DefWindowProcA(hwnd, message, wparam, lparam);
    }
}
