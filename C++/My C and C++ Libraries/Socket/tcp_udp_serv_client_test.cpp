#include <iostream>
#include <chrono>
#include <thread>

#include "Socket/Socket.h"

#include <mutex>

class safe_ostream
{
private:
    std::mutex _mtx;

public:
    safe_ostream() = default;
    safe_ostream(const safe_ostream &) = delete;
    safe_ostream(safe_ostream &&) = delete;

    ~safe_ostream() = default;

    template<typename T>
    safe_ostream &operator<<(const T &obj)
    {
        _mtx.lock();
        std::cout << obj;
        _mtx.unlock();

        return *this;
    }
};

safe_ostream thread_cout;

inline bool was_pressed(int key_vcode)
{
    return GetAsyncKeyState(key_vcode) & (0x8000 | 0x0001);
};

void tcp_server_handler(int key_vcode)
{
    try
    {
        Socket listener(Socket::TCP);

        const auto &host_name = Socket::gethostname();
        const auto &ip = Socket::gethostbyname(host_name);

        listener.Bind({ ip, 9091});
        listener.Listen(1);

        thread_cout << "TCP Server ON (host name = " << host_name << " : IP = " << ip << "), key = " << static_cast<char>(key_vcode) << "\n";

        was_pressed(key_vcode);/* Clear async state */

        Socket conn;
        while (was_pressed(key_vcode) == 0 && (conn = listener.Accept()))
        {
            const auto &[client_host, client_port] = conn.GetAddress();
            thread_cout << "Server thread: Connection established (client : ip = " << client_host << " : port = " << client_port << ")\n";

            Socket::Bytes data;
            while ((data = conn.Receive(1024)))
            {
                thread_cout << "Server thread: " << static_cast<std::string>(data) << "\n";
            }

            conn.Send("Last shutdown message");

            thread_cout << "Shutdown connection\n";
            conn.Shutdown(Socket::Write);

            thread_cout << "Close connection\n";
            conn.Close();
        }

        thread_cout << "Server OFF\n";
    }
    catch (const std::exception &error)
    {
        thread_cout << "*** - Server thread - " << error.what() << "\n";
    }
}

void tcp_client_handler(int thread_id, int key_vcode)
{
    /* Client */
    try
    {
        thread_cout << "Create new TCP client (" << thread_id << "), key = " << static_cast<char>(key_vcode) << "\n";

        Socket conn(Socket::TCP);
        conn.Connect({ Socket::gethostname(), 9091});
        thread_cout << "Client (" << thread_id << ") connection pass!\n";

        was_pressed(key_vcode);/* Clear async state */
        do
        {
            conn.Send(std::string("Aloha! (" + std::to_string(thread_id) + std::string(")")));
            conn.Send({"abcde", 3});

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } while (was_pressed(key_vcode) == 0);

        thread_cout << "Shutdown client (" << thread_id << ")\n";
        conn.Shutdown(Socket::Write);

        Socket::Bytes last_msg;
        while ((last_msg = conn.Receive(1024)))
        {
            thread_cout << "Client thread (" << thread_id << "): " << static_cast<std::string>(last_msg) << "\n";
        }

        thread_cout << "Close client (" << thread_id << ")\n";
        conn.Close();
    }
    catch (const std::exception &error)
    {
        thread_cout << "*** - Client thread (" << thread_id << ") - " << error.what() << "\n";
    }
}

int tcp_main(int argc, const char **argv)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif /* _WIN32 */

    std::jthread server_thread(tcp_server_handler, 'X');

    std::vector<std::jthread> client_threads;

    was_pressed('Z');
    while (was_pressed('Z') == 0)
    {
        if (was_pressed('Y'))
        {
            auto clients_num = client_threads.size();
            client_threads.push_back(std::jthread(tcp_client_handler, static_cast<int>(clients_num + 1), static_cast<int>('A' + clients_num)));
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}

/* ------------------------------------------------------------- */

void udp_server_handler(int key_vcode)
{
    try
    {
        Socket server(Socket::UDP);

        const auto &host_name = Socket::gethostname();
        const auto &ip = Socket::gethostbyname(host_name);

        server.Bind({ ip, 9091});

        thread_cout << "UDP Server ON (host name = " << host_name << " : IP = " << ip << "), key = " << static_cast<char>(key_vcode) << "\n";

        was_pressed(key_vcode);/* Clear async state */

        while (was_pressed(key_vcode) == 0)
        {
            const auto &[data, addr] = server.ReceiveFrom(1024);
            if (data == false)
            {
                break;
            }

            const auto &[client_host, client_port] = addr;
            thread_cout << "Server thread: " << static_cast<std::string>(data) << " (From client : ip = " << client_host << " : port = " << client_port << ")\n";

            //conn.Send("Last shutdown message");

            //thread_cout << "Shutdown connection\n";
            //conn.Shutdown(Socket::Write);
        }

        server.Close();
        thread_cout << "Server OFF\n";
    }
    catch (const std::exception &error)
    {
        thread_cout << "*** - Server thread - " << error.what() << "\n";
    }
}

void udp_client_handler(int thread_id, int key_vcode)
{
    /* Client */
    try
    {
        thread_cout << "Create new UDP client (" << thread_id << "), key = " << static_cast<char>(key_vcode) << "\n";

        Socket conn(Socket::UDP);
        Socket::Address dst_addr = { Socket::gethostname(), 9091};

        was_pressed(key_vcode);/* Clear async state */
        do
        {
            conn.SendTo(std::string("Aloha! (" + std::to_string(thread_id) + std::string(")")), dst_addr);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } while (was_pressed(key_vcode) == 0);

        /*thread_cout << "Shutdown client (" << thread_id << ")\n";
        conn.Shutdown(Socket::Write);

        Socket::Bytes last_msg;
        while (last_msg = conn.Receive(1024))
        {
            thread_cout << "Client thread (" << thread_id << "): " << static_cast<const std::string &>(last_msg) << "\n";
        }*/

        thread_cout << "Close client (" << thread_id << ")\n";
        conn.Close();
    }
    catch (const std::exception &error)
    {
        thread_cout << "*** - Client thread (" << thread_id << ") - " << error.what() << "\n";
    }
}

int udp_main(int argc, const char **argv)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif /* _WIN32 */

    //std::jthread server_thread(udp_server_handler, 'X');

    std::vector<std::jthread> client_threads;

    was_pressed('Z');
    while (was_pressed('Z') == 0)
    {
        if (was_pressed('Y'))
        {
            auto clients_num = client_threads.size();
            client_threads.push_back(std::jthread(udp_client_handler, static_cast<int>(clients_num + 1), static_cast<int>('A' + clients_num)));
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
