#include "ComboBox.h"

ComboBox::ComboBox(HWND hWnd, int x, int y, int width, int height, DWORD style)
{
	this->hWnd = CreateWindow("combobox", "", style, x, y, width, height, hWnd, NULL, NULL, NULL);
	if (!this->hWnd)
		throw std::runtime_error("Can't create combo box");
}

void ComboBox::AddItem(const char *item)
{
	SendMessage(this->hWnd, CB_ADDSTRING, 0, (LPARAM)item);
}

void ComboBox::SelectItem(int id)
{
	SendMessage(this->hWnd, CB_SETCURSEL, (WPARAM)id, 0);
}

int ComboBox::GetItemId()
{
	return (int)SendMessage(this->hWnd, CB_GETCURSEL, 0, 0);
}

void ComboBox::GetItem(char *buffer)
{
	SendMessage(this->hWnd, CB_GETLBTEXT, (WPARAM)GetItemId(), (LPARAM)buffer);
}
