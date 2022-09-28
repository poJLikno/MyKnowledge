#include "GraphGDI.h"

//Initialization
GraphGDI::GraphGDI()
{
    GdiplusStartupInput gdiplusStartupInput{};
    GdiplusStartup(GraphGDI::gdiplusTokenPointer, &gdiplusStartupInput, NULL);
}

GraphGDI::~GraphGDI()
{
    GraphGDI::gdiplusTokenPointer = nullptr;
    GdiplusShutdown(GraphGDI::gdiplusToken);
}

//Bufer
void GraphGDI::CreateDCBufer(HDC dc)
{
    GraphGDI::bufer = CreateCompatibleDC(dc);
    GraphGDI::bufbit = CreateCompatibleBitmap(dc, screenwidth, screenheight);
    SelectObject(GraphGDI::bufer, GraphGDI::bufbit);

    SelectObject(GraphGDI::bufer, GetStockObject(DC_BRUSH));
    SelectObject(GraphGDI::bufer, GetStockObject(DC_PEN));
}

void GraphGDI::ShowDCBufer(HDC dc)
{
    BitBlt(dc, 0, 0, screenwidth, screenheight, GraphGDI::bufer, 0, 0, SRCCOPY);
}

void GraphGDI::DeleteDCBufer()
{
    DeleteDC(GraphGDI::bufer);
    DeleteObject(GraphGDI::bufbit);
}