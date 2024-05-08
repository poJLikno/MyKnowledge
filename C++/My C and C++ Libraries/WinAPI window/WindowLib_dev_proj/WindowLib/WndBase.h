#ifndef WINDOWLIB_WND_BASE_H
#define WINDOWLIB_WND_BASE_H

#include <iostream>
#include <string>
#include <windows.h>

class WndPairValue {
public:
	int first = 0;
	int second = 0;
};

class WndBase {
protected:
	HWND _hwnd = { 0 };
	WndPairValue _pos = { 0, 0};
	WndPairValue _size = { 0, 0};
	bool _is_visible = true;

	void *_some_data = nullptr;

	WndBase(const WndPairValue &pos, const WndPairValue &size)
		: _pos(pos), _size(size) {};

public:
	virtual ~WndBase();

	virtual void **SomeDataPtr() final;

	//virtual WndPairValue &get_pos_ref() final;
	//virtual WndPairValue &get_size_ref() final;

	virtual void ShowWnd(const bool &flag) final;
	virtual LRESULT SendMsg(const UINT &msg, const WPARAM &wparam, const LPARAM &lparam) final;

	virtual HWND GetHwnd() final;

	virtual void GetWndText(wchar_t *buffer, const size_t &count) final;
	virtual void SetWndText(const wchar_t *label) final;

	virtual LONG_PTR GetWndStyle() final;
	virtual void SetWndStyle(const LONG_PTR &params) final;

	virtual HWND GetWndParent() final;
	virtual void SetWndParent(const HWND &hwnd);// Non final cause can be problems

	virtual WndPairValue GetWndPos() final;
	virtual void SetWndPos(const WndPairValue &pos) final;

	virtual WndPairValue GetWndSize() final;
	virtual void SetWndSize(const WndPairValue &size) final;

	virtual void SetWndOrderZ(const HWND &hwnd) final;
};

#endif
