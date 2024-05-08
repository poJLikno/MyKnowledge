#include "Window.h"

#include <functional>

WndList<Window> Window::_wnd_list;
WndList<WndPairValue> Window::_wnd_pos_list;
WndList<WndPairValue> Window::_wnd_size_list;

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
		if (!Wnd) return DefWindowProc(hwnd, uMsg, wParam, lParam);

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
				WndSizeParams params(*Wnd, *WndSize);
				WndSize->first = LOWORD(lParam);
				WndSize->second = HIWORD(lParam);

				// On size changing callbacks referense
				auto _SizeChangeCallbacks = [&params](auto &ctrls_list)->void {
						for (int i = 0; i < ctrls_list.GetCount(); ++i) {
							auto *ctrl = ctrls_list[i];

							params._data = ctrl->SomeDataPtr();
							*ctrl->SomeDataPtr() = &params;
							ctrl->RunCallback(0);
							*ctrl->SomeDataPtr() = *params._data;
							params._data = nullptr;
						}
					};

				// Run controls callbacks
				_SizeChangeCallbacks(Wnd->GetButtonsList());
				_SizeChangeCallbacks(Wnd->GetComboBoxesList());
				_SizeChangeCallbacks(Wnd->GetEditsList());
				_SizeChangeCallbacks(Wnd->GetLabelsList());

				UpdateWindow(hwnd);

				result = 0;
			}
			else if (uMsg == WM_COMMAND) {
				bool ctrl_was_found_flag = false;

				// Main controls callbacks reference
				auto _MainControlsCallbacks = [&ctrl_was_found_flag, &lParam](auto &ctrls_list)->void {
					if (ctrl_was_found_flag) return;
					for (int i = 0; i < ctrls_list.GetCount(); ++i) {
						auto *ctrl = ctrls_list[i];
						if (lParam == (LPARAM)ctrl->GetHwnd()) {
							ctrl->RunCallback(1);
							ctrl_was_found_flag = true;
							break;
						}
					}
					};

				std::function<bool(MenuBase &)> _MenuPointsCallbacks = [&_MenuPointsCallbacks, &wParam](MenuBase &menu)->bool {
					for (int i = 0; i < menu.GetMenuPointsList().GetCount(); ++i) {
						MenuPoint *menu_point = menu.GetMenuPointsList()[i];
						if (LOWORD(wParam) == menu_point->GetId()) {
							menu_point->RunCallback(0);
							return true;
						}
					}
					for (int i = 0; i < menu.GetPopupMenusList().GetCount(); ++i) {
						MenuBase *popup_menu = menu.GetPopupMenusList()[i];
						if (popup_menu)
							if (_MenuPointsCallbacks(*popup_menu)) break;
					}
					return false;
					};

				// Run controls callbacks
				{
					_MainControlsCallbacks(Wnd->GetButtonsList());

					if (HIWORD(wParam) == CBN_SELCHANGE)
						_MainControlsCallbacks(Wnd->GetComboBoxesList());
					else if (HIWORD(wParam) == EN_UPDATE)
						_MainControlsCallbacks(Wnd->GetEditsList());
					/*else if (HIWORD(wParam) == EN_CHANGE) { // Also edit message
						std::wcout << L"EN_CHANGE\r\n";
					}*/
				}

				// Run menu points callbacks
				if (Wnd->_menu)
				{
					_MenuPointsCallbacks(*Wnd->_menu);
				}

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
			else result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	catch (std::wstring &e) {
		MessageBox(NULL, e.c_str(), L"Error", MB_OK);
		DestroyWindow(hwnd);
		result = 0;
	}

	return result;
}
