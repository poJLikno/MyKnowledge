#include "MenuPoint.h"

unsigned __int32 MenuPoint::ID_COUNTER = WM_USER + 1;

MenuPoint::MenuPoint(const wchar_t *text, MenuPointType menu_point_type)
	: CallbackWindow(1), _text((wchar_t *)text), _id(ID_COUNTER++), _type(menu_point_type) {}

void MenuPoint::SetMenuParent(const HMENU &hmenu) {
	AppendMenu(hmenu, _type, _id, _text);
	_parent_hmenu = hmenu;
}

unsigned int MenuPoint::GetId() const {
	return _id;
}

bool MenuPoint::GetState() const {
	return _state;
}

void MenuPoint::SetState(bool flag) {
	_state = flag;

	switch (_type) {
	case Enabled:
		EnableMenuItem(_parent_hmenu, _id, (_state ? MF_ENABLED : MF_DISABLED));
		break;

	case Checked:
		CheckMenuItem(_parent_hmenu, _id, (_state ? MF_CHECKED : MF_UNCHECKED));
		break;

	default:
		break;
	}
}
