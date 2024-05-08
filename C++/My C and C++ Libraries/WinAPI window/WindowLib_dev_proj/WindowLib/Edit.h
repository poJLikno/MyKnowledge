#ifndef WINDOWLIB_EDIT_H
#define WINDOWLIB_EDIT_H

#include "WndBase.h"
#include "WndCallback.h"

class Edit : public WndBase, public CallbackWindow {
public:
	Edit(WndPairValue pos = WndPairValue{ 0, 0 }, WndPairValue size = WndPairValue{ 60, 20 });

	virtual void SetWndParent(const HWND &hwnd) override;

	template<class T>
	void SetOnResizeCallback(T callback);

	template<class T>
	void SetOnChangeCallback(T callback);
};

template<class T>
inline void Edit::SetOnResizeCallback(T callback) {
	_callbacks[0] = callback;
}

template<class T>
inline void Edit::SetOnChangeCallback(T callback) {
	_callbacks[1] = callback;
}

#endif
