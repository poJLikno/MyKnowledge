#include <iostream>
#include <windows.h>
#include <thread>

//#define WINDOWLIB_NO_CONSOLE

#include "WindowLib/Window.h"
#include "WindowLib/NormalFont.h"

int main(int argc, const char **argv) {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	Window wnd("TestApp", WndPairValue{ CW_USEDEFAULT, CW_USEDEFAULT }, WndPairValue{ 400, 300 });
	//wnd.SetWndText("Programm");
	wnd.SetWndText("Русский Язык ya!");
	wnd.EnableControlsDialogMessages(true);

	__int64 j = 0;

	//wnd.AddCallback("AsyncLoopCallback", [&j](void *ptr) {
	//		Window &wnd = Callback::GetCallbackParams<Window>(ptr);
	//		wnd.SetWndText(std::string(std::to_string(j)).c_str());//std::to_string(j).c_str());
	//		std::cout << "It's work!\r\n";
	//	});

	Button btn("Русская кнопка ya!", WndPairValue{ 100, 100 }, WndPairValue{ 50, 25 });
	//Button btn("First button", WndPairValue{ 100, 100 }, WndPairValue{ 50, 25 });
	Button btn_t("Second button", WndPairValue{ 350, 100 }, WndPairValue{ 200, 100 });
	ComboBox cmb_bx(WndPairValue{ 100, 350 }, WndPairValue{ 140, 200 });
	Label lbl("govnar_pes Рус", WndPairValue{ 300, 350 }, WndPairValue{ 140, 20 });
	Menu menu;
	Edit edit;

	// Button 1
	btn.AddCallback("MainCallback", [&j](void *ptr) {
		Button &btn = Callback::GetCallbackParams<Button>(ptr);
			btn.SetWndText(std::to_string(j++).c_str());
			std::cout << "Button 1 was pressed!\r\n";
		});
	btn.AddCallback("ParentResizeCallback", [](void *ptr) {
			ParentResizeCallbackParams &params = Callback::GetCallbackParams<ParentResizeCallbackParams>(ptr);
			Button &btn = Callback::GetCallbackParams<Button>(params.wnd);/**((Button *)params.wnd);*/
			WndPairValue &size = params.old_size;
			if (btn.GetWndParent() == nullptr) {
				return;
			}
			btn.SetWndSize(WndPairValue{ btn.GetWndParent()->GetWndSize().first / 4, btn.GetWndParent()->GetWndSize().second / 6});
		});

	//Button 2
	btn_t.AddCallback("MainCallback", [&j](void *ptr) {
			Button &btn_ref = Callback::GetCallbackParams<Button>(ptr);
			btn_ref.SetWndText(std::to_string(-(j++)).c_str());
			std::cout << "Button 2 was pressed!\r\n";
		});
	btn_t.AddCallback("ParentResizeCallback", [](void *ptr) {
			ParentResizeCallbackParams &params = Callback::GetCallbackParams<ParentResizeCallbackParams>(ptr);
			Button &btn = Callback::GetCallbackParams<Button>(params.wnd);
			if (btn.GetWndParent() == nullptr) {
				return;
			}
			btn.SetWndPos(WndPairValue{ btn.GetWndParent()->GetWndSize().first / 4, btn.GetWndParent()->GetWndSize().second / 6 });
		});
	
	// ComboBox 1
	cmb_bx.AddCallback("MainCallback", [](void *ptr) {
			ComboBox &cmb_bx_ref = Callback::GetCallbackParams<ComboBox>(ptr);
			char str[32] = { 0 };
			cmb_bx_ref.GetItem(str, 32);
			std::wcout << cmb_bx_ref.GetItemId() << " |----| " << str << "\r\n";
		});
	cmb_bx.AddCallback("ParentResizeCallback", [](void *ptr) {
			ParentResizeCallbackParams &params = Callback::GetCallbackParams<ParentResizeCallbackParams>(ptr);
			ComboBox &cmb_bx_ref = Callback::GetCallbackParams<ComboBox>(params.wnd);
			if (cmb_bx_ref.GetWndParent() == nullptr) {
				return;
			}
			cmb_bx_ref.SetWndSize(WndPairValue{ cmb_bx_ref.GetWndParent()->GetWndSize().first / 4, cmb_bx_ref.GetWndParent()->GetWndSize().second / 6 });
			cmb_bx_ref.SetWndPos(WndPairValue{ cmb_bx_ref.GetWndParent()->GetWndSize().first / 2, cmb_bx_ref.GetWndParent()->GetWndSize().second / 4 });
		});

	// Label 1
	lbl.AddCallback("ParentResizeCallback", [](void *ptr) {
			ParentResizeCallbackParams &params = Callback::GetCallbackParams<ParentResizeCallbackParams>(ptr);
			Label &lbl_ref = Callback::GetCallbackParams<Label>(params.wnd);
			if (lbl_ref.GetWndParent() == nullptr) {
				return;
			}
			//lbl_ref.SetWndSize(WndPairValue{ lbl_ref.GetWndParent()->GetWndSize().first / 4, lbl_ref.GetWndParent()->GetWndSize().second / 30 });
			lbl_ref.SetWndPos(WndPairValue{ lbl_ref.GetWndParent()->GetWndSize().first / 2, lbl_ref.GetWndParent()->GetWndSize().second / 3 });
		});

	// Edit 1
	edit.AddCallback("MainCallback", [](void *ptr) {
			try {
				Edit &edit_ref = Callback::GetCallbackParams<Edit>(ptr);
				char str[32] = { 0 };
				edit_ref.GetWndText(str, 32);
				std::cout << str << "\r\n";
			}
			catch (std::string &/*error*/) {
				std::cout << "None\r\n";
			}
		});
	edit.AddCallback("ParentResizeCallback", [](void *ptr) {
			ParentResizeCallbackParams &params = Callback::GetCallbackParams<ParentResizeCallbackParams>(ptr);
			Edit &edit_ref = Callback::GetCallbackParams<Edit>(params.wnd);
			if (edit_ref.GetWndParent() == nullptr) {
				return;
			}
			//edit_ref.SetWndSize(WndPairValue{ params._wnd.GetWndSize().first / 4, params._wnd.GetWndSize().second / 6 });
			edit_ref.SetWndPos(WndPairValue{ edit_ref.GetWndParent()->GetWndSize().first / 4, edit_ref.GetWndParent()->GetWndSize().second / 6 });
		});

	// Menu & menu points
	MenuPoint p_f("First");
	MenuPoint p_s("Second");
	p_f.AddCallback("MainCallback", [&p_s, &wnd](void *ptr) {
			MenuPoint &menu_point = Callback::GetCallbackParams<MenuPoint>(ptr);
			p_s.SetState(!p_s.GetState());

			std::cout << "First is work!\r\n";
		});
	p_s.AddCallback("MainCallback", [&btn_t, &wnd, &j](void *ptr) {
			btn_t.ShowWnd(j % 2);

			std::cout << "Second is work!\r\n";
		});

	PopupMenu pop_s("Second popup");
	pop_s.AttachMenuPoint(&p_f);

	PopupMenu pop_f("First popup");
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
	edit.SetWndText("Русский текст pozalusta");
	cmb_bx.AddItem("pososi 1");
	//cmb_bx.AddItem("pososi 2");
	cmb_bx.AddItem("Рус строчка!");
	cmb_bx.AddItem("pososi 3");
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