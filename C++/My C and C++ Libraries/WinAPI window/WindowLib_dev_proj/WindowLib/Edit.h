#ifndef WINDOWLIB_EDIT_H
#define WINDOWLIB_EDIT_H

#include "WndBase.h"
#include "CallbackManager.h"

class Edit : public WndBase, public CallbackManager {
public:
	Edit(WndPairValue pos = WndPairValue{ 0, 0 }, WndPairValue size = WndPairValue{ 60, 20 });

	virtual void SetWndParent(WndBase *wnd) override;
};

#endif
