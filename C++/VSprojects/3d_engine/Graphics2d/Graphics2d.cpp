#include "Graphics2d.h"

void Graphics2d::CreateBuffer(PAINTSTRUCT *ps)
{
    dc = CreateCompatibleDC(ps->hdc);
    bitmap = CreateCompatibleBitmap(ps->hdc, WinWidth, WinHeight);
    SelectObject(dc, bitmap);

    SelectObject(dc, GetStockObject(DC_BRUSH));
    SelectObject(dc, GetStockObject(DC_PEN));
}

void Graphics2d::SetBuffer(PAINTSTRUCT *ps)
{
    BitBlt(ps->hdc, 0, 0, WinWidth, WinHeight, dc, 0, 0, SRCCOPY);
    DeleteDC(dc);
    dc = {};
    DeleteObject(bitmap);
    bitmap = {};
}

void Graphics2d::SetBrushColor(COLORREF color)
{
    SetDCBrushColor(dc, color);
}

void Graphics2d::SetPenColor(COLORREF color)
{
    SetDCPenColor(dc, color);
}

int Graphics2d::TranX(float x)
{
    return int((x + 0.5f) * (float)WinWidth);
}

int Graphics2d::TranY(float y)
{
    return int((float)WinHeight - (y + 0.5f) * (float)WinHeight);
}

void Graphics2d::DrawRect(float x, float y, float width, float height)
{
    Rectangle(dc, TranX(x), TranY(y), TranX(x + width), TranY(y - height));
}

void Graphics2d::DrawCircle(float x, float y, float radius)
{
    Ellipse(dc, TranX(x - radius), TranY(y + radius), TranX(x + radius), TranY(y - radius));
}

void Graphics2d::DrawPixel(float x, float y, COLORREF color)
{
    SetPixel(dc, TranX(x), TranY(y), color);
}

void Graphics2d::DrawLine(float x0, float y0, float x1, float y1)
{
    MoveToEx(dc, TranX(x0), TranY(y0), NULL);
    LineTo(dc, TranX(x1), TranY(y1));
}

Graphics2d::Graphics2d()
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

Graphics2d::~Graphics2d()
{
    Gdiplus::GdiplusShutdown(gdiplusToken);
}