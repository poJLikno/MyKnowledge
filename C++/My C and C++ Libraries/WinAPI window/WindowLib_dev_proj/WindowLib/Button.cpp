#include "Button.h"

Button::Button(const char *text, WndPairValue pos, WndPairValue size)
    : WndBase(pos, size), _text(text) {}

void Button::SetWndParent(WndBase *wnd) {
    int text_size = (int)strlen(_text) + 1;
    wchar_t *w_text = new wchar_t[text_size] { 0 };
    MultiByteToWideChar(CP_UTF8, 0, _text, text_size, w_text, text_size);

    this->_parent_wnd = wnd;
    _hwnd = CreateWindowExW(0L, L"button", w_text, WS_VISIBLE | WS_CHILD | WS_TABSTOP /*WS_POPUP*/,
        _pos.first, _pos.second,
        _size.first, _size.second,
        wnd->GetHwnd(), NULL, NULL, NULL);
    if (!_hwnd)
        throw std::string("Can't create button -> Error code: " + std::to_string(GetLastError()));

    delete[] w_text;
    w_text = nullptr;
}
