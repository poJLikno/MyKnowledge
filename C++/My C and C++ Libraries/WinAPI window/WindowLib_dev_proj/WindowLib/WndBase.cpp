#include "WndBase.h"

WndBase::~WndBase() {
    _some_data = nullptr;
}

void **WndBase::SomeDataPtr() {
    return &_some_data;
}

void WndBase::ShowWnd(const bool &flag) {
    _is_visible = flag;
    ShowWindow(this->_hwnd, (flag ? SW_SHOWNORMAL : SW_HIDE));
    if (flag) UpdateWindow(this->_hwnd);
}

LRESULT WndBase::SendMsg(const UINT &msg, const WPARAM &wparam, const LPARAM &lparam) {
    return SendMessage(this->_hwnd, msg, wparam, lparam);
}

HWND WndBase::GetHwnd() {
    return this->_hwnd;
}

void WndBase::GetWndText(wchar_t *buffer, const size_t &count) {
    int result = GetWindowText(this->_hwnd, buffer, (int)count);
    if (!result)
        throw std::wstring(L"Can't get text -> Error code: " + std::to_wstring(GetLastError()));
}

void WndBase::SetWndText(const wchar_t *text) {
    int result = SetWindowText(this->_hwnd, text);
    if (!result)
        throw std::wstring(L"Can't set text -> Error code: " + std::to_wstring(GetLastError()));
}

LONG_PTR WndBase::GetWndStyle() {
    return GetWindowLongPtr(this->_hwnd, GWL_STYLE);
}

void WndBase::SetWndStyle(const LONG_PTR &params) {
    LONG_PTR result = SetWindowLongPtr(this->_hwnd, GWL_STYLE, params);
    if (!result)
        throw std::wstring(L"Can't set window style -> Error code: " + std::to_wstring(GetLastError()));

    SetWindowPos(this->_hwnd, NULL, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

    UpdateWindow(_hwnd);
}

HWND WndBase::GetWndParent() {
    return GetParent(this->_hwnd);
}

void WndBase::SetWndParent(const HWND &hwnd) {
    if (hwnd) {
        LONG_PTR old_style = GetWindowLongPtr(this->_hwnd, GWL_STYLE);
        SetWindowLongPtr(this->_hwnd, GWL_STYLE, old_style & ~WS_POPUP | WS_CHILD);
        SetWindowPos(this->_hwnd, NULL, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
    }
    else if (!hwnd) {
        LONG_PTR old_style = GetWindowLongPtr(this->_hwnd, GWL_STYLE);
        SetWindowLongPtr(this->_hwnd, GWL_STYLE, old_style & ~WS_CHILD | WS_POPUP);
        SetWindowPos(this->_hwnd, NULL, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
    }

    HWND result = SetParent(this->_hwnd, hwnd);
    UpdateWindow(_hwnd);
    if (!result)
        throw std::wstring(L"Can't set parent window -> Error code: " + std::to_wstring(GetLastError()));
}

WndPairValue WndBase::GetWndPos() {
    return _pos;
}

void WndBase::SetWndPos(const WndPairValue &pos) {
    _pos = pos;
    int result = SetWindowPos(this->_hwnd, NULL, _pos.first, _pos.second, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOSIZE | SWP_NOZORDER);
    UpdateWindow(_hwnd);
    if (!result)
        throw std::wstring(L"Can't set window position -> Error code: " + std::to_wstring(GetLastError()));
}

WndPairValue WndBase::GetWndSize() {
    return _size;
}

void WndBase::SetWndSize(const WndPairValue &size) {
    _size = size;
    int result = SetWindowPos(this->_hwnd, NULL, 0, 0, _size.first, _size.second, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOZORDER);
    UpdateWindow(_hwnd);
    if (!result)
        throw std::wstring(L"Can't set window size -> Error code: " + std::to_wstring(GetLastError()));
}

void WndBase::SetWndOrderZ(const HWND &hwnd) {
    int result = SetWindowPos(this->_hwnd, hwnd, 0, 0, 0, 0, (_is_visible ? SWP_SHOWWINDOW : 0) | SWP_NOMOVE | SWP_NOSIZE);
    UpdateWindow(_hwnd);
    if (!result)
        throw std::wstring(L"Can't set window Z-order -> Error code: " + std::to_wstring(GetLastError()));
}
