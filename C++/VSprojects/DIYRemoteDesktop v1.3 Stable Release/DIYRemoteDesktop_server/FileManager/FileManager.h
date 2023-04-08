#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include "../ImageManager/ImageManager.h"
#include <Windows.h>
#include <Gdiplus.h>

class FileManager
{
private:
	static int GetEncoderClsid(const WCHAR *format, CLSID *pClsid);

	static void HbitmapToJPEGImage(HBITMAP &bmp, const wchar_t *fileName, ULONG quality);

public:
	static size_t GetFileSize(const char *filename);

	static void WriteFile(const char *filename, char *data, size_t size);

	static void ReadFile(const char *filename, char *buffer, size_t size);

	static void SaveScreenshot(std::string &x, std::string &y, std::string &quality);
};

#endif