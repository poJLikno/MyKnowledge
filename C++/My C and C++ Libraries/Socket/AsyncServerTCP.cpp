#include <iostream>

#include "Socket/Socket.h"

#include "CoroLib.h"

class AsyncServerTCP
{
private:
    Socket _server;
    Socket _conn;

    MakeAsync<Socket> _async_accept_task;
    MakeAsync<Socket::Bytes> _async_recv_task;

    std::atomic<bool> _stop_token = false;

public:
    AsyncServerTCP(const Socket::Address &address);

    AsyncServerTCP(const AsyncServerTCP &) = delete;
    AsyncServerTCP(AsyncServerTCP &&) = delete;

    ~AsyncServerTCP() noexcept = default;

    Task<bool> Accept();
    Task<Socket::Bytes> Receive(int buffer_size);

    void CloseConnection();

    void Poll();

    bool StopToken() const { return _stop_token.load(std::memory_order::acquire); }

    void RequestStop();
};

Task<void> async_server_task(AsyncServerTCP &async_server)
{
    Socket::Bytes data;
    while (async_server.StopToken() == false && co_await async_server.Accept())
    {
        while ((data = co_await async_server.Receive(1024)))
        {
            std::cout << (std::string)data << "\n";
        }

        async_server.CloseConnection();
    }
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
        Socket win_sock_init;

        Socket::Address address(Socket::gethostbyname(Socket::gethostname()), 9091);
        const auto &[ip, port] = address;

        AsyncServerTCP async_server(address);
        std::cout << "Async Server TCP start (ip = " << ip << " : port = " << port << ")\n";

        Task<void> async_server_handler = async_server_task(async_server);
        async_server_handler.Resume();

        was_pressed('X');/* Reset state */

        while (async_server_handler.Done() == false)
        {
            std::cout << "Some useful code\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            if (was_pressed('X'))
            {
                async_server.RequestStop();
            }

            async_server.Poll();
        }
    }
    catch (const std::exception &error)
    {
        std::cout << "!!! " << error.what() << "\n";
    }

    std::cout << "exit\n";

    return 0;
}

/* AsyncServerTCP.cpp */
AsyncServerTCP::AsyncServerTCP(const Socket::Address &address)
    : _server(Socket::TCP)
{
    _server.Bind(address);
    _server.Listen(1);
}

Task<bool> AsyncServerTCP::Accept()
{
    _async_accept_task = [](Socket &server)->MakeAsync<Socket> { co_return server.Accept(); }(_server);
    _conn = co_await _async_accept_task;

    co_return true;
}

Task<Socket::Bytes> AsyncServerTCP::Receive(int buffer_size)
{
    _async_recv_task = [](Socket &conn, int buffer_size)->MakeAsync<Socket::Bytes> { co_return conn.Receive(buffer_size); }(_conn, buffer_size);

    co_return co_await _async_recv_task;
}

void AsyncServerTCP::CloseConnection()
{
    _conn.Close();
}

void AsyncServerTCP::Poll()
{
    if (_async_accept_task.Exist() && _async_accept_task.ResultReady())
    {
        _async_accept_task.ResumePausedCoro();
    }
    if (_async_recv_task.Exist() && _async_recv_task.ResultReady())
    {
        _async_recv_task.ResumePausedCoro();
    }
}

void AsyncServerTCP::RequestStop()
{
    _stop_token.store(true, std::memory_order_release);

    Socket im_conn;
    im_conn.Connect(_server.GetAddress());
    //im_conn.Shutdown(Socket::Write);
    im_conn.Close();
}
