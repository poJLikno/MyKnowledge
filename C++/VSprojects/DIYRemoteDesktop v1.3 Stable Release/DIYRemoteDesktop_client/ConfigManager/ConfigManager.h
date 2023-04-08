#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "../FileManager/FileManager.h"

class ConfigManager
{
private:
	static uint16_t Parse(uint16_t start, char *src, size_t edge, char key, std::string &buffer);

public:
	static void LoadConfig(std::string &ip);

	static void CreateConfig(const char *data, size_t size);

	static void ParseResolution(char *src, size_t src_size, std::string &x, std::string &y);
};

#endif