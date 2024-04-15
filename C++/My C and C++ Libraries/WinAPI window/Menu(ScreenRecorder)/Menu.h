#pragma once
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <windows.h>

enum MenuPointType
{
	Enabled = MF_ENABLED,
	Checked = MF_CHECKED
};

class MenuBase
{
protected:
	HMENU hMenu = { 0 };

	MenuBase() {}

public:
	virtual ~MenuBase() {
		DestroyMenu(hMenu);
	}

	HMENU GetHmenu() const {
		return hMenu;
	}
};

class Menu : public MenuBase
{
public:
	Menu() {
		hMenu = CreateMenu();
	}

	void AttachToWindow(HWND hWnd) {
		SetMenu(hWnd, hMenu);
	}
};

class ChildMenu : public MenuBase
{
public:
	ChildMenu(const wchar_t *text, Menu *menu) {
		hMenu = CreatePopupMenu();
		AppendMenu(menu->GetHmenu(), MF_POPUP, (UINT_PTR)hMenu, text);
	}
};

class MenuPoint
{
private:
	HMENU hMenu;
	unsigned __int32 id;
	unsigned __int32  type;
	bool state;

public:
	MenuPoint(const wchar_t *text, MenuBase *menu, MenuPointType menu_point_type = MenuPointType::Enabled);

	bool GetState() const;

	void ChangeState();

	bool WasPressed(WPARAM *wParam) const;

	static void AddSeparator(MenuBase *menu);
};

#endif
