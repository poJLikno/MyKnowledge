#include <iostream>
#include <string.h>
#include <assert.h>

#include "try_catch_diy/try_catch_diy.h"

class A : public try_catch_diy_support
{
private:
    int _id;

public:
    A(int id) : _id(id) { assert(_id > 0); std::cout << "con " << _id << "\n"; }

    A(const A &a) noexcept { *this = a; }
    A(A &&a) noexcept { *this = std::move(a); }

    A &operator=(const A &a) noexcept { if (this != &a) _id *= 10; return *this; }
    A &operator=(A &&a) noexcept { if (this != &a) _id *= 100; return *this; }

    ~A() noexcept/* override */{ std::cout << "des " << _id << "\n"; }
};

int main(int argc, const char **argv)
{
    A a(1);

    TRY_BLOCK
    {
        A b(2);

        TRY_BLOCK
        {
            A c(3);
            {
                A cc(31);
            }
            A ccc(32);
            THROW_IN_BLOCK ("Error 2");
            A d(4);
        }
        CATCH_BLOCK
        {
            std::cout << "Deep 2 !!! -> " << try_catch_block::current_exception << "\n";
            std::cout << "Rethrow\n";
            A erer(41);
            //RETHROW_IN_BLOCK;

            //THROW_IN_BLOCK ("Error 2 rethrow");
            A ereasdsar(42);
        }
        END_BLOCK;

        A e(5);
    }
    CATCH_BLOCK
    {
        std::cout << "Deep 1 !!! -> " << try_catch_block::current_exception << "\n";
    }
    END_BLOCK;

    std::cout << "Aloha!\n";

    return 0;
}
