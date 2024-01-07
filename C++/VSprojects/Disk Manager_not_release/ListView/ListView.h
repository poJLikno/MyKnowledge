#ifndef LIST_VIEW_H
#define LIST_VIEW_H

#include <iostream>
#include <Windows.h>
#include <CommCtrl.h>

#pragma comment(lib,"Comctl32.lib")

class ListView
{
private:
	LVCOLUMN list_view_column = { 0 };
	LVITEM list_view_item = { 0 };

public:
	HWND hWnd = { 0 };

	ListView(HWND hWnd, int x, int y, int width, int height, DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT);

	void SetStyle();

	void SetColumnWidth(int width);

	void AddColumn(char *text, int number);

	void DeleteColumn(int column_number);

	void AddItem(int item_number);

	int GetSelectedItem();

	void DeleteItem(int item_number);

	void SetText(char *text, int item_number, int subitem_number);

	void GetText(int item_number, int column_number, char *buffer, int size);
};

#endif