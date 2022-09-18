#include <stdio.h>
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

SYSTEMTIME st1;
SYSTEMTIME st2;
ifstream settings;

bool attempt = 0;

int limHour = 0;
int limMinute = 0;

int timHour = 0;
int timMinute = 0;

void Tweaks();

DWORD WINAPI MyThread(LPVOID param);

int WINAPI WinMain(HINSTANCE hIstance, HINSTANCE prev, LPSTR lpCmdLine, int nCmdShow)//            SERVER debug - int main(){}
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);

    SOCKET servSocket;
    servSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servInfo;
    memset(&servInfo, 0, sizeof(servInfo));
    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(9070);//9080

    bind(servSocket, (struct sockaddr*)&servInfo, sizeof(servInfo));
    listen(servSocket, 10);

    int buf[1];
    memset(buf, 0, sizeof(buf));

    GetLocalTime(&st1);

    Tweaks();

    HANDLE mythread = CreateThread(NULL, 0, MyThread, NULL, 0, NULL);

    SOCKET clientSocket;
    while (clientSocket = accept(servSocket, NULL, NULL))
    {
        cout << "Connect OK" << endl;

        while (recv(clientSocket, (char*)buf, sizeof(buf), 0) > 0)
        {
            system("rundll32.exe user32.dll, LockWorkStation");
        }
    }
    closesocket(servSocket);
    CloseHandle(mythread);


    return 0;
}

DWORD WINAPI MyThread(LPVOID param)
{
    int lockHour = (st1.wHour + timHour > 23) ? st1.wHour + timHour - 24 : st1.wHour + timHour;
    int lockMinute = (st1.wMinute + timMinute > 59) ? st1.wMinute + timMinute - 60 : st1.wMinute + timMinute;

    while (1)
    {
        Sleep(1000);
        GetLocalTime(&st2);

        if (st2.wHour == limHour && st2.wMinute == limMinute && !attempt)
        {
            attempt = 1;
            system("rundll32.exe user32.dll, LockWorkStation");
        }
        else if (st2.wHour == lockHour && st2.wMinute == lockMinute && st2.wSecond == st1.wSecond && attempt == 0)
        {
            system("rundll32.exe user32.dll, LockWorkStation");
        }
    }
}

void Tweaks()
{
    settings.open("settings.txt", ios_base::binary);
    if (settings.is_open())
    {
        int fsize;
        char* fdata;
        char tempHour[2];
        char tempMinute[2];
        char ttempHour[2];
        char ttempMinute[2];

        settings.seekg(0, ios_base::end);
        fsize = settings.tellg();
        settings.seekg(0, ios_base::beg);
        fdata = new char[fsize];
        settings.read(fdata, fsize);

        for (int i = 0; i < fsize; i++)
        {
            if (fdata[i] == ':')
            {
                limHour = atoi(tempHour);
                int m = 0;
                for (int n = i + 1; n < fsize; n++)
                {
                    if (fdata[n] == '\n')
                    {
                        limMinute = atoi(tempMinute);
                        int k = 0;
                        for (int j = n + 1; j < fsize; j++)
                        {
                            if (fdata[j] == ':')
                            {
                                timHour = atoi(ttempHour);
                                int g = 0;
                                for (int l = j + 1; l < fsize; l++)
                                {
                                    if (fdata[l] == ';')
                                    {
                                        timMinute = atoi(ttempMinute);
                                        break;
                                    }
                                    ttempMinute[g] = fdata[l];
                                    g++;
                                }
                                break;
                            }
                            ttempHour[k] = fdata[j];
                            k++;
                        }
                        break;
                    }
                    tempMinute[m] = fdata[n];
                    m++;
                }
                break;
            }
            tempHour[i] = fdata[i];
        }

        delete[] fdata;
    }
    settings.close();

}
