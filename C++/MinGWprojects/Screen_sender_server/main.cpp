#include <iostream>
#include <fstream>
#include <io.h>
#include <winsock2.h>
#include <Windows.h>

using namespace std;

int main()//            SERVER
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2,2), &wsData);

    ofstream filew;
    ifstream filer;

    int fsize = 0;

    SOCKET servSocket;
    servSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servInfo;
    memset(&servInfo, 0, sizeof(servInfo));
    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(6372);

    bind(servSocket, (struct sockaddr *)&servInfo, sizeof(servInfo));
    listen(servSocket, 10);

    SOCKET clientSocket;

    clientSocket = accept(servSocket, NULL, NULL);

    cout << "Connect OK" << endl;

    //int jopa = 0;

    while (1/*jopa == 0*/)
    {
        //jopa++;
        int x1, y1, x2, y2, w, h;


        x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
        y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
        x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);

        w = x2 - x1;
        h = y2 - y1;

        HDC memDC = CreateCompatibleDC(GetDC(NULL));

        // Создание и частичное заполнение структуры формата

        BITMAPINFO BMI;
        BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BMI.bmiHeader.biWidth = w;
        BMI.bmiHeader.biHeight = h; // Отрицательное значение высоты, чтобы изображение не было перевёрнутым
        BMI.bmiHeader.biSizeImage = w * h * 3; // Ширина * Высота * Количество_цветов_на_пиксель
        BMI.bmiHeader.biCompression = BI_RGB;
        BMI.bmiHeader.biBitCount  = 24;
        BMI.bmiHeader.biPlanes = 1;

        DWORD ScreenshotSize;
        ScreenshotSize = BMI.bmiHeader.biSizeImage; // ScreenshotSize - глобальная переменная типа int, может меняться в ходе выполнения программы
        unsigned char *ImageBuffer; // Указатель на блок данных BGR, управляемый HBITMAP (да, именно BGR - не RGB)

        HBITMAP bitmap = CreateDIBSection(GetDC(NULL), &BMI,DIB_RGB_COLORS, (void**)&ImageBuffer, 0, 0);
        SelectObject(memDC, bitmap);
        BitBlt(memDC, 0, 0, w, h, GetDC(NULL), x1, y1, SRCCOPY);
        //BitBlt(dc, 0, 0, w, h, GetDC(NULL), x1, y1, SRCCOPY);

        BITMAPINFO bmi;
        memset(&bmi, 0, sizeof(BITMAPINFOHEADER));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biHeight = h;
        bmi.bmiHeader.biWidth =  w;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biSizeImage = w * h * 3;

        char *user = getenv("USERNAME");
        char *way = (char*)malloc(100);
        char *way2 = (char*)malloc(100);
        char *way3 = (char*)malloc(300);
        snprintf(way, 100, "C:\\Users\\%s\\Desktop\\screenshot.bmp", user);
        snprintf(way2, 100, "C:\\Users\\%s\\Desktop\\screenshot.jpg", user);
        snprintf(way3, 300, "cons_rcp.exe -s \"%s\" -o \"%s\"", way, way2);

        filew.open(way, ios_base::binary | ios_base::trunc);
        if (filew.is_open())
        {
            int nBitsOffset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        LONG lImageSize = w * h * 3 ;
        LONG lFileSize = nBitsOffset + lImageSize;
        BITMAPFILEHEADER bmfh;
        bmfh.bfType = 'B'+('M'<<8);
        bmfh.bfOffBits = nBitsOffset;
        bmfh.bfSize = lFileSize;
        bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

            filew.write((char*) &bmfh, sizeof(BITMAPFILEHEADER));
            filew.write((char*) &bmi, sizeof(BITMAPINFOHEADER));
            filew.write((char*)ImageBuffer, w * h * 3);
        }
        filew.close();

        DeleteDC(memDC);
        DeleteObject(bitmap);

        system(way3);
        printf("%s", way3);

        char *bytes;
        char bruf[1] = {0};

        filer.open(way2, ios_base::binary);
        if (filer.is_open())
        {
            filer.seekg(0, ios_base::end);
            fsize = filer.tellg();
            printf("%d\n", fsize);

            send(clientSocket, to_string(fsize).c_str(), 16, 0);

            bytes = new char[fsize];
            filer.seekg(0, ios_base::beg);
            filer.read(bytes, fsize);

            recv(clientSocket, (char*)bruf, 1, 0);

            send(clientSocket, (const char*)bytes, fsize, 0);
        }
        filer.close();

        //system("del /Q \"screenshot.bmp\"");
        //system("del /Q \"screenshot.jpg\"");
        free(way);
        free(way2);
        free(way3);

        delete[] bytes;
    }
    closesocket(servSocket);


    return 0;
}
