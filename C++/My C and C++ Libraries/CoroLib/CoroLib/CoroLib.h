#ifndef CORO_LIB_H_
#define CORO_LIB_H_

#define CORO_LIB_VERSION "v1.0.0"

#include <coroutine>
#include <exception>
#include <thread>
#include <atomic>
#include <optional>
#include <variant>

/*
* Simple universal coroutine object
*/
template<typename T>
class Task
{
public:
    class promise_type;

private:
    std::coroutine_handle<promise_type> _coro;

    Task(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

public:
    class promise_type
    {
    private:
        std::coroutine_handle<> _paused_coro;
        std::optional<std::variant<T, std::exception_ptr>> _result;

    public:
        auto get_return_object()
        {
            return Task<T>(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        std::suspend_always initial_suspend() { return {}; }

        auto final_suspend() noexcept
        {
            class final_awaiter
            {
            public:
                bool await_ready() noexcept { return false; }
                std::coroutine_handle<> await_suspend(std::coroutine_handle<promise_type> coro) noexcept
                {
                    auto paused_coro = coro.promise()._paused_coro;
                    if (paused_coro)
                    {
                        return paused_coro;
                    }

                    return std::noop_coroutine();
                }
                void await_resume() noexcept {}
            };

            return final_awaiter();
        }

        void unhandled_exception() { _result = std::current_exception(); }
        void return_value(T value) { _result = std::move(value); }

        friend class Task<T>;
    };

    auto operator co_await()
    {
        class awaiter
        {
        private:
            std::coroutine_handle<promise_type> _coro;

        public:
            awaiter(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

            bool await_ready() { return false; }

            std::coroutine_handle<> await_suspend(std::coroutine_handle<> paused_coro)
            {
                _coro.promise()._paused_coro = paused_coro;

                return _coro;
            }
            T await_resume()
            {
                std::optional<std::variant<T, std::exception_ptr>> &opt = _coro.promise()._result;
                T *result = std::get_if<T>(&opt.value());
                if (result)
                {
                    return std::move(*result);
                }

                std::rethrow_exception(std::get<std::exception_ptr>(opt.value()));
            }
        };

        return awaiter(_coro);
    }

    Task() = default;

    Task(const Task &) = delete;
    Task(Task &&task) noexcept { *this = std::move(task); };

    ~Task() noexcept
    {
        if (_coro)
        {
            _coro.destroy();
        }
    }

    Task &operator=(Task &&task) noexcept
    {
        if (this != &task)
        {
            std::swap(_coro, task._coro);
        }

        return *this;
    }

    void CheckException() const
    {
        if (_coro && _coro.done())
        {
            std::optional<std::variant<T, std::exception_ptr>> &opt = _coro.promise()._result;
            std::exception_ptr *except = std::get_if<std::exception_ptr>(&opt.value());
            if (except)
            {
                std::rethrow_exception(*except);
            }
        }
    }

    bool Exist() const
    {
        Task<T>::CheckException();

        return (bool)_coro;
    }

    bool Done() const
    {
        if (Task<T>::Exist() == false)
        {
            throw std::logic_error("Task<T>::Done() failed! -> Coroutine doesn't exist.");
        }

        return _coro.done();
    }

    void Resume() const
    {
        if (Task<T>::Done())
        {
            throw std::logic_error("Task<T>::Resume() failed! -> Coroutine is done.");
        }

        _coro.resume();
    }

    T Result() const
    {
        if (Task<T>::Done() == false)
        {
            throw std::logic_error("Task<T>::Result() failed! -> Coroutine has not finished its work yet.");
        }

        std::optional<std::variant<T, std::exception_ptr>> &opt = _coro.promise._result;
        return std::get<T>(opt.value());
    }
};

/* See template class description */
template<>
class Task<void>
{
public:
    class promise_type;

private:
    std::coroutine_handle<promise_type> _coro;

    Task(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

public:
    class promise_type
    {
    private:
        std::coroutine_handle<> _paused_coro;
        std::optional<std::exception_ptr> _exception;

    public:
        auto get_return_object()
        {
            return Task<void>(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        std::suspend_always initial_suspend() { return {}; }

        auto final_suspend() noexcept
        {
            class final_awaiter
            {
            public:
                bool await_ready() noexcept { return false; }
                std::coroutine_handle<> await_suspend(std::coroutine_handle<promise_type> coro) noexcept
                {
                    auto paused_coro = coro.promise()._paused_coro;
                    if (paused_coro)
                    {
                        return paused_coro;
                    }

                    return std::noop_coroutine();
                }
                void await_resume() noexcept {}
            };

            return final_awaiter();
        }

        void unhandled_exception() { _exception = std::current_exception(); }
        void return_void() {}

        friend class Task<void>;
    };
    
    auto operator co_await()
    {
        class awaiter
        {
        private:
            std::coroutine_handle<promise_type> _coro;

        public:
            awaiter(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

            bool await_ready() { return false; }
            std::coroutine_handle<> await_suspend(std::coroutine_handle<> paused_coro)
            {
                _coro.promise()._paused_coro = paused_coro;

                return _coro;
            }
            void await_resume()
            {
                auto &except = _coro.promise()._exception;
                if (except)
                {
                    std::rethrow_exception(except.value());
                }
            }
        };

        return awaiter(_coro);
    }

    Task() = default;

    Task(const Task &) = delete;
    Task(Task &&task) noexcept { *this = std::move(task); };

    ~Task() noexcept
    {
        if (_coro)
        {
            _coro.destroy();
        }
    }

    Task &operator=(Task &&task) noexcept
    {
        if (this != &task)
        {
            std::swap(_coro, task._coro);
        }

        return *this;
    }

    void CheckException() const
    {
        if (_coro && _coro.done())
        {
            auto &except = _coro.promise()._exception;
            if (except)
            {
                std::rethrow_exception(except.value());
            }
        }
    }

    bool Exist() const
    {
        Task<void>::CheckException();

        return (bool)_coro;
    }

    bool Done() const
    {
        if (Task<void>::Exist() == false)
        {
            throw std::logic_error("Task<void>::Done() failed! -> Coroutine doesn't exist.");
        }

        return _coro.done();
    }

    void Resume() const
    {
        if (Task<void>::Done())
        {
            throw std::logic_error("Task<void>::Resume() failed! -> Coroutine is done.");
        }

        _coro.resume();
    }
};

/*
* This coroutine object allows to run any sync code in new thread (make operation async)
* Need to check operation state: (.Exist() && .ResultReady) => .ResumePausedCoro();
*/
template<typename T>
class MakeAsync
{
public:
    class promise_type;

private:
    std::coroutine_handle<promise_type> _coro;

    MakeAsync(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

public:
    class promise_type
    {
    private:
        std::coroutine_handle<> _paused_coro;
        std::optional<std::variant<T, std::exception_ptr>> _result;

        std::thread _thread;
        std::atomic<bool> _result_ready = false;

    public:
        MakeAsync<T> get_return_object()
        {
            return MakeAsync<T>(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        std::suspend_always initial_suspend() { return {}; }

        auto final_suspend() noexcept
        {
            class final_awaiter
            {
            public:
                bool await_ready() noexcept { return false; }
                void await_suspend(std::coroutine_handle<promise_type> coro) noexcept
                {
                    coro.promise()._result_ready.store(true, std::memory_order::release);
                }
                void await_resume() noexcept {}
            };

            return final_awaiter();
        }

        void unhandled_exception()
        {
            _result = std::current_exception();
        }

        void return_value(T value)
        {
            _result = std::move(value);
        }

        friend class MakeAsync<T>;
    };

    auto operator co_await()
    {
        class awaiter
        {
        private:
            std::coroutine_handle<promise_type> _coro;

        public:
            awaiter(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> paused_coro)
            {
                _coro.promise()._paused_coro = paused_coro;
                _coro.promise()._thread = std::thread([](auto coro)->void { coro.resume(); }, _coro);
            }
            T await_resume()
            {
                std::optional<std::variant<T, std::exception_ptr>> &opt = _coro.promise()._result;
                T *result = std::get_if<T>(&opt.value());
                if (result)
                {
                    return std::move(*result);
                }

                std::rethrow_exception(std::get<std::exception_ptr>(opt.value()));
            }
        };

        return awaiter(_coro);
    }

    MakeAsync() = default;
    MakeAsync(const MakeAsync &) = delete;
    MakeAsync(MakeAsync &&async_operation) noexcept { *this = std::move(async_operation); }

    ~MakeAsync() noexcept
    {
        if (_coro)
        {
            auto &thread = _coro.promise()._thread;
            if (thread.joinable())
            {
                thread.join();
            }

            _coro.destroy();
        }
    }

    MakeAsync &operator=(MakeAsync &&async_operation) noexcept
    {
        if (this != &async_operation)
        {
            std::swap(_coro, async_operation._coro);
        }

        return *this;
    }

    void CheckException() const
    {
        if (_coro && _coro.done())
        {
            std::optional<std::variant<T, std::exception_ptr>> &opt = _coro.promise()._result;
            std::exception_ptr *except = std::get_if<std::exception_ptr>(&opt.value());
            if (except)
            {
                std::rethrow_exception(*except);
            }
        }
    }

    bool Exist() const
    {
        MakeAsync<T>::CheckException();

        return (bool)_coro;
    }

    bool Done() const
    {
        if (MakeAsync<T>::Exist() == false)
        {
            throw std::logic_error("MakeAsync<T>::Done() failed! -> Coroutine doesn't exist.");
        }

        return _coro.done();
    }

    void Resume() const
    {
        if (MakeAsync<T>::Done())
        {
            throw std::logic_error("MakeAsync<T>::Resume() failed! -> Coroutine is done.");
        }

        _coro.promise()._thread = std::thread([](auto coro)->void { coro.resume(); }, _coro);
    }

    T Result() const
    {
        if (MakeAsync<T>::Done() == false)
        {
            throw std::logic_error("MakeAsync<T>::Result() failed! -> Coroutine has not finished its work yet.");
        }

        std::optional<std::variant<T, std::exception_ptr>> &opt = _coro.promise._result;
        return std::get<T>(opt.value());
    }

    bool ResultReady() const
    {
        if (MakeAsync<T>::Exist() == false)
        {
            throw std::logic_error("MakeAsync<T>::ResultReady() failed! -> Coroutine doesn't exist.");
        }

        return _coro.promise()._result_ready.load(std::memory_order::acquire);
    }

    void ResumePausedCoro() const
    {
        if (MakeAsync<T>::Exist() == false)
        {
            throw std::logic_error("MakeAsync<T>::ResumePausedCoro() failed! -> Coroutine doesn't exist.");
        }

        _coro.promise()._result_ready.store(false, std::memory_order::relaxed);

        auto paused_coro = _coro.promise()._paused_coro;
        if ((bool)paused_coro == false)
        {
            throw std::logic_error("MakeAsync<T>::ResumePausedCoro() failed! -> Paused coroutine doesn't exist.");
        }

        paused_coro.resume();
    }
};

/* See template class description */
template<>
class MakeAsync<void>
{
public:
    class promise_type;

private:
    std::coroutine_handle<promise_type> _coro;

    MakeAsync(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

public:
    class promise_type
    {
    private:
        std::coroutine_handle<> _paused_coro;
        std::optional<std::exception_ptr> _exception;

        std::thread _thread;
        std::atomic<bool> _result_ready = false;

    public:
        MakeAsync<void> get_return_object()
        {
            return MakeAsync<void>(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        std::suspend_always initial_suspend() { return {}; }

        auto final_suspend() noexcept
        {
            class final_awaiter
            {
            public:
                bool await_ready() noexcept { return false; }
                void await_suspend(std::coroutine_handle<promise_type> coro) noexcept
                {
                    coro.promise()._result_ready.store(true, std::memory_order::release);
                }
                void await_resume() noexcept {}
            };

            return final_awaiter();
        }

        void unhandled_exception()
        {
            _exception = std::current_exception();
        }

        void return_void() {}

        friend class MakeAsync<void>;
    };

    auto operator co_await()
    {
        class awaiter
        {
        private:
            std::coroutine_handle<promise_type> _coro;

        public:
            awaiter(std::coroutine_handle<promise_type> coro) : _coro(coro) {}

            bool await_ready() { return false; }
            void await_suspend(std::coroutine_handle<> paused_coro)
            {
                _coro.promise()._paused_coro = paused_coro;
                _coro.promise()._thread = std::thread([](auto coro)->void { coro.resume(); }, _coro);
            }
            void await_resume()
            {
                auto &except = _coro.promise()._exception;
                if (except)
                {
                    std::rethrow_exception(except.value());
                }
            }
        };

        return awaiter(_coro);
    }

    MakeAsync() = default;
    MakeAsync(const MakeAsync &) = delete;
    MakeAsync(MakeAsync &&async_operation) noexcept { *this = std::move(async_operation); }

    ~MakeAsync() noexcept
    {
        if (_coro)
        {
            auto &thread = _coro.promise()._thread;
            if (thread.joinable())
            {
                thread.join();
            }

            _coro.destroy();
        }
    }

    MakeAsync &operator=(MakeAsync &&async_operation) noexcept
    {
        if (this != &async_operation)
        {
            std::swap(_coro, async_operation._coro);
        }

        return *this;
    }

    void CheckException() const
    {
        if (_coro && _coro.done())
        {
            auto &except = _coro.promise()._exception;
            if (except)
            {
                std::rethrow_exception(except.value());
            }
        }
    }

    bool Exist() const
    {
        MakeAsync<void>::CheckException();

        return (bool)_coro;
    }

    bool Done() const
    {
        if (MakeAsync<void>::Exist() == false)
        {
            throw std::logic_error("MakeAsync<void>::Done() failed! -> Coroutine doesn't exist.");
        }

        return _coro.done();
    }

    void Resume() const
    {
        if (MakeAsync<void>::Done())
        {
            throw std::logic_error("MakeAsync<void>::Resume() failed! -> Coroutine is done.");
        }

        _coro.promise()._thread = std::thread([](auto coro)->void { coro.resume(); }, _coro);
    }

    bool ResultReady() const
    {
        if (MakeAsync<void>::Exist() == false)
        {
            throw std::logic_error("MakeAsync<void>::ResultReady() failed! -> Coroutine doesn't exist.");
        }

        return _coro.promise()._result_ready.load(std::memory_order::acquire);
    }

    void ResumePausedCoro() const
    {
        if (MakeAsync<void>::Exist() == false)
        {
            throw std::logic_error("MakeAsync<void>::ResumePausedCoro() failed! -> Coroutine doesn't exist.");
        }

        _coro.promise()._result_ready.store(false, std::memory_order::relaxed);

        auto paused_coro = _coro.promise()._paused_coro;
        if ((bool)paused_coro == false)
        {
            throw std::logic_error("MakeAsync<void>::ResumePausedCoro() failed! -> Paused coroutine doesn't exist.");
        }

        paused_coro.resume();
    }
};

/* This awaitable class allows to switch coroutine's thread */
class SwitchCoroThread
{
private:
    std::thread &_new_thread;

public:
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> coro)
    {
        if (_new_thread.joinable())
        {
            throw std::logic_error("Couldn't switch coroutine's thread! -> Target thread has already initialized.");
        }

        _new_thread = std::thread([coro]()->void { coro.resume(); });
    }
    void await_resume() {}

    SwitchCoroThread(std::thread &new_thread) : _new_thread(new_thread) {}

    SwitchCoroThread(const SwitchCoroThread &) = delete;
    SwitchCoroThread(SwitchCoroThread &&) = delete;

    ~SwitchCoroThread() noexcept = default;
};

#endif/* CORO_LIB_H_ */
