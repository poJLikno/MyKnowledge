#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <Windows.h>

using namespace std;

ofstream file;
HDC dc;
HWND hwnd;
PAINTSTRUCT ps;
int x1, y1, x2, y2, w, h;
char myString[100];
char myStringg[100];

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
    {
        KillTimer(hwnd, 1);
        ReleaseDC(hwnd, dc);
        PostQuitMessage(0);
    }
    else if (message == WM_CREATE)
    {
        dc = GetDC(hwnd);
        SetTimer(hwnd, 1, 15, NULL);
    }
    else if (message == WM_TIMER)
    {
        InvalidateRect(hwnd, NULL, TRUE);
    }
    else if (message == WM_PAINT)
    {
        ReleaseDC(hwnd, dc);

        dc = BeginPaint(hwnd, &ps);

        x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
        y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
        x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);

        w = x2 - x1;
        h = y2 - y1;

        HDC memDC = CreateCompatibleDC(dc);
        // Создание и частичное заполнение структуры формата
        BITMAPINFO BMI;
        BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BMI.bmiHeader.biWidth = w;
        BMI.bmiHeader.biHeight = h; // Отрицательное значение высоты, чтобы изображение не было перевёрнутым
        BMI.bmiHeader.biSizeImage = w * h * 3; // Ширина * Высота * Количество_цветов_на_пиксель
        BMI.bmiHeader.biCompression = BI_RGB;
        BMI.bmiHeader.biBitCount  = 24;
        BMI.bmiHeader.biPlanes = 1;

        DWORD ScreenshotSize;
        ScreenshotSize = BMI.bmiHeader.biSizeImage; // ScreenshotSize - глобальная переменная типа int, может меняться в ходе выполнения программы
        unsigned char *ImageBuffer; // Указатель на блок данных BGR, управляемый HBITMAP (да, именно BGR - не RGB)

        HBITMAP bitmap = CreateDIBSection(GetDC(NULL), &BMI,DIB_RGB_COLORS, (void**)&ImageBuffer, 0, 0);
        SelectObject(memDC, bitmap);
        BitBlt(memDC, 0, 0, w, h, GetDC(NULL), x1, y1, SRCCOPY);
        //BitBlt(dc, 0, 0, w, h, GetDC(NULL), x1, y1, SRCCOPY);

        BITMAPINFO bmi;
        memset(&bmi, 0, sizeof(BITMAPINFOHEADER));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biHeight = GetSystemMetrics(SM_CYSCREEN);
        bmi.bmiHeader.biWidth =  GetSystemMetrics(SM_CXSCREEN);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biSizeImage = w * h * 3;

        file.open("screenShot.jpg", ios_base::binary | ios_base::trunc);

        if (file.is_open())
        {
            int nBitsOffset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
            LONG lImageSize = w * h * 3 ;
            LONG lFileSize = nBitsOffset + lImageSize;
            BITMAPFILEHEADER bmfh;
            bmfh.bfType = 'B'+('M'<<8);
            bmfh.bfOffBits = nBitsOffset;
            bmfh.bfSize = lFileSize;
            bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

            file.write((char*) &bmfh, sizeof(BITMAPFILEHEADER));
            file.write((char*) &bmi, sizeof(BITMAPINFOHEADER));
            file.write((char*)ImageBuffer, w * h * 3);
        }

        file.close();

        DeleteDC(memDC);
        DeleteObject(bitmap);

        EndPaint(hwnd, &ps);
        PostQuitMessage(0);
    }
    else if (message == WM_KEYDOWN)
    {
        if (wparam == VK_ESCAPE)
        {
            KillTimer(hwnd, 1);
            ReleaseDC(hwnd, dc);
            PostQuitMessage(0);
        }
    }
    else return DefWindowProcA(hwnd, message, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    //wcl.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wcl.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcl.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcl.lpszClassName = "myApp";
    wcl.lpfnWndProc = WndProc;
    RegisterClassA(&wcl);

	hwnd = CreateWindow(wcl.lpszClassName, "MyApplication", WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;

    /*OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, bitmap);
    CloseClipboard();*/

	while (GetMessage(&msg, NULL, 0, 0))
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
	}


    return 0;
}
