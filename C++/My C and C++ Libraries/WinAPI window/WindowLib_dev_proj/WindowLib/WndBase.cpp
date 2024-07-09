#include "WndBase.h"

WndBase::~WndBase() {
    _parent_wnd = nullptr;
}

void WndBase::ShowWnd(const bool &flag) {
    _is_visible = flag;
    ShowWindow(this->_hwnd, (flag ? SW_SHOWNORMAL : SW_HIDE));
    if (flag) UpdateWindow(this->_hwnd);
}

LRESULT WndBase::SendMsg(const UINT &msg, const WPARAM &wparam, const LPARAM &lparam) {
    return SendMessageW(this->_hwnd, msg, wparam, lparam);
}

HWND WndBase::GetHwnd() {
    return this->_hwnd;
}

void WndBase::GetWndText(char *buffer, const int &count) {
    wchar_t *w_buffer = new wchar_t[count] { 0 };

    int result = GetWindowTextW(this->_hwnd, w_buffer, (int)count);
    if (!result)
        throw std::string("Can't get text -> Error code: " + std::to_string(GetLastError()));

    WideCharToMultiByte(CP_UTF8, 0, w_buffer, (int)count, buffer, (int)count, 0, 0);

    delete[] w_buffer;
    w_buffer = nullptr;
}

void WndBase::SetWndText(const char *text) {
    int text_size = strlen(text) + 1/*null ending*/;
    wchar_t *w_buffer = new wchar_t[text_size] { 0 };

    MultiByteToWideChar(CP_UTF8, 0, text, text_size, w_buffer, text_size);

    int result = SetWindowTextW(this->_hwnd, w_buffer);
    if (!result)
        throw std::string("Can't set text -> Error code: " + std::to_string(GetLastError()));

    delete[] w_buffer;
    w_buffer = nullptr;
}

LONG_PTR WndBase::GetWndStyle() {
    return GetWindowLongPtrW(this->_hwnd, GWL_STYLE);
}

void WndBase::SetWndStyle(const LONG_PTR &params) {
    LONG_PTR result = SetWindowLongPtrW(this->_hwnd, GWL_STYLE, params);
    if (!result)
        throw std::string("Can't set window style -> Error code: " + std::to_string(GetLastError()));

    SetWindowPos(this->_hwnd, NULL, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

    UpdateWindow(_hwnd);
}

WndBase *WndBase::GetWndParent() {
    return _parent_wnd;
}

void WndBase::SetWndParent(WndBase *wnd) {
    if (wnd) {
        LONG_PTR old_style = GetWindowLongPtrW(this->_hwnd, GWL_STYLE);
        SetWindowLongPtrW(this->_hwnd, GWL_STYLE, old_style & ~WS_POPUP | WS_CHILD);
        SetWindowPos(this->_hwnd, NULL, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
    }
    else {/* wnd == NULL */
        LONG_PTR old_style = GetWindowLongPtrW(this->_hwnd, GWL_STYLE);
        SetWindowLongPtrW(this->_hwnd, GWL_STYLE, old_style & ~WS_CHILD | WS_POPUP);
        SetWindowPos(this->_hwnd, NULL, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
    }

    this->_parent_wnd = wnd;
    HWND result = SetParent(this->_hwnd, wnd->GetHwnd());
    UpdateWindow(this->_hwnd);
    if (!result)
        throw std::string("Can't set parent window -> Error code: " + std::to_string(GetLastError()));
}

WndPairValue WndBase::GetWndPos() {
    return _pos;
}

void WndBase::SetWndPos(const WndPairValue &pos) {
    _pos = pos;
    int result = SetWindowPos(this->_hwnd, NULL, _pos.first, _pos.second, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOSIZE | SWP_NOZORDER);
    UpdateWindow(_hwnd);
    if (!result)
        throw std::string("Can't set window position -> Error code: " + std::to_string(GetLastError()));
}

WndPairValue WndBase::GetWndSize() {
    return _size;
}

void WndBase::SetWndSize(const WndPairValue &size) {
    _size = size;
    int result = SetWindowPos(this->_hwnd, NULL, 0, 0, _size.first, _size.second, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOZORDER);
    UpdateWindow(_hwnd);
    if (!result)
        throw std::string("Can't set window size -> Error code: " + std::to_string(GetLastError()));
}

void WndBase::SetWndOrderZ(const HWND &hwnd) {
    int result = SetWindowPos(this->_hwnd, hwnd, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE);
    UpdateWindow(_hwnd);
    if (!result)
        throw std::string("Can't set window Z-order -> Error code: " + std::to_string(GetLastError()));
}
