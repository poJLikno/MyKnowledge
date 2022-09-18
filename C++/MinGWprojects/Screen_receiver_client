#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <windows.h>
#include <fstream>

using namespace std;

int main()//            CLIENT
{
    char *ip;
    int fsize = 0;
    ifstream filer;
    ofstream filew;
    filer.open("configs.txt", ios_base::binary);
    if (filer.is_open())
    {
        filer.seekg(0, ios_base::end);
        fsize = filer.tellg();
        ip = new char[fsize];
        filer.seekg(0, ios_base::beg);
        filer.read(ip, fsize);
    }
    else
    {
        filew.open("configs.txt", ios_base::binary | ios_base::trunc);
        if (filew.is_open())
        {
            filew.write("Enter server's IP", 17);
            MessageBox(NULL, "Server's IP wasn't found.\nMight it wasn't entered in \"configs.txt\" file.\nCheck it.", "Error", MB_OK);
            return 0;
        }
        filew.close();
    }
    filer.close();

    WSADATA wsData;
    WSAStartup(MAKEWORD(2,2), &wsData);
    //char ip[20] = "127.0.0.1";

    ofstream file;

    SOCKET netSocket;
    netSocket = socket(AF_INET, SOCK_STREAM, 0);

    HOSTENT *host = gethostbyname(ip);

    delete[] ip;

    struct sockaddr_in netInfo;
    ZeroMemory(&netInfo, sizeof(netInfo));
    netInfo.sin_family = AF_INET;
    netInfo.sin_port = htons(6372);
    memcpy(&netInfo.sin_addr.S_un.S_addr, host -> h_addr_list[0], sizeof(netInfo.sin_addr.S_un.S_addr));

    connect(netSocket, (struct sockaddr *)&netInfo, sizeof(netInfo));

    //WSAEventSelect(netSocket, 0, FD_READ);

    cout << "Connect OK" << endl;

    while (1)
    {
        char fsize[16];
        char *buf;
        char bruf[1] = {1};
        printf("start\n");

        recv(netSocket, (char*)fsize, 16, 0);

        int nsize = atoi(fsize);
        printf("%d\n", nsize);
        //system("pause");
        buf = new char[nsize];

        send(netSocket, (const char*)bruf, 1, 0);

        recv(netSocket, (char*)buf, nsize, 0);

        //printf("sfsdfdadag\n");

        char *user = getenv("USERNAME");
        char *way = (char*)malloc(100);
        //char *way2 = (char*)malloc(100);
        //char *way3 = (char*)malloc(300);
        snprintf(way, 100, "C:\\Users\\%s\\Desktop\\screenshot_recived.jpg", user);
        //snprintf(way2, 100, "C:\\Users\\%s\\Desktop\\picture.bmp", user);
        //snprintf(way3, 300, "cons_rcp.exe -s \"%s\" -o \"%s\" -resize 1280x800px qh", way, way2);

        file.open(way, ios_base::binary | ios_base::trunc);
        if (file.is_open())
        {
            file.write(buf, (int)nsize);
        }
        file.close();

        delete[] buf;

        //system(way3);
        //printf("%s\n", way3);

        free(way);
        //free(way2);
        //free(way3);
    }
    closesocket(netSocket);


    return 0;
}
