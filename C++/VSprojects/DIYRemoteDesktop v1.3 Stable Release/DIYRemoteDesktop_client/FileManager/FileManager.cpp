#include "FileManager.h"

size_t FileManager::GetFileSize(const char *filename)
{
    std::ifstream file;
    size_t fsize = 0;

    file.open(filename, std::ios_base::binary | std::ios_base::in);
    if (file.is_open())
    {
        file.seekg(0, std::ios_base::end);
        fsize = file.tellg();
    }
    else
    {
        file.close();
        throw std::runtime_error("Can't open file!\n");
    }

    file.close();

    return fsize;
}

void FileManager::WriteFile(const char *filename, char *data, size_t size)
{
    std::ofstream file;

    file.open(filename, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
    if (file.is_open())
    {
        file.write(data, size);
    }
    else
    {
        file.close();
        throw std::runtime_error("Can't open file!\n");
    }

    file.close();
}

void FileManager::ReadFile(const char *filename, char *buffer, size_t size)
{
    std::ifstream file;

    file.open(filename, std::ios_base::binary | std::ios_base::in);
    if (file.is_open())
    {
        file.read(buffer, size);
    }
    else
    {
        file.close();
        throw std::runtime_error("Can't open file!\n");
    }

    file.close();
}