#ifndef GRAPHGDI_H_
#define GRAPHGDI_H_


#include "main.h"

class GraphGDI
{
private:
	ULONG_PTR gdiplusToken{};

	ULONG_PTR* gdiplusTokenPointer = &gdiplusToken;

public:
	HDC bufer{};

	HBITMAP bufbit{};

	void CreateDCBufer(HDC dc);

	void ShowDCBufer(HDC dc);

	void DeleteDCBufer();

	GraphGDI();

	~GraphGDI();
};


#endif