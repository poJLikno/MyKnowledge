#include "Window.h"

#include <functional>

WndList<Window> Window::_wnd_list;
WndList<WndPairValue> Window::_wnd_pos_list;
WndList<WndPairValue> Window::_wnd_size_list;

template<class T>
static void ParentResizeCallbacksCaller(T &ctrls_list, ParentResizeCallbackParams *params);

template<class T>
static void MainCallbacksCaller(T &ctrls_list, LPARAM &lParam, bool &ctrl_was_found_flag);

static bool MenuMainCallbacksCaller(MenuBase *menu, WPARAM &wParam, bool &ctrl_was_found_flag);

LRESULT Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	try {
		// Check windows
		Window *Wnd = nullptr;
		WndPairValue *WndPos = nullptr;
		WndPairValue *WndSize = nullptr;
		for (int i = 0; i < _wnd_list.GetCount(); ++i) {
			if (hwnd == _wnd_list[i]->GetHwnd()) {
				Wnd = _wnd_list[i];
				WndPos = _wnd_pos_list[i];
				WndSize = _wnd_size_list[i];
				break;
			}
		}
		if (!Wnd) return DefWindowProcW(hwnd, uMsg, wParam, lParam);

		if (uMsg == WM_CREATE) {
			result = 1;
		}
		else {
			/*if (uMsg == WM_KEYDOWN) {
				if (wParam == VK_ESCAPE) DestroyWindow(hwnd);
				result = 0;
			}*/
			/*if (uMsg == WM_GETMINMAXINFO)
			{
				LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
				lpMMI->ptMinTrackSize.x = 752 + 16;// 16 * 47 +...
				lpMMI->ptMinTrackSize.y = 301 + 59;//423 + 59;// 9 * 47 +...
			}*/
			if (uMsg == WM_CTLCOLORSTATIC) {// !!! For transparent "Label" !!!
				SetBkMode((HDC)wParam, TRANSPARENT);
				result = 0;
			}
			else if (uMsg == WM_MOVE) {
				WndPos->first = LOWORD(lParam);
				WndPos->second = HIWORD(lParam);
				result = 0;
			}
			else if (uMsg == WM_SIZE) {
				ParentResizeCallbackParams params = { nullptr, *WndSize };
				WndSize->first = LOWORD(lParam);
				WndSize->second = HIWORD(lParam);

				// Run parent resize controls callbacks
				ParentResizeCallbacksCaller(Wnd->GetButtonsList(), &params);
				ParentResizeCallbacksCaller(Wnd->GetComboBoxesList(), &params);
				ParentResizeCallbacksCaller(Wnd->GetEditsList(), &params);
				ParentResizeCallbacksCaller(Wnd->GetLabelsList(), &params);

				UpdateWindow(hwnd);

				result = 0;
			}
			else if (uMsg == WM_COMMAND) {
				bool ctrl_was_found_flag = false;				

				// Run main controls callbacks
				MainCallbacksCaller(Wnd->GetButtonsList(), lParam, ctrl_was_found_flag);

				if (HIWORD(wParam) == CBN_SELCHANGE)
					MainCallbacksCaller(Wnd->GetComboBoxesList(), lParam, ctrl_was_found_flag);
				else if (HIWORD(wParam) == EN_UPDATE)
					MainCallbacksCaller(Wnd->GetEditsList(), lParam, ctrl_was_found_flag);
				/*else if (HIWORD(wParam) == EN_CHANGE) { // Also edit message
					std::wcout << L"EN_CHANGE\r\n";
				}*/

				// Run menu points main callbacks
				MenuMainCallbacksCaller(Wnd->_menu, wParam, ctrl_was_found_flag);

				result = 0;
			}
			else if (uMsg == WM_CLOSE) {
				DestroyWindow(hwnd);
				result = 0;
			}
			else if (uMsg == WM_DESTROY) {
				PostQuitMessage(0);
				result = 1;
			}
			else result = DefWindowProcW(hwnd, uMsg, wParam, lParam);
		}
	}
	catch (std::string &e) {
		int str_size = (int)e.length() + 1;
		wchar_t *w_error = new wchar_t[str_size] { 0 };
		MultiByteToWideChar(CP_UTF8, 0, e.c_str(), str_size, w_error, str_size);

		MessageBoxW(NULL, w_error, L"Error", MB_OK);
		DestroyWindow(hwnd);
		result = 0;

		delete[] w_error;
		w_error = nullptr;
	}

	return result;
}

template<class T>
static void ParentResizeCallbacksCaller(T &ctrls_list, ParentResizeCallbackParams *params) {
	for (int i = 0; i < ctrls_list.GetCount(); ++i) {
		auto *ctrl = ctrls_list[i];
		params->wnd = ctrl;
		ctrl->operator()("ParentResizeCallback", params);
	}
}

template<class T>
static void MainCallbacksCaller(T &ctrls_list, LPARAM &lParam, bool &ctrl_was_found_flag) {
	if (ctrl_was_found_flag) return;
	for (int i = 0; i < ctrls_list.GetCount(); ++i) {
		auto *ctrl = ctrls_list[i];
		if (lParam == (LPARAM)ctrl->GetHwnd()) {
			ctrl->operator()("MainCallback", ctrl);
			ctrl_was_found_flag = true;
			break;
		}
	}
}

static bool MenuMainCallbacksCaller(MenuBase *menu, WPARAM &wParam, bool &ctrl_was_found_flag) {
	if (ctrl_was_found_flag || menu == nullptr) return false;
	for (int i = 0; i < menu->GetMenuPointsList().GetCount(); ++i) {
		MenuPoint *menu_point = menu->GetMenuPointsList()[i];
		if (LOWORD(wParam) == menu_point->GetId()) {
			menu_point->operator()("MainCallback", menu_point);
			ctrl_was_found_flag = true;
			return true;
		}
	}
	for (int i = 0; i < menu->GetPopupMenusList().GetCount(); ++i) {
		MenuBase *popup_menu = menu->GetPopupMenusList()[i];
		if (popup_menu)
			if (MenuMainCallbacksCaller(popup_menu, wParam, ctrl_was_found_flag)) break;
	}
	return false;
}
