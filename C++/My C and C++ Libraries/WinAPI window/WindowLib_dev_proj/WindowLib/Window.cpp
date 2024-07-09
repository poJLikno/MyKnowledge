#include "Window.h"

#include <thread>
#include <chrono>

Window::Window(const char *name, WndPairValue pos, WndPairValue size, int icon_id)
	: WndBase(pos, size) {
	// Register window class
	//_class_name = std::string(name + std::string("_class"));
	int class_name_size = (int)strlen(name) + 1/*null ending*/ + 6/*_class*/;
	_w_class_name = new wchar_t[class_name_size] { 0 };
	wchar_t *w_name = new wchar_t[strlen(name) + 1] { 0 };

	/* Transform name */
	MultiByteToWideChar(CP_UTF8, 0, name, (int)strlen(name) + 1, w_name, (int)strlen(name) + 1);

	/* Transform class_name */
	MultiByteToWideChar(CP_UTF8, 0, std::string(name + std::string("_class")).c_str(), class_name_size, _w_class_name, class_name_size);

	WNDCLASSW wc = { 0 };
	{
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_PARENTDC;
		wc.lpfnWndProc = Window::WndProc;
		wc.cbClsExtra = 0;// 1 - Reserve for ability change WndProc
		wc.cbWndExtra = sizeof(LONG_PTR);
		wc.hInstance = HINST_THISCOMPONENT;
		wc.hIcon = icon_id ? LoadIconW(HINST_THISCOMPONENT, MAKEINTRESOURCEW(icon_id)) : LoadIconW(NULL, (LPWSTR)IDI_APPLICATION);
		wc.hCursor = LoadCursorW(NULL, (LPWSTR)IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//NULL
		wc.lpszMenuName = NULL;
		wc.lpszClassName = _w_class_name;
	}
	if (!RegisterClassW(&wc))
		throw std::string("Can't register class -> Error code: " + std::to_string(GetLastError()));
	
	// Create window
	this->_hwnd = CreateWindowExW(0L, wc.lpszClassName, w_name, WS_OVERLAPPEDWINDOW,
		_pos.first, _pos.second, _size.first, _size.second,
		NULL, NULL, NULL, NULL);
	if (!this->_hwnd)
		throw std::string("Can't create window -> Error code: " + std::to_string(GetLastError()));

	//ShowWindow(this->hWnd, SW_SHOWNORMAL);
	_wnd_list.Append(this);
	_wnd_pos_list.Append(&_pos);
	_wnd_size_list.Append(&_size);

	/* Clean up */
	delete[] w_name;
	w_name = nullptr;

	//Create font
	/*NONCLIENTMETRICSA ncm = { 0 };
	SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
	_normal_font = CreateFontIndirectA(&ncm.lfMessageFont);*/
}

Window::~Window() {
	//DeleteObject((HGDIOBJ)_normal_font);

	if (!UnregisterClassW(_w_class_name, HINST_THISCOMPONENT))
		MessageBoxW(NULL, std::wstring(L"Can't unregister class -> Error code: " + std::to_wstring(GetLastError())).c_str(), L"Error", MB_OK);

	delete[] _w_class_name;
	_w_class_name = nullptr;
}

void Window::AttachChildControl(WndBase *wnd) {
	if (dynamic_cast<Button *>(wnd)) {
		_btns_list.Append(dynamic_cast<Button *>(wnd));
		wnd->SetWndParent(this);
	}
	else if (dynamic_cast<ComboBox *>(wnd)) {
		_cmb_bxs_list.Append(dynamic_cast<ComboBox *>(wnd));
		wnd->SetWndParent(this);
	}
	else if (dynamic_cast<Edit *>(wnd)) {
		_edits_list.Append(dynamic_cast<Edit *>(wnd));
		wnd->SetWndParent(this);
	}
	else if (dynamic_cast<Label *>(wnd)) {
		_lbls_list.Append(dynamic_cast<Label *>(wnd));
		wnd->SetWndParent(this);
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
		if (HasCallback("AsyncLoopCallback")) {
			while (true) {
				if (PeekMessageW(&_msg, NULL, 0, 0, PM_REMOVE)) {
					if (_msg.message == WM_QUIT) break;
					else if (_ctrls_dlg_msg_flag) {
						if (!IsDialogMessageW(_hwnd, &_msg)/* -- VK_KEY's messages won't be delivered to main window -- */) {
							TranslateMessage(&_msg);
							DispatchMessageW(&_msg);
						}
					}
					else {
						TranslateMessage(&_msg);
						DispatchMessageW(&_msg);
					}
				}
				else {
					this->operator()("AsyncLoopCallback", this);
				}
				//Sleep(1);
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
		}
		else {
			while (GetMessageW(&_msg, NULL, 0, 0)) {
				if (_ctrls_dlg_msg_flag) {
					if (!IsDialogMessageW(_hwnd, &_msg)/* -- VK_KEY's messages won't be delivered to main window -- */) {
						TranslateMessage(&_msg);
						DispatchMessageW(&_msg);
					}
				}
				else {
					TranslateMessage(&_msg);
					DispatchMessageW(&_msg);
				}
				//Sleep(1);
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
		}
	}
	catch (const std::string &e) {
		int str_size = (int)e.length() + 1;
		wchar_t *w_error = new wchar_t[str_size] { 0 };
		MultiByteToWideChar(CP_UTF8, 0, e.c_str(), str_size, w_error, str_size);

		MessageBoxW(NULL, w_error, L"Error", MB_OK);
		DestroyWindow(_hwnd);

		delete[] w_error;
		w_error = nullptr;
	}

	return static_cast<int>(_msg.wParam);
}
