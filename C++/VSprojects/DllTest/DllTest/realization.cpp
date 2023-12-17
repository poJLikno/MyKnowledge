#include <iostream>
#include <string>
#include <windows.h>

#define DLLTEST_EXPORTING_DLL// important for static-dynamic & dynamic-dynamic links
#include "realization.h"

BOOL WINAPI MainThread() {// main thread
	MessageBox(NULL, std::to_wstring(GetCurrentThreadId()).c_str(), L"Dll thread ID", MB_OK);

	return TRUE;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)// Entry point
{
	//HANDLE hThread = nullptr;
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH: // A process is loading the DLL.
		DisableThreadLibraryCalls(hinstDLL);
		/*hThread = */CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, NULL, 0, NULL);

		MessageBox(NULL, L"DLL_PROCESS_ATTACH", L"Message", MB_OK);
		break;

	case DLL_PROCESS_DETACH: // A process unloads the DLL.
		//if (hThread != NULL) {
		//	DWORD exit_code = 0ul;
		//	GetExitCodeThread(hThread, &exit_code);
		//	MessageBox(NULL, std::to_wstring(exit_code).c_str(), L"Dll exit code", MB_OK);
		//	TerminateThread(hThread, exit_code);
		//}

		MessageBox(NULL, L"DLL_PROCESS_DETACH", L"Message", MB_OK);
		break;
	}

	return TRUE;
}

void SomeFunc() {
	//...Do something
}
