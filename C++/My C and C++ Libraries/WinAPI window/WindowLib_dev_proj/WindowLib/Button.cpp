#include "Button.h"

Button::Button(const wchar_t *text, WndPairValue pos, WndPairValue size)
	: WndBase(pos, size), CallbackWindow(2) {
	_hwnd = CreateWindow(L"button", text, WS_VISIBLE | WS_POPUP | WS_TABSTOP,
		_pos.first, _pos.second,
		_size.first, _size.second,
		NULL/*hWnd*/, NULL, NULL, NULL);
	if (!_hwnd)
		throw std::wstring(L"Can't create button -> Error code: " + std::to_wstring(GetLastError()));
}
