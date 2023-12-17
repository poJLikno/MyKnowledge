#pragma once
#include <iostream>

class ClassForDll {
public:
	ClassForDll() {}
	virtual ~ClassForDll() {}

	virtual void CallFunc(const wchar_t *str) {
		std::wcout << str;
	}
};