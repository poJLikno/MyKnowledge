#ifndef WINDOWLIB_BUTTON_H
#define WINDOWLIB_BUTTON_H

#include "WndBase.h"
#include "WndCallback.h"

class Button : public WndBase, public CallbackWindow {
public:
	Button(const wchar_t *text,
		WndPairValue pos = { 0, 0 },
		WndPairValue size = { 20, 20 });

	template<class T>
	void SetOnResizeCallback(T callback);

	template<class T>
	void SetOnClickCallback(T callback);
};

template<class T>
inline void Button::SetOnResizeCallback(T callback) {
	_callbacks[0] = callback;
}

template<class T>
inline void Button::SetOnClickCallback(T callback) {
	_callbacks[1] = callback;
}

#endif
