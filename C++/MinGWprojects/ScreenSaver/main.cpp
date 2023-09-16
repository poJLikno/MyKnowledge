#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

HDC dc;
PAINTSTRUCT ps;
RECT rect;
HWND bt_quit;
HWND bt_save;
HWND cap;
HWND edit;
HDC hdc;
HBITMAP bitmap;
BITMAP bimp;
float scale_cof;
char *way;
SYSTEMTIME st;
int sizex;
int sizey;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.style = CS_VREDRAW | CS_HREDRAW/*CS_OWNDC*/;
    wcl.lpfnWndProc = WndProc;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hInstance = hInstance;
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.hbrBackground = (HBRUSH)(6);
    wcl.lpszMenuName = 0;
    wcl.lpszClassName = "class";
    wcl.hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE);

    if (!RegisterClassA(&wcl))
	{
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }

    //Display size if < 1600x900, default program resolution
    GetClientRect(GetDesktopWindow(), &rect);
    //------------
    sizex = (rect.right < 1600) ? 1600 : rect.right;
    sizey = (rect.bottom < 900) ? 900 : rect.bottom;

	HWND hwnd;
	hwnd = CreateWindow(wcl.lpszClassName, "ScreenSaver", WS_POPUP, rect.right / 4, rect.bottom / 2 - rect.bottom / 6, sizex / 2, sizey / 3,NULL, NULL, NULL, NULL);

	if (!hwnd)
	{
        MessageBox(NULL, "Can't create window", "Error", MB_OK);
        return 0;
    }

	ShowWindow(hwnd, SW_HIDE);

	bt_quit = CreateWindow("button", "X", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, sizex / 2.11, 0, sizex / 38.4, sizey / 21.6, hwnd, NULL, NULL, NULL);
	bt_save = CreateWindow("button", "Save", WS_VISIBLE | WS_CHILD, sizex / 2.23256, sizey / 3.48, sizex / 19.2, sizey / 21.6, hwnd, NULL, NULL, NULL);
    edit = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT, sizex / 2.9538, sizey / 21.6, sizex / 8.727, sizey / 54, hwnd, NULL, NULL, NULL);

	MSG msg;

    while (1)
    {
        if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (GetKeyState(VK_SNAPSHOT) < 0)
            {
                Sleep(500);
                ShowWindow(hwnd, SW_SHOWNORMAL);
                SetForegroundWindow(hwnd);
                InvalidateRect(hwnd, NULL, FALSE);
                Sleep(300);

                char *user = getenv("USERNAME");
                way = (char*)malloc(100);
                GetLocalTime(&st);
                snprintf(way, 100, "C:\\Users\\%s\\Pictures\\screenshot_date(m-d-y)_%d-%d-%d_time(h-m-s)_%d-%d-%d.jpg", user, st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond);
                SetWindowText(edit, way);
            }
        }
    }

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
    {
        free(way);
        DeleteDC(hdc);
        DeleteObject(bitmap);
        ReleaseDC(hwnd, dc);
        PostQuitMessage(0);
    }
    else if (message == WM_PAINT)
    {
        dc = BeginPaint(hwnd, &ps);

        if (IsClipboardFormatAvailable(CF_BITMAP))
        {
            if (OpenClipboard(0))
            {
                SelectObject(dc, GetStockObject(DC_PEN));
                SetDCPenColor(dc, RGB(170, 170, 170));
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(240, 240, 240));
                Rectangle(dc, 0, 0, sizex / 2, sizey / 3);
                SetBkMode(dc, TRANSPARENT);
                bitmap = GetClipboardData(CF_BITMAP);
                CloseClipboard();
                GetObject(bitmap, sizeof(bimp), &bimp);
                scale_cof = (float)bimp.bmWidth / (float)rect.right;
                hdc = CreateCompatibleDC(dc);
                SelectObject(hdc, bitmap);
                SetDCPenColor(dc, RGB(0, 0, 0));
                Rectangle(dc, sizex / 128 - 1, sizey / 72 - 1, sizex / 3.27 + sizex / 128 + 1, sizey / 3.27 + sizey / 72 + 1);
                StretchBlt(dc, sizex / 128, sizey / 72, sizex / 3.27, sizey / 3.27, hdc, 0, 0, (float)rect.right * scale_cof, (float)rect.bottom * scale_cof, SRCCOPY);
                TextOut(dc, sizex / 3, sizey / 72, "Do you want to save screenshot?", 31);
            }
        }

        EndPaint(hwnd, &ps);
    }
    else if (message == WM_COMMAND)
    {
        if (lparam == bt_quit)
        {
            ShowWindow(hwnd, SW_HIDE);
            free(way);
            DeleteDC(hdc);
            DeleteObject(bitmap);
        }
        if (lparam == bt_save)
        {
            ShowWindow(hwnd, SW_HIDE);

            ofstream filew;

            float x1, y1, x2, y2, w, h;

            x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
            y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
            x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
            y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);

            w = scale_cof * (x2 - x1);
            h = scale_cof * (y2 - y1);

            BITMAPINFO BMI;
            BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            BMI.bmiHeader.biWidth = w;
            BMI.bmiHeader.biHeight = h;
            BMI.bmiHeader.biSizeImage = w * h * 3;
            BMI.bmiHeader.biCompression = BI_RGB;
            BMI.bmiHeader.biBitCount  = 24;
            BMI.bmiHeader.biPlanes = 1;

            DWORD ScreenshotSize;
            ScreenshotSize = BMI.bmiHeader.biSizeImage;
            unsigned char *ImageBuffer;

            HDC memdc = CreateCompatibleDC(hdc);
            HBITMAP membitmap = CreateDIBSection(hdc, &BMI,DIB_RGB_COLORS, (void**)&ImageBuffer, 0, 0);
            SelectObject(memdc, membitmap);
            BitBlt(memdc, 0, 0, w, h, hdc, x1, y1, SRCCOPY);

            BITMAPINFO bmi;
            memset(&bmi, 0, sizeof(BITMAPINFOHEADER));
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biHeight = h;
            bmi.bmiHeader.biWidth =  w;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 24;
            bmi.bmiHeader.biCompression = BI_RGB;
            bmi.bmiHeader.biSizeImage = w * h * 3;

            GetWindowText(edit, way, 100);

            filew.open(way, ios_base::binary | ios_base::trunc);
            if (filew.is_open())
            {
                int nBitsOffset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
                LONG lImageSize = w * h * 3 ;
                LONG lFileSize = nBitsOffset + lImageSize;
                BITMAPFILEHEADER bmfh = { 0 };
                {
					bmfh.bfType = 'B'+('M'<<8);
					bmfh.bfOffBits = nBitsOffset;
					bmfh.bfSize = lFileSize;
					bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
				}

                filew.write((char*) &bmfh, sizeof(BITMAPFILEHEADER));
                filew.write((char*) &bmi, sizeof(BITMAPINFOHEADER));
                filew.write((char*)ImageBuffer, w * h * 3);
            }
            filew.close();

            free(way);
            DeleteDC(memdc);
            DeleteObject(membitmap);
            DeleteDC(hdc);
            DeleteObject(bitmap);
        }
    }
    else return DefWindowProcA(hwnd, message, wparam, lparam);
}
