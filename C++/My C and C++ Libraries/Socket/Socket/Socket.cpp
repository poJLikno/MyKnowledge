#include "Socket.h"

#ifdef _WIN32
unsigned long long Socket::_windows_sockets_users = 0;
std::mutex Socket::_windows_sockets_mutex;

void Socket::_InitWindowsSockets()
{
    /* Lock mutex */
    std::lock_guard<std::mutex> lock_mutex(_windows_sockets_mutex);

    /* Initialize Windows Sockets */
    if (_windows_sockets_users == 0)
    {
        WSADATA windows_sockets_data = {};

        int error_code = WSAStartup(MAKEWORD(2, 2), &windows_sockets_data);
        if (error_code > 0)
        {
            /* Auto mutex unlock */
            throw Socket::Error("Couldn't initialize Windows Sockets!", std::to_string(error_code).c_str());
        }
    }

    _windows_sockets_users += 1;
    /* Auto mutex unlock */
}

void Socket::_CleanUpWindowsSockets() noexcept
{
    /* Lock mutex */
    std::lock_guard<std::mutex> lock_mutex(_windows_sockets_mutex);

    /* Clean up Windows Sockets */
    _windows_sockets_users -= 1;

    if (_windows_sockets_users == 0)
    {
        WSACleanup();/* error if < 0 */
    }

    /* Auto mutex unlock */
}
#endif /* _WIN32 */

Socket::Socket(char empty_byte)
{
#ifdef _WIN32
    _InitWindowsSockets();
#endif /* _WIN32 */
}

Socket::Socket(Socket::Protocol protocol)
{
#ifdef _WIN32
    _InitWindowsSockets();
#endif /* _WIN32 */

    /* Create scoket */
    _socket_info.sin_family = AF_INET;

    _socket = socket(AF_INET, (protocol == Socket::Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM), protocol);
    if (_socket == ~0)/* ~0 instead of -1 (SOCKET is unsigned in windows) */
    {
        throw Socket::Error("Couldn't create a listen socket!");
    }
}

Socket::Socket(Socket &&socket) noexcept
{
#ifdef _WIN32
    /* Increase Windows Sockets counter */
    {
        /* Lock mutex */
        std::lock_guard<std::mutex> lock_mutex(_windows_sockets_mutex);

        _windows_sockets_users += 1;
        /* Auto mutex unlock */
    }
#endif

    *this = std::move(socket);
}

Socket::~Socket() noexcept
{
    try
    {
        Socket::Close();
    }
    catch (...) {}

#ifdef _WIN32
    _CleanUpWindowsSockets();
#endif /* _WIN32 */
}

void Socket::Bind(const Address &address)
{
    const auto &[host, port] = address;

    _socket_info.sin_addr = (host.length() > 0 ? Socket::inet_aton(Socket::gethostbyname(host)) : in_addr{ INADDR_ANY });
    _socket_info.sin_port = htons(port);

    if (bind(_socket, reinterpret_cast<const sockaddr *>(&_socket_info), sizeof(_socket_info)) < 0)
    {
        throw Socket::Error("Couldn't bind a listen socket!");
    }
}

void Socket::Listen(int conn_queue)
{
    if (listen(_socket, conn_queue) < 0)
    {
        throw Socket::Error("Couldn't start listening port!");
    }
}

Socket Socket::Accept()
{
    Socket connection_socket(SOCKET_NO_INIT);
    socklen_t socket_info_size = sizeof(connection_socket._socket_info);

    connection_socket._socket = accept(_socket, reinterpret_cast<sockaddr *>(&connection_socket._socket_info), &socket_info_size);
    if (connection_socket._socket == ~0)
    {
        throw Error("Couldn't accept connection!");
    }

    return connection_socket;
}

void Socket::Connect(const Address &address)
{
    const auto &[host, port] = address;

    _socket_info.sin_addr = Socket::inet_aton(Socket::gethostbyname(host));
    _socket_info.sin_port = htons(port);

    if (connect(_socket, reinterpret_cast<const sockaddr *>(&_socket_info), sizeof(_socket_info)) < 0)
    {
        throw Socket::Error("Couldn't establish connection!");
    }
}

Socket::Bytes Socket::Receive(int buffer_size, int flags)
{
    if (buffer_size <= 0)
    {
        throw Socket::Error("Couldn't receive a data to invalid buffer!");
    }

    std::vector<char> buffer(buffer_size);

    /*
    // > 0 -> bytes were read
    // == 0 -> shutdown conn (Write)
    // < 0 -> error
    */
    int bytes_read = recv(_socket, buffer.data(), static_cast<int>(buffer.size()), flags);
    if (bytes_read < 0)
    {
        throw Socket::Error("Couldn't receive a data!");
    }

    buffer.resize(bytes_read);

    return Bytes(std::move(buffer));
}

std::pair<Socket::Bytes, Socket::Address> Socket::ReceiveFrom(int buffer_size, int flags)
{
    if (buffer_size <= 0)
    {
        throw Socket::Error("Couldn't receive a data from special address to invalid buffer!");
    }

    std::vector<char> buffer(buffer_size);

    sockaddr_in sender_info = {};
    socklen_t sender_info_size = sizeof(sender_info);

    /*
    // > 0 -> bytes were read
    // == 0 -> shutdown conn (Write)
    // < 0 -> error
    */
    int bytes_read = recvfrom(_socket, buffer.data(), static_cast<int>(buffer.size()), flags, reinterpret_cast<sockaddr *>(&sender_info), &sender_info_size);
    if (bytes_read < 0)
    {
        throw Socket::Error("Couldn't receive a data from special address!");
    }

    buffer.resize(bytes_read);

    return { Bytes(std::move(buffer)), Address(Socket::inet_ntoa(sender_info.sin_addr), ntohs(sender_info.sin_port)) };
}

int Socket::Send(Socket::BytesPtr bytes_ptr, int flags)
{
    if (bytes_ptr == false)
    {
        throw Socket::Error("Couldn't send a invalid data!");
    }

    int bytes_written = send(_socket, bytes_ptr.Data(), bytes_ptr.Size(), flags);
    if (bytes_written < 0)
    {
        throw Socket::Error("Couldn't send a data!");
    }

    return bytes_written;
}

int Socket::SendTo(Socket::BytesPtr bytes_ptr, int flags, const Socket::Address &address)
{
    if (bytes_ptr == false)
    {
        throw Socket::Error("Couldn't send a invalid data to special address!");
    }

    const auto &[host, port] = address;

    sockaddr_in host_info = {};
    host_info.sin_family = AF_INET;
    host_info.sin_addr = Socket::inet_aton(Socket::gethostbyname(host));
    host_info.sin_port = htons(port);

    int bytes_written = sendto(_socket, bytes_ptr.Data(), bytes_ptr.Size(), flags, reinterpret_cast<const sockaddr *>(&host_info), sizeof(host_info));
    if (bytes_written < 0)
    {
        throw Socket::Error("Couldn't send a data to special address!");
    }

    return bytes_written;
}

void Socket::Shutdown(ShutdownHow how)
{
    if (shutdown(_socket, how) < 0)
    {
        throw Socket::Error("Couldn't shutdown socket!");
    }
}

void Socket::Close()
{
    if (_socket == 0)
    {
        return;
    }

#ifdef _WIN32
    int result = closesocket(_socket);

#else
    int result = close(_socket);
#endif /* _WIN32 */

    _socket_info = {};
    _socket = 0;

    if (result < 0)
    {
        throw Socket::Error("Couldn't close a socket!");
    }
}

/* Helpers */
in_addr Socket::inet_aton(const std::string &ip_string)
{
    in_addr address_big_endian = {};

    int result = inet_pton(AF_INET, ip_string.c_str(), &address_big_endian);
    if (result < 0)
    {
        throw Socket::Error("Couldn't transform invalid address family string to packed address!");
    }
    else if (result == 0)
    {
        throw Socket::Error("Couldn't transform invalid string to packed address!", "None");
    }

    return address_big_endian;
}

std::string Socket::inet_ntoa(in_addr address_big_endian)
{
    char ip_string[16] = {};

    if (inet_ntop(AF_INET, &address_big_endian, ip_string, sizeof(ip_string)) == nullptr)
    {
        throw Socket::Error("Couldn't transform packed address to string!");
    }

    return ip_string;
}

std::string Socket::gethostname()
{
    char hostname[512] = {};

    if (::gethostname(hostname, sizeof(hostname)) < 0)
    {
        throw Socket::Error("Couldn't get a host name for local machine!");
    }

    return std::string(hostname);
}

std::string Socket::gethostbyname(const std::string &name)
{
    addrinfo address_hints = {};
    address_hints.ai_family = AF_INET;

    addrinfo *address_list = nullptr;

    int result = getaddrinfo(name.c_str(), "0", &address_hints, &address_list);
    if (result != 0)
    {
        throw Socket::Error("Couldn't get the host info!", std::to_string(result).c_str());
    }

    std::string host_address;

    if (isalpha(name[0]) == 0)
    {
        host_address = name;
    }
    else
    {
        /* list order is reversed, if compare with ::gethostbyname list */
        host_address = inet_ntoa(reinterpret_cast<sockaddr_in *>(address_list->ai_addr)->sin_addr);
    }

    /* Clean up */
    freeaddrinfo(address_list);
    address_list = nullptr;

    return host_address;

    // need #define _WINSOCK_DEPRECATED_NO_WARNINGS
    /*hostent *host_info = ::gethostbyname(name.c_str());
    if (host_info == nullptr)
    {
        throw Socket::Error("Couldn't get the host info!");
    }

    if (isalpha(name[0]) == 0)
    {
        return name;
    }

    for (int i = 0; ; ++i)
    {
        if (host_info->h_addr_list[i] == nullptr)
        {
            if (i == 0)
            {
                throw Socket::Error("Couldn't find IP address of host!", "None");
            }

            return inet_ntoa(*reinterpret_cast<in_addr *>(host_info->h_addr_list[i - 1]));
        }
    }*/
}
