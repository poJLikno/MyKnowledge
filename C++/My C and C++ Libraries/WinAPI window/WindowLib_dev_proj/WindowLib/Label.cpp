#include "Label.h"

Label::Label(const wchar_t *text, WndPairValue pos, WndPairValue size)
	: WndBase(pos, size), CallbackWindow(1) {
	_hwnd = CreateWindow(L"static", text, WS_VISIBLE | WS_POPUP,
		_pos.first, _pos.second, _size.first, _size.second,
		NULL/*hWnd*/, NULL, NULL, NULL);
	if (!_hwnd)
		throw std::wstring(L"Can't create label -> Error code: " + std::to_wstring(GetLastError()));
}
