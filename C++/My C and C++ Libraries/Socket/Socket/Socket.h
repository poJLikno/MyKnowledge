#ifndef SOCKET_LIB_H_
#define SOCKET_LIB_H_

#define SOCKET_LIB_VERSION "v1.0.0"

#define SOCKET_NO_INIT ((char)'\0')

#include <vector>
#include <string.h>
#include <string>
#include <utility>
#include <exception>

#ifdef _WIN32
/* first sockets-h, then windows-h */
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <mutex>

#pragma comment(lib, "ws2_32.lib")

#else
/* libs for unix */
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

typedef int SOCKET;

//#define INVALID_SOCKET (~0)/* ~0 instead of -1 (SOCKET is unsigned in windows) */
//#define SOCKET_ERROR (-1)
#endif /* _WIN32 */

class Socket
{
private:
#ifdef _WIN32
    static unsigned long long _windows_sockets_users;
    static std::mutex _windows_sockets_mutex;

    void _InitWindowsSockets();
    void _CleanUpWindowsSockets() noexcept;
#endif /* _WIN32 */

    sockaddr_in _socket_info = {};
    SOCKET _socket = 0;

public:
    class BytesPtr
    {
    private:
        const char *_bytes = nullptr;
        const int _size = 0;

    public:
        BytesPtr(const std::vector<char> &vector)
            : _bytes(vector.data()), _size(static_cast<const int>(vector.size()))
        {
        }

        BytesPtr(const std::string &string)
            : _bytes(string.c_str()), _size(static_cast<const int>(string.length()))
        {
        }

        BytesPtr(const char *string)
            : _bytes(string), _size(static_cast<const int>(strlen(string)))
        {
        }

        BytesPtr(const char *bytes, const int length)
            : _bytes(bytes), _size(length)
        {
        }

        BytesPtr(const BytesPtr &bytes_ptr) noexcept
            : _bytes(bytes_ptr._bytes), _size(bytes_ptr._size)
        {
        }

        BytesPtr(BytesPtr &&) = delete;

        ~BytesPtr() = default;

        operator bool() const
        {
            return _size > 0 && _bytes != nullptr;
        }

        const char *Data() const
        {
            return _bytes;
        }
        int Size() const
        {
            return _size;
        }
    };

    class Bytes
    {
    private:
        std::vector<char> _bytes;

    public:
        Bytes() = default;

        Bytes(std::vector<char> vector)
        {
            _bytes = std::move(vector);
        }
        /*Bytes(const std::vector<char> &vector)
        {
            _bytes = vector;
        }
        Bytes(std::vector<char> &&vector)
        {
            _bytes = std::move(vector);
        }*/

        Bytes(const std::string &string)
        {
            _bytes = std::vector<char>(string.begin(), string.end());
        }
        Bytes(const char *string)
        {
            for (int i = 0; string[i] != '\0'; ++i)
            {
                _bytes.push_back(string[i]);
            }
        }
        Bytes(const char *bytes, int length)
        {
            for (int i = 0; i < length; ++i)
            {
                _bytes.push_back(bytes[i]);
            }
        }

        Bytes(const Bytes &bytes) noexcept
        {
            *this = bytes;
        }
        Bytes(Bytes &&bytes) noexcept
        {
            *this = std::move(bytes);
        }

        ~Bytes() = default;

        Bytes &operator=(const Bytes &bytes) noexcept
        {
            if (this == &bytes)
            {
                return *this;
            }

            _bytes = bytes._bytes;

            return *this;
        }
        Bytes &operator=(Bytes &&bytes) noexcept
        {
            if (this == &bytes)
            {
                return *this;
            }

            _bytes = std::move(bytes._bytes);

            return *this;
        }

        operator std::string() const
        {
            return std::string(_bytes.begin(), _bytes.end());
        }
        operator bool() const
        {
            return _bytes.size() > 0;
        }

        std::vector<char> &Vector()
        {
            return _bytes;
        }
        const std::vector<char> &Vector() const
        {
            return _bytes;
        }

        const char *Data() const
        {
            return _bytes.data();
        }
        int Size() const
        {
            return static_cast<int>(_bytes.size());
        }
    };

    class Error : public std::exception
    {
    private:
        std::string _error;

    public:
        Error() = default;
        Error(const char *error_text, const char *error_code)
            : _error(error_text)
        {
            _error += " -> Error code: ";
            _error += error_code;
        }
        Error(const char *error_text)
            : _error(error_text)
        {
#ifdef _WIN32
            _error += " -> Windows Sockets Error code: ";
            _error += std::to_string(WSAGetLastError());
#else
            _error += " -> Error code: ";
            _error += std::to_string(errno);
#endif /* _WIN32 */
        }
        Error(const Error &error) noexcept
        {
            *this = error;
        }
        Error(Error &&error) = delete;

        ~Error() override {};

        Error &operator=(const Error &error) noexcept
        {
            if (this == &error)
            {
                return *this;
            }

            _error = error._error;

            return *this;
        }

        const char *what() const override
        {
            return _error.c_str();
        }
    };

    /* (host, port) */
    using Address = std::pair<std::string, unsigned short>;

    enum Protocol { TCP = IPPROTO_TCP, UDP = IPPROTO_UDP };

#ifdef _WIN32
    enum ShutdownHow { Read = SD_RECEIVE, Write = SD_SEND, ReadWrite = SD_BOTH };
#else
    enum ShutdownHow { Read = SHUT_RD, Write = SHUT_WR, ReadWrite = SHUT_RDWR };
#endif /* _WIN32 */

    Socket(char empty_byte);
    Socket(Socket::Protocol protocol = Socket::Protocol::TCP);
    Socket(const Socket &) = delete;
    Socket(Socket &&socket) noexcept;

    ~Socket() noexcept;

    Socket &operator=(Socket &&socket) noexcept
    {
        if (this == &socket)
        {
            return *this;
        }

        std::swap(_socket_info, socket._socket_info);
        std::swap(_socket, socket._socket);

        return *this;
    }

    /* --- Server --- */

    void Bind(const Socket::Address &address);
    void Listen(int conn_queue = SOMAXCONN);/* [For TCP only] */
    /* Returns connection socket [For TCP only] */
    Socket Accept();

    /* --- Client [for TCP ony] --- */

    void Connect(const Address &address);

    /* --- Shared --- */

    /* Returns a byte buffer, the size of which is equal to the number of bytes received */
    Socket::Bytes Receive(int buffer_size, int flags = 0);/* [For TCP only] */
    /* Returns a byte buffer, the size of which is equal to the number of bytes received */
    std::pair<Socket::Bytes, Socket::Address> ReceiveFrom(int buffer_size, int flags = 0);

    /* Returns the number of bytes sent */
    int Send(Socket::BytesPtr bytes_ptr, int flags = 0);/* [For TCP only] */
    /* Returns the number of bytes sent */
    int SendTo(Socket::BytesPtr bytes_ptr, int flags, const Socket::Address &address);
    /* Returns the number of bytes sent */
    int SendTo(Socket::BytesPtr bytes_ptr, const Socket::Address &address)
    {
        return SendTo(bytes_ptr, 0, address);
    }

    void Shutdown(ShutdownHow how);/* [For TCP only] */
    void Close();

    Socket::Address GetAddress() const
    {
        Address address = {};
        auto &[host, port] = address;

        host = Socket::inet_ntoa(_socket_info.sin_addr);
        port = ntohs(_socket_info.sin_port);

        return address;
    }
    const sockaddr_in &GetInfo() const
    {
        return _socket_info;
    }
    SOCKET GetHandle() const
    {
        return _socket;
    }

    operator bool() const
    {
        return _socket > 0;
    }

    /* Helpers */
    static in_addr inet_aton(const std::string &ip_string);
    static std::string inet_ntoa(in_addr address_big_endian);
    /* Returns standart host name of local machine */
    static std::string gethostname();
    /* Returns last record from IP address list of host, or return "name" if it is IPv4 address */
    static std::string gethostbyname(const std::string &name);
};

#endif /* SOCKET_LIB_H_ */
