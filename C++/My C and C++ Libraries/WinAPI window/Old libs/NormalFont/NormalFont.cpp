#include "NormalFont.h"

NormalFont::NormalFont()
{
    // initialize NONCLIENTMETRICS structure
    NONCLIENTMETRICS ncm = {};
    ncm.cbSize = sizeof(ncm);

    // obtain non-client metrics
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);

    // create the new font
    hNewFont = CreateFontIndirect(&ncm.lfMessageFont);
}

void NormalFont::SetFont(HWND hWnd)
{
    // set the new font
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hNewFont, 0);
}
