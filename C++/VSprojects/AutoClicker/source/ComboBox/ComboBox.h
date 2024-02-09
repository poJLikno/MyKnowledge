#ifndef BOMBO_BOX_H
#define BOMBO_BOX_H

#include <iostream>
#include <Windows.h>

class ComboBox
{
public:
	HWND hWnd = {};

	ComboBox(HWND hWnd, int x, int y, int width, int height, DWORD style = WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST);

	void AddItem(const char *item);

	void SelectItem(int id);

	int GetItemId();

	void GetItem(char *buffer);
};

#endif