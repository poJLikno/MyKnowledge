#include <iostream>
#include <windows.h>

class A
{
public:
    int _a = 12;
    int _b = 12;

    A() = default;

    A(const int &num) : _a(num) {}

    ~A()
    {
        _a = 0;
    }

    void set_a_to(const int &num)
    {
        _a = num;
    }
};

/* Use only with 'new' memory allocation */
template <class T>
class SmtObj
{
private:
    T *_ptr;
    void (*_custom_delete)(T *p);

public:
    SmtObj() noexcept : _ptr(nullptr), _custom_delete(nullptr) {}

    SmtObj(T *ptr, void (*custom_delete)(T *p) = [](T *p)->void { delete p; }) noexcept : _ptr(ptr), _custom_delete(custom_delete) {}

    SmtObj(const SmtObj<T> &smt_obj) = delete;

    SmtObj(SmtObj<T> &&smt_obj) noexcept
    {
        std::swap(_ptr, smt_obj._ptr);
        std::swap(_custom_delete, smt_obj._custom_delete);
    }

    SmtObj<T> &operator= (SmtObj<T> &&smt_obj) noexcept
    {
        std::swap(_ptr, smt_obj._ptr);
        std::swap(_custom_delete, smt_obj._custom_delete);

        return *this;
    }

    SmtObj<T> &operator= (const SmtObj<T> &smt_obj) = delete;

    ~SmtObj() noexcept
    {
        reset();
    }

    void reset() noexcept
    {
        std::cout << "start reset\n";
        if (_ptr)
        {
            std::cout << "delete\n";
            /*delete _ptr;*/
            _custom_delete(_ptr);
            _ptr = nullptr;
            _custom_delete = nullptr;
        }
    }

    T *get() noexcept
    {
        return _ptr;
    }

    const T *get() const noexcept
    {
        return (const T *)_ptr;
    }

    T *operator-> () noexcept
    {
        return get();
    }
    const T *operator-> () const noexcept
    {
        return get();
    }

    T &operator* () noexcept
    {
        return *get();
    }
    const T &operator* () const noexcept
    {
        return (const T &)*get();
    }

    T &operator[] (size_t index) noexcept
    {
        return _ptr[index];
    }
    const T &operator[] (size_t index) const noexcept
    {
        return _ptr[index];
    }

    operator const T *() const noexcept
    {
        return _ptr;
    }
};

/* Use only with 'new' memory allocation */
template <class T>
class SmtObj<T[]>
{
private:
    T *_ptr;

public:
    SmtObj() noexcept : _ptr(nullptr) {}

    SmtObj(T *ptr) noexcept : _ptr(ptr) {}

    SmtObj(const SmtObj<T[]> &smt_obj) = delete;

    SmtObj(SmtObj<T[]> &&smt_obj) noexcept
    {
        std::swap(_ptr, smt_obj._ptr);
    }

    SmtObj<T[]> &operator= (SmtObj<T[]> &&smt_obj) noexcept
    {
        std::swap(_ptr, smt_obj._ptr);

        return *this;
    }

    SmtObj<T[]> &operator= (const SmtObj<T[]> &smt_obj) = delete;

    ~SmtObj() noexcept
    {
        reset();
    }

    void reset() noexcept
    {
        std::cout << "start reset[]\n";
        if (_ptr)
        {
            std::cout << "delete[]\n";
            delete[] _ptr;
            _ptr = nullptr;
        }
    }

    T *get() noexcept
    {
        return _ptr;
    }

    const T *get() const noexcept
    {
        return _ptr;
    }

    T *operator-> () noexcept
    {
        return get();
    }
    const T *operator-> () const noexcept
    {
        return get();
    }

    T &operator* () noexcept
    {
        return *get();
    }
    const T &operator* () const noexcept
    {
        return *get();
    }

    T &operator[] (size_t index) noexcept
    {
        return _ptr[index];
    }
    const T &operator[] (size_t index) const noexcept
    {
        return _ptr[index];
    }

    operator const T *() const noexcept
    {
        return _ptr;
    }
};

int main(int argc, const char **argv)
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::cout << "Aloha!\n";

    //std::unique_ptr<int> a = std::make_unique<int>(int(13));
    //std::unique_ptr<A> a = std::make_unique<A>(A(13));
    //std::unique_ptr<int[]> a(new int[4] { 0 });// = std::make_unique<int[]>(int[4] { 0 });


    //SmtObj<A> a = new A(99);
    //int t[2] = { 0, 1 };

    //SmtObj<int> a;
    SmtObj<int[]> a;

    if (!a)
    {
        std::cout << "nullptr\n";
    }

    //a = SmtObj<int>(new int[4] { 1, 2, 3, 4 }, [](int *p)->void { delete[] p; });
    a = SmtObj<int[]>(new int[4] { 1, 2, 3, 4 });

    a[0] = 12;

    std::cout << a[0] << "   " << a << "\n";

    a.reset();

    return 0;
}
