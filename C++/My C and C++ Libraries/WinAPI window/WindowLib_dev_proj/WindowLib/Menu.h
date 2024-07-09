#ifndef WINDOWLIB_MENU_H
#define WINDOWLIB_MENU_H

#include "MenuBase.h"

class Menu : public MenuBase {
public:
	Menu() {
		_hmenu = CreateMenu();
	}

	virtual void SetHParent(void *hparent) override {
		SetMenu((HWND)hparent, _hmenu);
	}

	// Menu point access & message detection
};

class PopupMenu : public MenuBase {
private:
	const char *_text;

public:
	PopupMenu(const char *text) : _text(text) {
		_hmenu = CreatePopupMenu();
	}

	virtual void SetHParent(void *hparent) override {
		int text_size = (int)strlen(_text) + 1;
		wchar_t *w_text = new wchar_t[text_size] { 0 };
		MultiByteToWideChar(CP_UTF8, 0, _text, text_size, w_text, text_size);

		AppendMenuW((HMENU)hparent, MF_POPUP, (UINT_PTR)_hmenu, w_text);

		delete[] w_text;
		w_text = nullptr;
	}
};

#endif
