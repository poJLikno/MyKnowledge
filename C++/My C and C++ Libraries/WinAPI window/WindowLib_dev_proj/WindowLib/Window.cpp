#include "Window.h"

#include <thread>
#include <chrono>

Window::Window(const wchar_t *name, WndPairValue pos, WndPairValue size, int icon_id)
    : WndBase(pos, size), CallbackWindow(1) {
    // Register window class
    _class_name = std::wstring(name + std::wstring(L"_class"));

    WNDCLASS wc = { 0 };
    {
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_PARENTDC;
        wc.lpfnWndProc = Window::WndProc;
        wc.cbClsExtra = 0;// 1 - Reserve for ability change WndProc
        wc.cbWndExtra = sizeof(LONG_PTR);
        wc.hInstance = HINST_THISCOMPONENT;
        wc.hIcon = icon_id ? LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(icon_id)) : LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//NULL
        wc.lpszMenuName = NULL;
        wc.lpszClassName = _class_name.c_str();
    }
    if (!RegisterClass(&wc))
        throw std::wstring(L"Can't register class -> Error code: " + std::to_wstring(GetLastError()));
    
    // Create window
    this->_hwnd = CreateWindow(wc.lpszClassName, name, WS_OVERLAPPEDWINDOW,
        _pos.first, _pos.second, _size.first, _size.second,
        NULL, NULL, NULL, NULL);
    if (!this->_hwnd)
        throw std::wstring(L"Can't create window -> Error code: " + std::to_wstring(GetLastError()));

    //ShowWindow(this->hWnd, SW_SHOWNORMAL);
    _wnd_list.Append(this);
    _wnd_pos_list.Append(&_pos);
    _wnd_size_list.Append(&_size);

    //Create font
    NONCLIENTMETRICS ncm = { 0 };
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
    _normal_font = CreateFontIndirect(&ncm.lfMessageFont);
}

Window::~Window() {
    DeleteObject((HGDIOBJ)_normal_font);

    if (!UnregisterClass(_class_name.c_str(), HINST_THISCOMPONENT))
        MessageBox(NULL, std::wstring(L"Can't unregister class -> Error code: " + std::to_wstring(GetLastError())).c_str(), L"Error", MB_OK);
}

void Window::AttachChildControl(WndBase *wnd) {
    if (dynamic_cast<Button *>(wnd)) {
        _btns_list.Append(dynamic_cast<Button *>(wnd));
        wnd->SetWndParent(_hwnd);
    }
    else if (dynamic_cast<ComboBox *>(wnd)) {
        _cmb_bxs_list.Append(dynamic_cast<ComboBox *>(wnd));
        wnd->SetWndParent(_hwnd);
    }
    else if (dynamic_cast<Edit *>(wnd)) {
        _edits_list.Append(dynamic_cast<Edit *>(wnd));
        wnd->SetWndParent(_hwnd);
    }
    else if (dynamic_cast<Label *>(wnd)) {
        _lbls_list.Append(dynamic_cast<Label *>(wnd));
        wnd->SetWndParent(_hwnd);
    }
}

void Window::AttachMenu(Menu *menu) {
    _menu = menu;
    menu->SetHParent((void *)_hwnd);
}

WndList<Button> &Window::GetButtonsList() {
    return _btns_list;
}

WndList<ComboBox> &Window::GetComboBoxesList() {
    return _cmb_bxs_list;
}

WndList<Edit> &Window::GetEditsList() {
    return _edits_list;
}

WndList<Label> &Window::GetLabelsList() {
    return _lbls_list;
}

Menu &Window::GetMenu() {
    return *_menu;
}

void Window::EnableControlsDialogMessages(const bool &flag) {
    _ctrls_dlg_msg_flag = flag;
}

int Window::Run() {
    try {
        // Program main loop
        if (_callbacks[0].HasCallback()) {
            while (true) {
                if (PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE)) {
                    if (_msg.message == WM_QUIT) break;
                    else if (_ctrls_dlg_msg_flag) {
                        if (!IsDialogMessage(_hwnd, &_msg)/* -- VK_KEY's messages won't be delivered to main window -- */) {
                            TranslateMessage(&_msg);
                            DispatchMessage(&_msg);
                        }
                    }
                    else {
                        TranslateMessage(&_msg);
                        DispatchMessage(&_msg);
                    }
                }
                else {
                    CallbackWindow::RunCallback(0);
                }
                //Sleep(1);
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        }
        else {
            while (GetMessage(&_msg, NULL, 0, 0)) {
                if (_ctrls_dlg_msg_flag) {
                    if (!IsDialogMessage(_hwnd, &_msg)/* -- VK_KEY's messages won't be delivered to main window -- */) {
                        TranslateMessage(&_msg);
                        DispatchMessage(&_msg);
                    }
                }
                else {
                    TranslateMessage(&_msg);
                    DispatchMessage(&_msg);
                }
                //Sleep(1);
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        }
    }
    catch (const std::wstring &e) {
        MessageBox(NULL, e.c_str(), L"Error", MB_OK);
        DestroyWindow(_hwnd);
    }

    return static_cast<int>(_msg.wParam);
}
