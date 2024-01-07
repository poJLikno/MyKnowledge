#include "Window.h"
#include "../ListView/ListView.h"

#define ID_DELETE_VOLUME 1
#define ID_DELETE_PARTITION 2
#define ID_EXIT 3

ListView *list_view;
HMENU hPopupMenu;
HMENU hDeleteMenu;

void InitWindowControls(HWND hWnd);

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        InitWindowControls(hWnd);

        result = 1;
    }
    else
    {
        if (message == WM_CONTEXTMENU)
        {
            if (wParam == (WPARAM)list_view->hWnd)
            {
                if (list_view->GetSelectedItem() == 0)
                {
                    HMENU hPopupMenu = CreatePopupMenu();
                    AppendMenu(hPopupMenu, MF_STRING, NULL, "Format");
                    AppendMenu(hPopupMenu, MF_SEPARATOR, NULL, NULL);
                    AppendMenu(hPopupMenu, MF_STRING, ID_EXIT, "Exit");
                    TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), NULL, hWnd, NULL);
                }
                else if (list_view->GetSelectedItem() == 1)
                {
                    hPopupMenu = CreatePopupMenu();
                    {
                        hDeleteMenu = CreatePopupMenu();
                        {
                            AppendMenu(hDeleteMenu, MF_STRING, ID_DELETE_VOLUME, "Volume");
                            AppendMenu(hDeleteMenu, MF_STRING, ID_DELETE_PARTITION, "Partition");
                        }

                        AppendMenu(hPopupMenu, MF_POPUP, (UINT_PTR)hDeleteMenu, "Delete");
                        AppendMenu(hPopupMenu, MF_SEPARATOR, NULL, NULL);
                        AppendMenu(hPopupMenu, MF_STRING, ID_EXIT, "Exit");
                    }
                    TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), NULL, hWnd, NULL);
                }
                else
                {
                    HMENU hPopupMenu = CreatePopupMenu();
                    AppendMenu(hPopupMenu, MF_STRING, NULL, "Exit");
                    TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), NULL, hWnd, NULL);
                }
            }

            result = 0;
        }
        else if (message == WM_COMMAND)
        {
            if (LOWORD(wParam) == ID_DELETE_VOLUME)
            {
                MessageBeep(MB_OK);
            }
            else if (LOWORD(wParam) == ID_DELETE_PARTITION)
            {
                MessageBox(NULL, "Partition has been deleted successeful.", "Message", MB_OK);
            }
            else if (LOWORD(wParam) == ID_EXIT)
            {
                SendMessage(hWnd, WM_CLOSE, NULL, NULL);
            }

            result = 0;
        }
        else if (message == WM_KEYDOWN)
        {
            if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
            result = 0;
        }
        else if (message == WM_CLOSE)
        {
            DestroyWindow(hWnd);
            result = 0;
        }
        else if (message == WM_DESTROY)
        {
            delete list_view;

            PostQuitMessage(0);
            result = 1;
        }
        else result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return result;
}

void InitWindowControls(HWND hWnd)
{
    list_view = new ListView(hWnd, 0, 0, 700, 300);

    list_view->SetStyle();
    list_view->SetColumnWidth(80);

    list_view->AddColumn((char *)"Volume ###", 0);
    list_view->AddColumn((char *)"Letter", 1);
    list_view->AddColumn((char *)"Label", 2);
    list_view->AddColumn((char *)"File system", 3);
    list_view->AddColumn((char *)"Type", 4);
    list_view->AddColumn((char *)"Size", 5);
    list_view->AddColumn((char *)"Status", 6);
    list_view->AddColumn((char *)"Info", 7);

    list_view->AddItem(0);
    {
        list_view->SetText((char *)"Volume 0", 0, 0);
        list_view->SetText((char *)"C", 0, 1);
        list_view->SetText((char *)"New volume", 0, 2);
        list_view->SetText((char *)"NTFS", 0, 3);
        list_view->SetText((char *)"Partition", 0, 4);
        list_view->SetText((char *)"917 GB", 0, 5);
        list_view->SetText((char *)"Healthy", 0, 6);
        list_view->SetText((char *)"Boot", 0, 7);
    }

    list_view->AddItem(1);
    {
        list_view->SetText((char *)"Volume 1", 1, 0);
        list_view->SetText((char *)"D", 1, 1);
        list_view->SetText((char *)"Drivers", 1, 2);
        list_view->SetText((char *)"NTFS", 1, 3);
        list_view->SetText((char *)"Partition", 1, 4);
        list_view->SetText((char *)"5 GB", 1, 5);
        list_view->SetText((char *)"Healthy", 1, 6);
        list_view->SetText((char *)"", 1, 7);
    }

    // ----------- Not Wrong --------------
    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();
    {
        AppendMenu(hSubMenu, MF_STRING, 24, "Delete");
        AppendMenu(hSubMenu, MF_STRING, 25, "Flag");
    }
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Aboba");
    CheckMenuItem(hMenu, 24, MF_CHECKED/*MF_UNCHECKED*/);
    EnableMenuItem(hMenu, 25, MF_DISABLED);

    SetMenu(hWnd, hMenu);
    // --------------------------------
}