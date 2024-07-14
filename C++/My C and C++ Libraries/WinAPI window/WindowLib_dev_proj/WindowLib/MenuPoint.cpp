#include "MenuPoint.h"

unsigned __int32 MenuPoint::ID_COUNTER = WM_USER + 1;

MenuPoint::MenuPoint(const char *text, MenuPointType menu_point_type)
    : _text(text), _id(ID_COUNTER++), _type(menu_point_type) {}

void MenuPoint::SetMenuParent(const HMENU &hmenu) {
    int text_size = (int)strlen(_text) + 1;
    wchar_t *w_text = new wchar_t[text_size] { 0 };
    MultiByteToWideChar(CP_UTF8, 0, _text, text_size, w_text, text_size);

    AppendMenuW(hmenu, _type, _id, w_text);
    _parent_hmenu = hmenu;

    delete[] w_text;
    w_text = nullptr;
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
