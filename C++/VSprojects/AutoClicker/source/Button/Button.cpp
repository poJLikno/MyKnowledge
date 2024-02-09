#include "Button.h"

Button::Button(HWND hWnd, const char *text, int x, int y, int width, int height, DWORD style)
{
	this->hWnd = CreateWindow("button", text, style, x, y, width, height, hWnd, NULL, NULL, NULL);
	if (!this->hWnd)
		throw std::runtime_error("Can't create button");
}

void Button::SetText(const char *text)
{
	SetWindowText(this->hWnd, text);
}

void Button::GetText(char *buffer, size_t size)
{
	GetWindowText(this->hWnd, buffer, (int)size);
}