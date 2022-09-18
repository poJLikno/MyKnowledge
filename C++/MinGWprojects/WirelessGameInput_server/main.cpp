#include <iostream>
#include <math.h>
#include <Windows.h>
#include <winsock2.h>

using namespace std;

int main()//            SERVER
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2,2), &wsData);

    system("ipconfig");
    cout << "" << endl;
    cout << "Server ready\n" << endl;

    SOCKET servSocket;
    servSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servInfo;
    memset(&servInfo, 0, sizeof(servInfo));
    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(8000);

    bind(servSocket, (struct sockaddr *)&servInfo, sizeof(servInfo));
    listen(servSocket, 10);

    int codes[101] = {0x01, 0x02, 0x04, 0x08, 0x09, 0x0D, 0x10, 0x11, 0x12, 0x14, 0x1B, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x2C, 0x2D, 0x2E, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0xC0, 0xBD, 0xBB, 0xDB, 0xDD, 0xBA, 0xDE, 0xDC, 0xBC, 0xBE, 0xBF, 0x5B, 0x5C, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x90, 0x91, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E};

    LPPOINT point;
    point = (LPPOINT)malloc(sizeof(*point));

    int buf[106];
    memset(&buf, 0, sizeof(buf));

    int lbuf[104];
    memset(&lbuf, 0, sizeof(lbuf));

    SOCKET clientSocket;

    while (clientSocket = accept(servSocket, NULL, NULL))
    {
        cout << "Connect OK\n" << endl;

        while(recv(clientSocket, (char*)buf, sizeof(buf), 0) > 0)
        {
            for (int i = 3; i < 101; i++)
            {
                if (buf[i] == 1 && lbuf[i] != buf[i])
                {
                    keybd_event(codes[i], MapVirtualKey(codes[i], 0), 0, 0);
                    lbuf[i] = buf[i];
                }
                else if (buf[i] == 0 && lbuf[i] != buf[i])
                {
                    keybd_event(codes[i], MapVirtualKey(codes[i], 0), KEYEVENTF_KEYUP, 0);
                    lbuf[i] = buf[i];
                }
            }

            if (buf[0] == 1 && lbuf[0] != buf[0])
            {
                GetCursorPos(point);
                mouse_event(MOUSEEVENTF_LEFTDOWN, point[0].x, point[0].y, 0, 0);
                lbuf[0] = buf[0];
            }
            else if (buf[0] == 0 && lbuf[0] != buf[0])
            {
                GetCursorPos(point);
                mouse_event(MOUSEEVENTF_LEFTUP, point[0].x, point[0].y, 0, 0);
                lbuf[0] = buf[0];
            }

            if (buf[1] == 1 && lbuf[1] != buf[1])
            {
                GetCursorPos(point);
                mouse_event(MOUSEEVENTF_RIGHTDOWN, point[0].x, point[0].y, 0, 0);
                lbuf[1] = buf[1];
            }
            else if (buf[1] == 0 && lbuf[1] != buf[1])
            {
                GetCursorPos(point);
                mouse_event(MOUSEEVENTF_RIGHTUP, point[0].x, point[0].y, 0, 0);
                lbuf[1] = buf[1];
            }

            if (buf[2] == 1 && lbuf[2] != buf[2])
            {
                GetCursorPos(point);
                mouse_event(MOUSEEVENTF_MIDDLEDOWN, point[0].x, point[0].y, 0, 0);
                lbuf[2] = buf[2];
            }
            else if (buf[2] == 0 && lbuf[2] != buf[2])
            {
                GetCursorPos(point);
                mouse_event(MOUSEEVENTF_MIDDLEUP, point[0].x, point[0].y, 0, 0);
                lbuf[2] = buf[2];
            }

            if (buf[102] != lbuf[102] || buf[103] != lbuf[103])
            {
                //SetCursorPos(round(buf[25]*1.5), round(buf[26]*1.35));
                mouse_event(MOUSEEVENTF_MOVE, buf[102] - buf[104], buf[103] - buf[105], 0, 0);

                lbuf[102] = buf[102];
                lbuf[103] = buf[103];
            }

            if (buf[101] > 0)
            {
                mouse_event(MOUSEEVENTF_WHEEL, point[0].x, point[0].y, 120, 0);
            }
            else if (buf[101] < 0)
            {
                mouse_event(MOUSEEVENTF_WHEEL, point[0].x, point[0].y, -120, 0);
            }
        }
    }
    closesocket(servSocket);


    return 0;
}
