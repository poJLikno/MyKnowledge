#ifndef WINDOWLIB_COMBO_BOX_H
#define WINDOWLIB_COMBO_BOX_H

#include "WndBase.h"
#include "CallbackManager.h"

class ComboBox : public WndBase, public CallbackManager {
private:
	using WndBase::GetWndText;
	using WndBase::SetWndText;

public:
	ComboBox(WndPairValue pos = { 0, 0 }, WndPairValue size = { 20, 20 });

	virtual void SetWndParent(WndBase *wnd) override;

	void AddItem(const char *text);

	void SelectItem(const int &id);

	int GetItemId();

	/* Without null ending */
	int GetItemLength();

	void GetItem(char *buffer, const int &count);

	void GetOldItem(char *buffer, int buffer_size);
};

#endif
