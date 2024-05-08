#ifndef WINDOWLIB_MENU_POINT_H
#define WINDOWLIB_MENU_POINT_H

#include <windows.h>
#include "WndCallback.h"

enum MenuPointType {
	Enabled = MF_ENABLED,
	Checked = MF_CHECKED
};

class MenuPoint : public CallbackWindow {
private:
	static unsigned __int32 ID_COUNTER;

	HMENU _parent_hmenu = { 0 };

	wchar_t *_text = nullptr;
	bool _state = true;
	unsigned int _id = 0;
	unsigned int  _type = 0;

public:
	MenuPoint(const wchar_t *text, MenuPointType menu_point_type = MenuPointType::Enabled);

	void SetMenuParent(const HMENU &hmenu);

	unsigned int GetId() const;
	bool GetState() const;
	void SetState(bool flag);

	template<class T>
	void SetOnClickCallback(T callback);
};

template<class T>
inline void MenuPoint::SetOnClickCallback(T callback) {
	_callbacks[0] = callback;
}

#endif
