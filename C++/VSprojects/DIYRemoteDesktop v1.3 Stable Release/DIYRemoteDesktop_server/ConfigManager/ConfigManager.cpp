#include "ConfigManager.h"

uint16_t ConfigManager::Parse(uint16_t start, char *src, size_t edge, char key, std::string &buffer)
{
    for (uint16_t i = start; i < edge; i++)
    {
        if (src[i] == key)
        {
            return i;
        }
        buffer += src[i];
    }
    return 0;
}

void ConfigManager::LoadConfig(std::string &x, std::string &y, std::string &quality)
{
    // Variables
    char *buffer = nullptr;
    size_t buff_size = 0;

    // Read config
    buff_size = FileManager::GetFileSize("config.txt");
    buffer = new char[buff_size] {};
    FileManager::ReadFile("config.txt", buffer, buff_size);

    // Parse data
    uint16_t count = Parse(0, buffer, buff_size, 'x', x);
    count = Parse(count + 1, buffer, buff_size, ';', y);
    count = Parse(count + 1, buffer, buff_size, ';', quality);

    //Clean up
    ZeroMemory(buffer, buff_size);
    delete[] buffer;
    buffer = nullptr;
}

void ConfigManager::CreateConfig(const char *data, size_t size)
{
    FileManager::WriteFile("config.txt", (char *)data, size);
}
