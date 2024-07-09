#include "NormalFont.h"

NormalFont::NormalFont() {
    // Initialize NONCLIENTMETRICS structure
    NONCLIENTMETRICSW ncm = {};
    ncm.cbSize = sizeof(ncm);

    // Obtain non-client metrics
    SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);

    // Create the new font
    _normal_font = CreateFontIndirectW(&ncm.lfMessageFont);
}

NormalFont::~NormalFont() {
	DeleteObject((HGDIOBJ)_normal_font);
}

void NormalFont::SetFont(const HWND &hwnd) {
    // Set the new font
    SendMessageW(hwnd, WM_SETFONT, (WPARAM)_normal_font, NULL);
}

void NormalFont::SetFont(WndBase *wnd) {
    // Set the new font
    wnd->SendMsg(WM_SETFONT, (WPARAM)_normal_font, NULL);
}
