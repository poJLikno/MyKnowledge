#include <iostream>
#include <windows.h>
#include <thread>

#include "WindowLib/Window.h"
#include "WindowLib/NormalFont.h"

int wmain(int argc, const wchar_t *argv) {
	setlocale(LC_ALL, "");
	_wsetlocale(LC_ALL, L"");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Window wnd(L"TestApp", WndPairValue{ CW_USEDEFAULT, CW_USEDEFAULT }, WndPairValue{ 400, 300 });
	wnd.SetWndText(L"Programm");
	wnd.EnableControlsDialogMessages(true);

	unsigned __int8 j = 0;

	/*wnd.SetAsyncWndLoopCallback([&j](void *ptr) {
			Window &wnd_ref = WndCallback::GetCallObject<Window>(ptr);
			wnd_ref.SetWndText(std::to_wstring(j).c_str());
			std::wcout << L"It's work!\r\n";
		});*/

	Button btn(L"First button", WndPairValue{ 100, 100 }, WndPairValue{ 50, 25 });
	Button btn_t(L"Second button", WndPairValue{ 350, 100 }, WndPairValue{ 200, 100 });
	ComboBox cmb_bx(WndPairValue{ 100, 350 }, WndPairValue{ 140, 200 });
	Label lbl(L"govnar_pes", WndPairValue{ 300, 350 }, WndPairValue{ 140, 20 });
	Menu menu;
	Edit edit;

	// Button 1
	btn.SetOnClickCallback([&j](void *ptr) {
			Button &btn_ref = WndCallback::GetCallObject<Button>(ptr);
			btn_ref.SetWndText(std::to_wstring(j++).c_str());
			std::wcout << "Button 1 was pressed!\r\n";
		});
	btn.SetOnResizeCallback([](void *ptr) {
			Button &btn_ref = WndCallback::GetCallObject<Button>(ptr);
			WndSizeParams &params = *(WndSizeParams *)*btn_ref.SomeDataPtr();
			btn_ref.SetWndSize(WndPairValue{ params._wnd.GetWndSize().first / 4, params._wnd.GetWndSize().second / 6 });
		});

	//Button 2
	btn_t.SetOnClickCallback([&j](void *ptr) {
			Button &btn_ref = WndCallback::GetCallObject<Button>(ptr);
			btn_ref.SetWndText(std::to_wstring(-j++).c_str());
			std::wcout << "Button 2 was pressed!\r\n";
		});
	btn_t.SetOnResizeCallback([](void *ptr) {
			Button &btn_ref = WndCallback::GetCallObject<Button>(ptr);
			WndSizeParams &params = *(WndSizeParams *)*btn_ref.SomeDataPtr();
			btn_ref.SetWndPos(WndPairValue{ params._wnd.GetWndSize().first / 4, params._wnd.GetWndSize().second / 6 });
		});
	
	// ComboBox 1
	cmb_bx.SetOnChangeCallback([](void *ptr) {
			ComboBox &cmb_bx_ref = WndCallback::GetCallObject<ComboBox>(ptr);
			std::wcout << cmb_bx_ref.GetItemId() << L" |----\r\n";
		});
	cmb_bx.SetOnResizeCallback([](void *ptr) {
			ComboBox &cmb_bx_ref = WndCallback::GetCallObject<ComboBox>(ptr);
			WndSizeParams &params = *(WndSizeParams *)*cmb_bx_ref.SomeDataPtr();
			cmb_bx_ref.SetWndSize(WndPairValue{ params._wnd.GetWndSize().first / 4, params._wnd.GetWndSize().second / 6 });
			cmb_bx_ref.SetWndPos(WndPairValue{ params._wnd.GetWndSize().first / 2, params._wnd.GetWndSize().second / 4 });
		});

	// Label 1
	lbl.SetOnResizeCallback([](void *ptr) {
			Label &lbl_ref = WndCallback::GetCallObject<Label>(ptr);
			WndSizeParams &params = *(WndSizeParams *)*lbl_ref.SomeDataPtr();
			lbl_ref.SetWndSize(WndPairValue{ params._wnd.GetWndSize().first / 4, params._wnd.GetWndSize().second / 30 });
			lbl_ref.SetWndPos(WndPairValue{ params._wnd.GetWndSize().first / 2, params._wnd.GetWndSize().second / 3 });
		});

	// Edit 1
	edit.SetOnChangeCallback([](void *ptr) {
			try {
				Edit &edit_ref = WndCallback::GetCallObject<Edit>(ptr);
				wchar_t wstr[32] = { 0 };
				edit_ref.GetWndText(wstr, 32);
				std::wcout << wstr << L"\r\n";
			}
			catch (std::wstring &error) {
				std::wcout << L"None\r\n";
			}
		});
	edit.SetOnResizeCallback([](void *ptr) {
			Edit &edit_ref = WndCallback::GetCallObject<Edit>(ptr);
			WndSizeParams &params = *(WndSizeParams *)*edit_ref.SomeDataPtr();
			//edit_ref.SetWndSize(WndPairValue{ params._wnd.GetWndSize().first / 4, params._wnd.GetWndSize().second / 6 });
			edit_ref.SetWndPos(WndPairValue{ params._wnd.GetWndSize().first / 4, params._wnd.GetWndSize().second / 6 });
		});

	// Menu & menu points
	MenuPoint p_f(L"First");
	MenuPoint p_s(L"Second");
	p_f.SetOnClickCallback([&p_s, &wnd](void *ptr) {
			MenuPoint &menu_point = WndCallback::GetCallObject<MenuPoint>(ptr);
			p_s.SetState(!p_s.GetState());

			std::wcout << L"First is work!\r\n";
		});
	p_s.SetOnClickCallback([&btn_t, &wnd, &j](void *ptr) {
			btn_t.ShowWnd(j % 2);

			std::wcout << L"Second is work!\r\n";
		});

	PopupMenu pop_s(L"Second popup");
	pop_s.AttachMenuPoint(&p_f);

	PopupMenu pop_f(L"First popup");
	pop_f.AttachMenuPoint(&p_s);
	pop_f.AppendSeparator();
	pop_f.AttachPopupMenu(&pop_s);

	menu.AttachMenuPoint(&p_f);
	menu.AttachPopupMenu(&pop_f);
	//menu.AttachMenuPoint(&p_t);
	// -----

	// Attach controls
	wnd.AttachChildControl(&btn);
	wnd.AttachChildControl(&btn_t);
	wnd.AttachChildControl(&cmb_bx);
	wnd.AttachChildControl(&lbl);
	wnd.AttachChildControl(&edit);
	wnd.AttachMenu(&menu);

	// Settings
	cmb_bx.AddItem(L"pososi 1");
	cmb_bx.AddItem(L"pososi 2");
	cmb_bx.AddItem(L"pososi 3");
	cmb_bx.SelectItem(0);

	// Font
	NormalFont good_font;
	{
		good_font.SetFont(&btn);
		good_font.SetFont(&btn_t);
		good_font.SetFont(&cmb_bx);
		good_font.SetFont(&lbl);
		good_font.SetFont(&edit);
	}
	
	// Show window
	wnd.ShowWnd(true);

	// Run message loop
	return wnd.Run();
}