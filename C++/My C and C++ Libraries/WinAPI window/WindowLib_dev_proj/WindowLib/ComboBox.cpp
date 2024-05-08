#include "ComboBox.h"

ComboBox::ComboBox(WndPairValue pos, WndPairValue size)
	: WndBase(pos, size), CallbackWindow(2) {}

void ComboBox::SetWndParent(const HWND &hwnd) {
	_hwnd = CreateWindow(L"combobox", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_TABSTOP,
		_pos.first, _pos.second,
		_size.first, _size.second,
		hwnd/*parent hwnd*/, NULL, NULL, NULL);
	if (!_hwnd)
		throw std::wstring(L"Can't create combobox -> Error code: " + std::to_wstring(GetLastError()));
}

void ComboBox::AddItem(const wchar_t *text) {
	SendMsg(CB_ADDSTRING, NULL, (LPARAM)text);
	//SendMessage(_hwnd, CB_ADDSTRING, 0, (LPARAM)text);
	
}

void ComboBox::SelectItem(const int &id) {
	SendMsg(CB_SETCURSEL, (WPARAM)id, NULL);
	//SendMessage(_hwnd, CB_SETCURSEL, (WPARAM)id, 0);
}

int ComboBox::GetItemId() {
	return (int)SendMsg(CB_GETCURSEL, NULL, NULL);
	//return (int)SendMessage(_hwnd, CB_GETCURSEL, 0, 0);
}

void ComboBox::GetItem(wchar_t *buffer) {
	SendMsg(CB_GETLBTEXT, (WPARAM)GetItemId(), (LPARAM)buffer);
	//SendMessage(_hwnd, CB_GETLBTEXT, (WPARAM)GetItemId(), (LPARAM)buffer);
}

void ComboBox::GetOldItem(wchar_t *buffer, int buffer_size) {
	GetWindowText(_hwnd, buffer, buffer_size);
}
