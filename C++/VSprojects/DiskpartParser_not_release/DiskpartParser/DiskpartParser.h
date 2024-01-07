#ifndef DISKPART_PARSER_H
#define DISKPART_PARSER_H

#include <iostream>

class DiskpartParser
{
private:
	static size_t GetFileSize(const char *file_name);

	static void ReadFile(const char *file_name, char *buffer, size_t buffer_size);

	static void DeleteFromString(char *src, size_t src_size, int symbols_count);

	static int DeleteFromStringUntil(char *src, size_t src_size, const char symbol);

	static void DeleteFromStringBefore(char *src, size_t src_size, const char *segment);

	static void ChangeSegment(char *src, size_t src_size, const char *old_segment, const char *new_segment);

	static int ParseString(char *src, size_t src_size, const char stop_symbol, char *buffer, size_t buffer_size);

public:
	static void ParseVolumeList_Volume(const char *file_name, char *buffer, size_t buffer_size);
};

#endif