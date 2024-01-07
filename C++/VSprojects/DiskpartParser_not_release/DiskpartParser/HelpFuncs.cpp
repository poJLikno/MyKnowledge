#include "DiskpartParser.h"
#include <fstream>

size_t DiskpartParser::GetFileSize(const char *file_name)
{
    std::ifstream file;
    size_t file_size = 0;

    file.open(file_name, std::ios_base::binary | std::ios_base::in);
    if (file.is_open())
    {
        file.seekg(0, std::ios_base::end);
        file_size = file.tellg();
    }
    else
    {
        throw std::runtime_error("Can't open file!\r\n");
    }

    file.close();

    return file_size;
}

void DiskpartParser::ReadFile(const char *file_name, char *buffer, size_t buffer_size)
{
    std::ifstream file;
    file.open(file_name, std::ios_base::binary | std::ios_base::in);
    if (file.is_open())
    {
        file.read(buffer, buffer_size);
    }
    else
    {
        throw std::runtime_error("Can't open file!\r\n");
    }
    file.close();
}

void DiskpartParser::DeleteFromString(char *src, size_t src_size, int symbols_count)
{
    char *tmp = new char[src_size];
    if (tmp)
    {
        memset(tmp, 0, src_size);
        memcpy(tmp, &src[symbols_count], size_t(src_size - symbols_count));

        memset(src, 0, src_size);
        memmove(src, tmp, src_size);

        memset(tmp, 0, src_size);

        delete[] tmp;
        tmp = nullptr;
    }
}

int DiskpartParser::DeleteFromStringUntil(char *src, size_t src_size, const char symbol)
{
    int symbols_count = 0;
    for (int i = 0; i < src_size; i++)
    {
        if (src[i] == symbol) symbols_count++;
        else break;
    }

    if (symbols_count)
    {
        DeleteFromString(src, src_size, symbols_count);
    }

    return symbols_count;
}

void DiskpartParser::DeleteFromStringBefore(char *src, size_t src_size, const char *segment)
{
    for (int symbols_count = 0; symbols_count < src_size; symbols_count++)
    {
        int flag = 1;
        flag = memcmp(&src[symbols_count], segment, strlen(segment));
        if (!flag)
        {
            DeleteFromString(src, src_size, symbols_count);
            break;
        }
    }
}

void DiskpartParser::ChangeSegment(char *src, size_t src_size, const char *old_segment, const char *new_segment)
{
    for (size_t i = 0; i < src_size; i++)
    {
        int flag = 1;
        flag = memcmp(&src[i], old_segment, strlen(old_segment));
        if (!flag)
        {
            memcpy(&src[i], new_segment, strlen(new_segment));
        }
    }
}

int DiskpartParser::ParseString(char *src, size_t src_size, const char stop_symbol, char *buffer, size_t buffer_size)
{
    int deleted_stop_symbols_count = 0;
    int symbols_count = 0;
    for (symbols_count = 0; symbols_count < buffer_size; symbols_count++)
    {
        if (src[symbols_count] == stop_symbol
            && src[symbols_count + 1] == stop_symbol)
        {
            break;
        }
        buffer[symbols_count] = src[symbols_count];
    }

    DeleteFromString(src, src_size, symbols_count);
    deleted_stop_symbols_count = DeleteFromStringUntil(src, src_size, stop_symbol);

    return deleted_stop_symbols_count;
}