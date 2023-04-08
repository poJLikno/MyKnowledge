#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include <Windows.h>

class FileManager
{
public:
	static size_t GetFileSize(const char *filename);

	static void WriteFile(const char *filename, char *data, size_t size);

	static void ReadFile(const char *filename, char *buffer, size_t size);
};

#endif