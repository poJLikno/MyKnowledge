#include "Edit.h"

Edit::Edit(WndPairValue pos, WndPairValue size)
	: WndBase(pos, size), CallbackWindow(2) {}

void Edit::SetWndParent(const HWND &hwnd) {
	_hwnd = CreateWindow(L"edit", NULL, WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | WS_BORDER | WS_CHILD | WS_TABSTOP,
		_pos.first, _pos.second,
		_size.first, _size.second,
		hwnd/*parent hwnd*/, NULL, NULL, NULL);
	if (!_hwnd)
		throw std::wstring(L"Can't create edit -> Error code: " + std::to_wstring(GetLastError()));
}
