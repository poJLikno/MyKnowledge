#include <iostream>
#include <string>
#include <string.h>
#include <windows.h>

#include <io.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

// size != num of symbols
void get_console_utf8(char *buffer, size_t size) {
	wchar_t *w_buffer = (wchar_t *)calloc(size, sizeof(wchar_t));
	if (w_buffer) {
		unsigned int w_read = 0u;

		ReadConsoleW(GetStdHandle(STD_INPUT_HANDLE), w_buffer, size, (LPDWORD)&w_read, NULL);
		WideCharToMultiByte(CP_UTF8, 0, w_buffer, w_read, buffer, size, NULL, NULL);

		free(w_buffer);
		w_buffer = nullptr;

		unsigned long long written = strlen(buffer);
		buffer[written - 1] = 0;
		buffer[written - 2] = 0;
	}
}

int main(int argc, const char **argv) {// UTF-8
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	char str[] = "\321\221жик";// \u0451 => ё | \321\221 => ё

	for (int i = 0; i < sizeof(str); ++i) {
		//std::cout << (int)str[i] << " - " << i << "\n";
		printf("%d - %d\n", (int)str[i], i);
	}
	//std::cout << str << " - " << sizeof(str) << "\n";
	printf("%s - %d\n", str, (int)sizeof(str));

	char buf[64] = { 0 };
	//std::cin.getline(buf, sizeof(buf));
	//fgets(buf, 32, stdin);
	get_console_utf8(buf, 32ull);

	for (int i = 0; i < sizeof(buf); ++i) {
		//std::cout << (int)buf[i] << " - " << i << "\n";
		printf("%d - %d\n", (int)buf[i], i);
	}
	//std::cout << buf << " - " << sizeof(buf) << "\n";
	if (buf)
		printf("%s - %d\n", buf, (int)strlen(buf) + 1);

	return 0;
}