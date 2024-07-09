#ifndef WINDOWLIB_BUTTON_H
#define WINDOWLIB_BUTTON_H

#include "WndBase.h"
#include "CallbackManager.h"

class Button : public WndBase, public CallbackManager {
private:
	const char *_text;

public:
	Button(const char *text,
		WndPairValue pos = { 0, 0 },
		WndPairValue size = { 20, 20 });

	virtual void SetWndParent(WndBase *wnd) override;
};

#endif
