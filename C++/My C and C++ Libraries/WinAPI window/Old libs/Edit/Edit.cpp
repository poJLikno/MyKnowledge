#include "Edit.h"

Edit::Edit(HWND hWnd, int x, int y, int width, int height, DWORD style)
{
	this->hWnd = CreateWindow("edit", "", style, x, y, width, height, hWnd, NULL, NULL, NULL);
	if (!this->hWnd)
		throw std::runtime_error("Can't create edit");
}

void Edit::SetText(const char *text)
{
	SetWindowText(this->hWnd, text);
}

void Edit::GetText(char *buffer, size_t size)
{
	GetWindowText(this->hWnd, buffer, (int)size);
}