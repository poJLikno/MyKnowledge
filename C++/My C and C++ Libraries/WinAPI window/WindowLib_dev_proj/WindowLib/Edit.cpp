#include "Edit.h"

Edit::Edit(WndPairValue pos, WndPairValue size)
	: WndBase(pos, size) {}

void Edit::SetWndParent(WndBase *wnd) {
	this->_parent_wnd = wnd;
	_hwnd = CreateWindowExW(0L, L"edit", NULL, WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | WS_BORDER | WS_CHILD | WS_TABSTOP,
		_pos.first, _pos.second,
		_size.first, _size.second,
		wnd->GetHwnd(), NULL, NULL, NULL);
	if (!_hwnd)
		throw std::string("Can't create edit -> Error code: " + std::to_string(GetLastError()));
}
