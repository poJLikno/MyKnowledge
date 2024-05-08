#ifndef WINDOWLIB_COMBO_BOX_H
#define WINDOWLIB_COMBO_BOX_H

#include "WndBase.h"
#include "WndCallback.h"

class ComboBox : public WndBase, public CallbackWindow {
private:
	using WndBase::GetWndText;
	using WndBase::SetWndText;

public:
	ComboBox(WndPairValue pos = { 0, 0 }, WndPairValue size = { 20, 20 });

	virtual void SetWndParent(const HWND &hwnd) override;

	void AddItem(const wchar_t *text);

	void SelectItem(const int &id);

	int GetItemId();

	void GetItem(wchar_t *buffer);

	void GetOldItem(wchar_t *buffer, int buffer_size);

	template<class T>
	void SetOnResizeCallback(T callback);

	template<class T>
	void SetOnChangeCallback(T callback);
};

template<class T>
inline void ComboBox::SetOnResizeCallback(T callback) {
	_callbacks[0] = callback;
}

template<class T>
inline void ComboBox::SetOnChangeCallback(T callback) {
	_callbacks[1] = callback;
}

#endif
