#include <iostream>
#include <windows.h>
#include <string>

#include "api.h"// api
#include "../DllTest/realization.h"// for static-dynamic link header
#pragma comment(lib, "DllTest.lib")// for static-dynamic link dependencies

class DllManager {// Class for dynamic-dynamic link
private:
	HINSTANCE hinstDLL_;

public:
	DllManager() : hinstDLL_(NULL) {}
	~DllManager() { Release(); }

	unsigned long Import(const wchar_t *lib_name) {
		DWORD result = 0ul;
		hinstDLL_ = LoadLibrary(lib_name);
		if (hinstDLL_ == NULL) {
			result = GetLastError();
		}
		return result;
	}

	void GetObj(const char *func_name, void **func_ptr) {
		if (hinstDLL_ != NULL) {
			*func_ptr = (void *)GetProcAddress(hinstDLL_, func_name);
		}
	}

	int Release() {
		int result = -1;
		if (hinstDLL_ != NULL) {
			result = FreeLibrary(hinstDLL_);
			hinstDLL_ = nullptr;
		}
		return result;
	}
};

int main(int argc, const wchar_t **argv) {
	setlocale(LC_ALL, "");
	_wsetlocale(LC_ALL, L"");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::wcout << L"W Русский язык & English\r\n";
	std::cout << "A Русский язык & English\r\n";

	/*ClassForDll *(*loadmod_ptr)() = nullptr;// Dynamic-dynamic link
	void (*releasemod_ptr)(ClassForDll **) = nullptr;
	DllManager dll_manager;
	dll_manager.Import(L"DllTest.dll");
	dll_manager.GetObj("LoadMod", (void **)&loadmod_ptr);
	dll_manager.GetObj("ReleaseMod", (void **)&releasemod_ptr);

	ClassForDll *class_ptr = nullptr;

	if (loadmod_ptr && releasemod_ptr) {
		class_ptr = loadmod_ptr();

		class_ptr->CallFunc(L"Jony\r\n");

		releasemod_ptr(&class_ptr);
	}
	else MessageBox(NULL, L"Can't run mod", L"Error", MB_OK);*/

	DllImportClass a(12);
	a.GetNum();

	_wsystem(L"pause");

	return 0;
}