#include "ComboBox.h"

ComboBox::ComboBox(WndPairValue pos, WndPairValue size)
	: WndBase(pos, size) {}

void ComboBox::SetWndParent(WndBase *wnd) {
	this->_parent_wnd = wnd;
	_hwnd = CreateWindowExW(0L, L"combobox", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_TABSTOP,
		_pos.first, _pos.second,
		_size.first, _size.second,
		wnd->GetHwnd(), NULL, NULL, NULL);
	if (!_hwnd)
		throw std::string("Can't create combobox -> Error code: " + std::to_string(GetLastError()));
}

void ComboBox::AddItem(const char *text) {
	int text_size = (int)strlen(text) + 1;
	wchar_t *w_text = new wchar_t[text_size] { 0 };
	MultiByteToWideChar(CP_UTF8, 0, text, text_size, w_text, text_size);

	SendMsg(CB_ADDSTRING, NULL, (LPARAM)w_text);
	//SendMessage(_hwnd, CB_ADDSTRING, 0, (LPARAM)text);

	delete[] w_text;
	w_text = nullptr;
}

void ComboBox::SelectItem(const int &id) {
	SendMsg(CB_SETCURSEL, (WPARAM)id, NULL);
	//SendMessage(_hwnd, CB_SETCURSEL, (WPARAM)id, 0);
}

int ComboBox::GetItemId() {
	return (int)SendMsg(CB_GETCURSEL, NULL, NULL);
	//return (int)SendMessage(_hwnd, CB_GETCURSEL, 0, 0);
}

int ComboBox::GetItemLength() {
	return (int)SendMsg(CB_GETLBTEXTLEN, (WPARAM)GetItemId(), NULL);
}

void ComboBox::GetItem(char *buffer, const int &count) {
	wchar_t *w_buffer = new wchar_t[count] { 0 };

	SendMsg(CB_GETLBTEXT, (WPARAM)GetItemId(), (LPARAM)w_buffer);
	//SendMessage(_hwnd, CB_GETLBTEXT, (WPARAM)GetItemId(), (LPARAM)buffer);

	WideCharToMultiByte(CP_UTF8, 0, w_buffer, count, buffer, count, 0, 0);

	delete[] w_buffer;
	w_buffer = nullptr;
}

void ComboBox::GetOldItem(char *buffer, int buffer_size) {
	wchar_t *w_buffer = new wchar_t[buffer_size] { 0 };

	GetWindowTextW(_hwnd, w_buffer, buffer_size);

	WideCharToMultiByte(CP_UTF8, 0, w_buffer, buffer_size, buffer, buffer_size, 0, 0);

	delete[] w_buffer;
	w_buffer = nullptr;
}
