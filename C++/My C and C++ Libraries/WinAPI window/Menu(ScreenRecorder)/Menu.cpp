#include "Menu.h"

uint32_t ID_COUNTER = WM_USER + 1;

MenuPoint::MenuPoint(const wchar_t *text, MenuBase *menu, MenuPointType menu_point_type)
	: hMenu(menu->GetHmenu()),
	type(menu_point_type),
	state(true),
	id(ID_COUNTER++)
{
	AppendMenu(hMenu, type, id, text);
}

bool MenuPoint::GetState() const
{
	return state;
}

void MenuPoint::ChangeState()
{
	state = !state;

	switch (type)
	{
	case Enabled:
		EnableMenuItem(hMenu, id, (state ? MF_ENABLED : MF_DISABLED));
		break;

	case Checked:
		CheckMenuItem(hMenu, id, (state ? MF_CHECKED : MF_UNCHECKED));
		break;

	default:
		break;
	}
}

bool MenuPoint::WasPressed(WPARAM *wParam) const
{
	bool result = false;
	if (LOWORD(*wParam) == id)
		result = true;

	return result;
}

void MenuPoint::AddSeparator(MenuBase *menu)
{
	AppendMenu(menu->GetHmenu(), MF_SEPARATOR, NULL, NULL);
}
