#ifndef WINDOWLIB_MENU_BASE_H
#define WINDOWLIB_MENU_BASE_H

#include "MenuPoint.h"
#include "WndList.h"

class MenuBase {
protected:
	HMENU _hmenu = { 0 };

	WndList<MenuPoint> _menu_points_list;
	WndList<MenuBase> _popup_menus_list;

	MenuBase() = default;

public:
	virtual ~MenuBase();

	virtual HMENU GetHmenu() final;

	virtual void SetHParent(void *hparent) = 0;

	WndList<MenuPoint> &GetMenuPointsList();

	WndList<MenuBase> &GetPopupMenusList();

	virtual void AttachMenuPoint(MenuPoint *menu_point) final;

	virtual void AttachPopupMenu(MenuBase *popup_menu) final;

	virtual void AppendSeparator() final;
};

#endif
