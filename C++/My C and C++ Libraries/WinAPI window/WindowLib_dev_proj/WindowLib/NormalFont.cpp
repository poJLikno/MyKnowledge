#include "NormalFont.h"

NormalFont::NormalFont() {
    // Initialize NONCLIENTMETRICS structure
    NONCLIENTMETRICS ncm = {};
    ncm.cbSize = sizeof(ncm);

    // Obtain non-client metrics
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);

    // Create the new font
    _normal_font = CreateFontIndirect(&ncm.lfMessageFont);
}

NormalFont::~NormalFont() {
	DeleteObject((HGDIOBJ)_normal_font);
}

void NormalFont::SetFont(const HWND &hwnd) {
    // Set the new font
    SendMessage(hwnd, WM_SETFONT, (WPARAM)_normal_font, NULL);
}

void NormalFont::SetFont(WndBase *wnd) {
    // Set the new font
    wnd->SendMsg(WM_SETFONT, (WPARAM)_normal_font, NULL);
}
