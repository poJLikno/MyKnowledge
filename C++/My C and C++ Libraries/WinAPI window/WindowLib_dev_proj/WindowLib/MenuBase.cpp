#include "MenuBase.h"

MenuBase::~MenuBase() {
	DestroyMenu(_hmenu);
}

HMENU MenuBase::GetHmenu() {
	return _hmenu;
}

WndList<MenuPoint> &MenuBase::GetMenuPointsList() {
	return _menu_points_list;
}

WndList<MenuBase> &MenuBase::GetPopupMenusList() {
	return _popup_menus_list;
}

void MenuBase::AttachMenuPoint(MenuPoint *menu_point) {
	_menu_points_list.Append(menu_point);
	menu_point->SetMenuParent(_hmenu);
}

void MenuBase::AttachPopupMenu(MenuBase *popup_menu) {
	_popup_menus_list.Append(popup_menu);
	popup_menu->SetHParent((void *)_hmenu);
}

void MenuBase::AppendSeparator() {
	AppendMenu(_hmenu, MF_SEPARATOR, NULL, NULL);
}
