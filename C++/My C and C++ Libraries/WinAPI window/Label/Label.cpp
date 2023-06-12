#include "Label.h"

Label::Label(HWND hWnd, const char *text, int x, int y, int width, int height, DWORD style)
{
	this->hWnd = CreateWindow("static", text, style, x, y, width, height, hWnd, NULL, NULL, NULL);
	if (!this->hWnd)
		throw std::runtime_error("Can't create label");
}

void Label::SetText(const char *text)
{
	SetWindowText(this->hWnd, text);
}

void Label::GetText(char *buffer, size_t size)
{
	GetWindowText(this->hWnd, buffer, (int)size);
}