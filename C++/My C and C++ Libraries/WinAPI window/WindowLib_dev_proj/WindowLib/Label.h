#ifndef WINDOWLIB_LABEL_H
#define WINDOWLIB_LABEL_H

#include "WndBase.h"
#include "WndCallback.h"

class Label : public WndBase, public CallbackWindow {
public:
	Label(const wchar_t *text, WndPairValue pos = { 0, 0 }, WndPairValue size = { 20, 20 });

	template<class T>
	void SetOnResizeCallback(T callback);
};

template<class T>
inline void Label::SetOnResizeCallback(T callback) {
	_callbacks[0] = callback;
}

#endif
