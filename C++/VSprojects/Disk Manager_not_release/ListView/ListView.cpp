#include "ListView.h"

ListView::ListView(HWND hWnd, int x, int y, int width, int height, DWORD style)
{
    INITCOMMONCONTROLSEX icex = { 0 };
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    this->hWnd = CreateWindow(WC_LISTVIEW,
        NULL,
        style,//LVS_EDITLABELS,
        x, y,
        width, height,
        hWnd,
        NULL,
        NULL,
        NULL);
    if (!this->hWnd)
    {
        throw std::runtime_error("Can't create list view control");
    }

    memset(&list_view_column, NULL, sizeof(list_view_column));                  // Zero Members
    {
        list_view_column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;    // Type of mask
    }

    memset(&list_view_item, NULL, sizeof(list_view_item)); // Zero struct's Members
    {
        list_view_item.mask = LVIF_TEXT;   // Text Style
        list_view_item.cchTextMax = 256; // Max size of text
    }
}

void ListView::SetStyle()
{
    ListView_SetExtendedListViewStyle(this->hWnd, LVS_EX_FULLROWSELECT);
}

void ListView::SetColumnWidth(int width)
{
    list_view_column.cx = width;
}

void ListView::AddColumn(char *text, int column_number)
{
    list_view_column.pszText = text;
    ListView_InsertColumn(this->hWnd, column_number, (LPARAM)&list_view_column);
}

void ListView::DeleteColumn(int column_number)
{
    ListView_DeleteColumn(this->hWnd, column_number);
}

void ListView::AddItem(int item_number)
{
    list_view_item.iItem = item_number;
    list_view_item.iSubItem = 0;
    list_view_item.pszText = NULL;
    ListView_InsertItem(this->hWnd, (LPARAM)&list_view_item);
}

int ListView::GetSelectedItem()
{
    return ListView_GetSelectionMark(this->hWnd);
}

void ListView::DeleteItem(int item_number)
{
    ListView_DeleteItem(this->hWnd, item_number);
}

void ListView::SetText(char *text, int item_number, int subitem_number)
{
    list_view_item.iItem = item_number;
    list_view_item.iSubItem = subitem_number;
    list_view_item.pszText = text;
    ListView_SetItem(this->hWnd, (LPARAM)&list_view_item);
}

void ListView::GetText(int item_number, int column_number, char *buffer, int size)
{
    ListView_GetItemText(this->hWnd, item_number, column_number, buffer, size)
}