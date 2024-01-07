#include "DiskpartParser.h"

void DiskpartParser::ParseVolumeList_Volume(const char *file_name, char *buffer, size_t buffer_size)
{
    size_t buff_size = GetFileSize(file_name);
    char *buff = new char[buff_size];
    char *sub_buff = new char[buff_size];
    if (buff && sub_buff)
    {
        // First
        memset(buff, 0, buff_size);
        ReadFile(file_name, buff, buff_size);
        DeleteFromStringBefore(buff, buff_size, "\r\n");
        ChangeSegment(buff, buff_size, "\r\n", "  ");
        DeleteFromStringUntil(buff, buff_size, ' ');
        //std::cout << buff << "\r\n\r\n\r\n";
        for (int i = 0; i < 5; i++)
        {
            int deleted_stop_symbols_count = 0;

            // Volume
            memset(sub_buff, 0, buff_size);
            deleted_stop_symbols_count = ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            // Letter
            memset(sub_buff, 0, buff_size);
            if (deleted_stop_symbols_count <= 5)
            {
                deleted_stop_symbols_count = ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            }
            else
            {
                DeleteFromStringUntil(buff, buff_size, ' ');
                snprintf(sub_buff, buff_size, "None");
            }
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            // Label
            memset(sub_buff, 0, buff_size);
            if (deleted_stop_symbols_count <= 3)
            {
                ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            }
            else
            {
                DeleteFromStringUntil(buff, buff_size, ' ');
                snprintf(sub_buff, buff_size, "None");
            }
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            // File system
            memset(sub_buff, 0, buff_size);
            ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            // Type
            memset(sub_buff, 0, buff_size);
            ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            // Size
            memset(sub_buff, 0, buff_size);
            ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            // Status
            memset(sub_buff, 0, buff_size);
            deleted_stop_symbols_count = ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            // Info
            memset(sub_buff, 0, buff_size);
            if (deleted_stop_symbols_count <= 5)
            {
                ParseString(buff, buff_size, ' ', sub_buff, buff_size);
            }
            else
            {
                DeleteFromStringUntil(buff, buff_size, ' ');
                snprintf(sub_buff, buff_size, "None");
            }
            std::cout << sub_buff << "     ";
            //std::cout << buff << "\r\n\r\n\r\n";

            system("pause");

            std::cout << "\r\n\r\n";
        }

        // ------
        // Check buff[~] == ' ' ? Param = ' ' : ParseString(); 
        // ------

        // Clean up
        delete[] sub_buff;
        sub_buff = nullptr;

        delete[] buff;
        buff = nullptr;
    }
    else
    {
        throw std::runtime_error("Can't create buff!\r\n");
    }
}
