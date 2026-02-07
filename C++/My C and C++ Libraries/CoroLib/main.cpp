#include <iostream>

#include "CoroLib/CoroLib.h"

#include <windows.h>

MakeAsync<int> async_task;
MakeAsync<void> async_print;

MakeAsync<void> AsyncPrint()
{
    //throw std::exception("Except in coro #4");

    std::cout << "Async aloha!\n";

    co_return;
}

MakeAsync<int> AsyncTask()
{
    //throw std::exception("Except in coro #3");

    std::this_thread::sleep_for(std::chrono::seconds(3));

    co_return 0;
}

Task<int> SyncTask()
{
    //throw std::exception("Except in coro #2");

    std::this_thread::sleep_for(std::chrono::seconds(3));

    co_return 1;
}

Task<void> VoidTask()
{
    //throw std::exception("Except in coro #5");

    std::cout << "Sync aloha!\n";

    co_return;
}

std::thread new_thread;// = std::thread([]()->void {});;

Task<int> MainTask()
{
    std::cout << "coro start\n";

    async_print = AsyncPrint();
    co_await async_print;

    async_task = AsyncTask();
    int a = co_await async_task;
    std::cout << "coro in middle (" << a << ")\n";

    co_await SwitchCoroThread(new_thread);

    //throw std::exception("Except in coro #1");

    int b = co_await SyncTask();
    std::cout << "coro end (" << b << ")\n";

    co_await VoidTask();

    co_return -10;
}

inline bool was_pressed(int key_vcode)
{
    return GetAsyncKeyState(key_vcode) & (0x8000 | 0x0001);
}

inline void set_codepage(unsigned int codepage)
{
    SetConsoleCP(codepage);
    SetConsoleOutputCP(codepage);
}

int main(int argc, const char **argv)
{
    set_codepage(65001);

    try
    {
        Task<int> task = MainTask();
        task.Resume();

        was_pressed('X');/* Reset state */

        while (was_pressed('X') == false && task.Done() == false)
        {
            if (async_print.Exist() && async_print.ResultReady())
            {
                async_print.ResumePausedCoro();
            }
            if (async_task.Exist() && async_task.ResultReady())
            {
                async_task.ResumePausedCoro();
                //task.CheckException();
            }

            std::cout << "Some useful code\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    catch (const std::exception &error)
    {
        std::cout << "!!! " << error.what() << "\n";
    }

    if (new_thread.joinable())
    {
        new_thread.join();
    }

    std::cout << "exit\n";

    return 0;
}
