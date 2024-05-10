#include <stdio.h>
#include <windows.h>

class A {
public:
	char *_err = nullptr;

	A(const A &obj) {
		this->_err = obj._err;
		printf("Копия\n");
	}

	A(A &&obj) noexcept {
		this->_err = obj._err;
		obj._err = nullptr;
		printf("Перемещ\n");
	}

	A(char *err) : _err(err) {
		printf("Констр\n");
	}

	virtual ~A() {
		printf("Дестр\n");
	}
};

int main(int argc, const char *argv) {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try {
		//A a((char *)"Ошибка Error!");

		throw A((char *)"Ошибка Error!");
	}
	catch (A &error) {
		printf("%s\n", error._err);
	}

	return 0;
}
