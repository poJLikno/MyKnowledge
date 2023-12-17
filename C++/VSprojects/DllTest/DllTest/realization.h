#ifndef REALIZATION_H
#define REALIZATION_H

#ifdef DLLTEST_EXPORTING_DLL
#define DLLTEST_WORD __declspec(dllexport)
#else
#define DLLTEST_WORD __declspec(dllimport)
#endif

/*#include "../ConsoleDllTest/api.h"// app api

class DllClass : public ClassForDll { // class for dynamic-dynamic link (parent: api class -> override)
public:
	DllClass() {}
	~DllClass() {}

	void CallFunc(const wchar_t *str) override {
		std::wcout << L"я –усски!\r\n";
	}
};

extern "C" DLLTEST_WORD ClassForDll *LoadMod() {
	return new DllClass();
}

extern "C" DLLTEST_WORD void ReleaseMod(ClassForDll **ptr) {
	delete *ptr;
	*ptr = nullptr;
}*/

extern "C" DLLTEST_WORD void SomeFunc();

class DLLTEST_WORD DllImportClass { // Class for static-dynamic link
private:
	int num_;

public:
	DllImportClass(int num = 0) : num_(num) {}
	~DllImportClass() {}

	void GetNum() const {
		std::wcout << num_ << L"\r\n";
	}
};

#endif