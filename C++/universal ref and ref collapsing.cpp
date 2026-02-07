#include <iostream>

template<typename T>
void func(T &&xvalue)
{
    std::cout << /*(T)xvalue*/ std::forward<T>(xvalue) << "\n";
}

/* Reference Collapsing [if (int&& int&& = int&&), overwise (int& int&& {and other combos} = int&) ] */
int main(int argc, const char **argv)
{
    std::cout << "Aloha!\n";

    func(12);/* rvalue */

    int num = 10;
    func(num);/* lvalue */

    int &&r_ref = 33;
    func(r_ref);/* lvalue */

    decltype(10) a = 0;/* int */
    decltype(a) b = 0;/* int */
    int &c = b;
    decltype(c) d = a;/* int & */
    int &&e = 55;
    decltype(e) f = 65;/* int && */

    decltype(d) &&g = d;/* int & */

    return 0;
}
