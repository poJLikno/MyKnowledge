#ifndef NORMAL_FONT_H
#define NORMAL_FONT_H

#include "WndBase.h"

class NormalFont
{
private:
	HFONT _normal_font = {};

public:
	NormalFont();
	~NormalFont();

	void SetFont(const HWND &hwnd);

	void SetFont(WndBase *wnd);
};

#endif