#ifndef NORMAL_FONT_H
#define NORMAL_FONT_H

#include <windows.h>

class NormalFont
{
private:
	HFONT hNewFont = {};

public:
	NormalFont();

	void SetFont(HWND hWnd);
};

#endif