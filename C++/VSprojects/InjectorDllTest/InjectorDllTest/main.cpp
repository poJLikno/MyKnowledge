#include <iostream>
#include <windows.h>
#include <string>

int wmain(int argc, const wchar_t **argv) {
	setlocale(LC_ALL, "");
	_wsetlocale(LC_ALL, L"");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 3) {
		std::wcout << L"InjectorDllTest.exe <process ID> <dll path>\r\n";
		return 0;
	}

	/* {// Tests
		std::wcout << argc << L"\r\n" << argv[0] << " : " << _wtoi(argv[1]) << " : " << argv[2] << L"\r\n";
		return 0;
	}*/

	// Dll file path for injection.
	wchar_t *dll_path = (wchar_t *)argv[2];//(wchar_t *)L"path";

	// Get handle of target process for injection
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, /*PID*/_wtoi(argv[1]));
	if (!hProcess) {
		std::wcout << L"hProcess error -> " << GetLastError() << L"\r\n";
		return 1;
	}

	// Allocate memory for dll_path string in the target process
	// (path length + null terminator) * size of char/wchat_t
	void *allocated_mem_ptr = VirtualAllocEx(
		hProcess, 0,
		(std::wstring(dll_path).length() + 1) * sizeof(wchar_t),
		MEM_COMMIT, PAGE_READWRITE);
	if (!allocated_mem_ptr) {
		std::wcout << L"allocated_mem_ptr error -> " << GetLastError() << L"\r\n";
		return 1;
	}

	// Write dll path in the allocated memory of target process
	WriteProcessMemory(
		hProcess, allocated_mem_ptr,
		(const void *)dll_path, (std::wstring(dll_path).length() + 1) * sizeof(wchar_t),
		NULL);

	// Create remote thread in target process which calls LoadLibrary with dll path in argument
	// program loads our dll
	HANDLE hLoadThread = CreateRemoteThread(
		hProcess,
		NULL, NULL,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryW"),
		allocated_mem_ptr,
		NULL, NULL);
	if (!hLoadThread) {
		std::wcout << L"hLoadThread error -> " << GetLastError() << L"\r\n";
		return 1;
	}

	WaitForSingleObject(hLoadThread, INFINITE);

	std::wcout << L"Dll path allocated in " << allocated_mem_ptr << L"\r\n";

	// Clean up
	if (hLoadThread) {
		if (!CloseHandle(hLoadThread)) {
			std::wcout << L"Close hLoadThread error -> " << GetLastError() << L"\r\n";
		}
	}

	// Free allocated memory for dll path
	if (hProcess) {
		VirtualFreeEx(hProcess, allocated_mem_ptr, (std::wstring(dll_path).length() + 1) * sizeof(wchar_t), MEM_RELEASE);
		if (allocated_mem_ptr) {
			allocated_mem_ptr = nullptr;
		}

		if (!CloseHandle(hProcess)) {
			std::wcout << L"Close hProcess error -> " << GetLastError() << L"\r\n";
		}
	}

	return 0;
}