#pragma once

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>

#pragma warning(disable : 4996)

using namespace std;

HDC dc;
RECT rect;
//HWND bt_quit;
HWND bt_save;
HWND edit;
HDC hdc;
HBITMAP bitmap;
BITMAP bimp;
float scale_cof;
char* way;
int sizex;
int sizey;
HFONT myFont;
SYSTEMTIME st;

void WaitingPress(HWND hwnd, SYSTEMTIME st)
{
    if (GetKeyState(VK_SNAPSHOT) < 0)
    {
        Sleep(500);
        ShowWindow(hwnd, SW_SHOWNORMAL);
        SetForegroundWindow(hwnd);
        InvalidateRect(hwnd, NULL, FALSE);
        Sleep(300);

        char* user = getenv("USERNAME");
        way = new char[101];
        GetLocalTime(&st);
        snprintf(way, 101, "C:\\Users\\%s\\Pictures\\screenshot_date(m-d-y)_%d-%d-%d_time(h-m-s)_%d-%d-%d.jpg", user, st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond);
        SetWindowText(edit, way);
    }
}

void DrawPreview()
{
    hdc = CreateCompatibleDC(dc);
    SelectObject(hdc, bitmap);
    StretchBlt(dc, sizex / 128, sizey / 72, sizex / 3.27, sizey / 3.27, hdc, 0, 0, (float)rect.right * scale_cof, (float)rect.bottom * scale_cof, SRCCOPY);
}

void DrawWindow()
{
    if (IsClipboardFormatAvailable(CF_BITMAP))
    {
        if (OpenClipboard(0))
        {
            SelectObject(dc, myFont);
            SelectObject(dc, GetStockObject(DC_PEN));
            SetDCPenColor(dc, RGB(170, 170, 170));
            SelectObject(dc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(dc, RGB(240, 240, 240));

            Rectangle(dc, 0, 0, sizex / 2, sizey / 3);
            SetBkMode(dc, TRANSPARENT);

            bitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
            CloseClipboard();

            GetObject(bitmap, sizeof(bimp), &bimp);
            scale_cof = (float)bimp.bmWidth / (float)rect.right;

            SetDCPenColor(dc, RGB(0, 0, 0));
            Rectangle(dc, sizex / 128 - 1, sizey / 72 - 1, sizex / 3.27 + sizex / 128 + 1, sizey / 3.27 + sizey / 72 + 1);

            DrawPreview();

            TextOut(dc, sizex / 3, sizey / 72, "Do you want to save screenshot?", 32);
        }
    }
}

void SavePicture(HWND hwnd)
{
    ShowWindow(hwnd, SW_HIDE);

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
    BMI.bmiHeader.biBitCount = 24;
    BMI.bmiHeader.biPlanes = 1;

    DWORD ScreenshotSize;
    ScreenshotSize = BMI.bmiHeader.biSizeImage;
    unsigned char* ImageBuffer;

    HDC memdc = CreateCompatibleDC(hdc);
    HBITMAP membitmap = CreateDIBSection(hdc, &BMI, DIB_RGB_COLORS, (void**)&ImageBuffer, 0, 0);
    SelectObject(memdc, membitmap);
    BitBlt(memdc, 0, 0, w, h, hdc, x1, y1, SRCCOPY);

    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(BITMAPINFOHEADER));
    {
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biHeight = h;
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biSizeImage = w * h * 3;
    }

    GetWindowText(edit, way, 100);

    ofstream filew;
    filew.open(way, ios_base::binary | ios_base::trunc);
    if (filew.is_open())
    {
        int nBitsOffset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        LONG lImageSize = w * h * 3;
        LONG lFileSize = nBitsOffset + lImageSize;
        BITMAPFILEHEADER bmfh;
        bmfh.bfType = 'B' + ('M' << 8);
        bmfh.bfOffBits = nBitsOffset;
        bmfh.bfSize = lFileSize;
        bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

        filew.write((char*)&bmfh, sizeof(BITMAPFILEHEADER));
        filew.write((char*)&bmi, sizeof(BITMAPINFOHEADER));
        filew.write((char*)ImageBuffer, w * h * 3);
    }
    filew.close();

    delete[] way;
    DeleteDC(memdc);
    DeleteObject(membitmap);
    DeleteDC(hdc);
    DeleteObject(bitmap);
}