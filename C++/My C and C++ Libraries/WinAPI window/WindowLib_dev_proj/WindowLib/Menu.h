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
	wchar_t *_text = nullptr;

public:
	PopupMenu(const wchar_t *text) : _text((wchar_t *)text) {
		_hmenu = CreatePopupMenu();
	}

	virtual void SetHParent(void *hparent) override {
		AppendMenu((HMENU)hparent, MF_POPUP, (UINT_PTR)_hmenu, _text);
	}
};

#endif
