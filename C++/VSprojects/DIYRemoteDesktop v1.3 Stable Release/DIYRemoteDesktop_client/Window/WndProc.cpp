#include "../NetSockets/NetSockets.h"
#include "../FileManager/FileManager.h"
#include "../KeyboardListener/KeyboardListener.h"
#include "Window.h"
#include <Windowsx.h>

extern uint32_t winWidth, winHeight;
extern UDPClient *udpClient;
extern TCPClient *tcpClient;
extern bool imgThr, inpThr;
extern std::string remoteResolutionX, remoteResolutionY;
extern float cofx, cofy;
extern KeyboardListener kbl;

PAINTSTRUCT ps;
ULONG_PTR gdiplusToken;

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    try
    {
        if (message == WM_CREATE)
        {
            //GDI+
            Gdiplus::GdiplusStartupInput gdiplusStartupInput;
            GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

            SetTimer(hWnd, 1, 10, NULL);
            result = 1;
        }
        else
        {
            if (message == WM_TIMER)
            {
                InvalidateRect(hWnd, NULL, FALSE);
                result = 0;
            }
            else if (message == WM_SIZE)
            {
                winWidth = LOWORD(lParam);
                winHeight = HIWORD(lParam);

                cofx = (float)stoi(remoteResolutionX) / (float)winWidth;
                cofy = (float)stoi(remoteResolutionY) / (float)winHeight;
                result = 0;
            }
            // Mouse events
            if (message == WM_LBUTTONDOWN)
            {
                tcpClient->SendData("lbtndown", 9);
            }
            else if (message == WM_LBUTTONUP)
            {
                tcpClient->SendData("lbtnup", 7);
            }
            else if (message == WM_RBUTTONDOWN)
            {
                tcpClient->SendData("rbtndown", 9);
            }
            else if (message == WM_RBUTTONUP)
            {
                tcpClient->SendData("rbtnup", 7);
            }
            else if (message == WM_MBUTTONDOWN)
            {
                tcpClient->SendData("mbtndown", 9);
            }
            else if (message == WM_MBUTTONUP)
            {
                tcpClient->SendData("mbtnup", 7);
            }
            else if (message == WM_MOUSEWHEEL)
            {
                int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
                char res[20] = {};
                snprintf(res, sizeof(res), "wheel%d", zDelta);

                tcpClient->SendData(res, sizeof(res));
            }
            else if (message == WM_MOUSEMOVE)
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                char res[20] = {};
                snprintf(res, sizeof(res), "move%d:%d", int(cofx * (float)xPos), int(cofy * (float)yPos));

                tcpClient->SendData(res, sizeof(res));
            }
            // Mouse events end
            else if (message == WM_ACTIVATE)
            {
                if (inpThr)
                {
                    uint32_t val = (uint32_t)wParam;
                    if (val > 0)
                        kbl.StartListenKeyboard();
                    else
                        kbl.StopListenKeyboard();
                }
                result = 0;
            }
            else if (message == WM_PAINT)
            {
                if (imgThr)
                {
                    try
                    {
                        // Buffers
                        char *buffer = nullptr;
                        char imgSize[16] = {};

                        // Receive image size
                        udpClient->ReceiveData(imgSize, sizeof(imgSize));
                        buffer = new char[atoi(imgSize)];

                        // Receive file
                        udpClient->ReceiveData(buffer, atoi(imgSize));
                        FileManager::WriteFile("image.jpg", buffer, atoi(imgSize));

                        // Draw image
                        ps.hdc = BeginPaint(hWnd, &ps);

                        Gdiplus::Graphics graphics(ps.hdc);
                        Gdiplus::Image image(L"image.jpg");
                        graphics.DrawImage(&image, 0, 0, winWidth, winHeight);

                        EndPaint(hWnd, &ps);

                        // Clean up
                        ZeroMemory(buffer, atoi(imgSize));
                        delete[] buffer;
                        buffer = nullptr;
                    }
                    catch (std::runtime_error e)
                    {
                        //MessageBox(NULL, e.what(), "Error", MB_OK);
                    }
                }
                result = 0;
            }
            else if (message == WM_KEYDOWN)
            {
                if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
                result = 0;
            }
            else if (message == WM_CLOSE)
            {
                DestroyWindow(hWnd);
                result = 0;
            }
            else if (message == WM_DESTROY)
            {
                delete tcpClient;
                tcpClient = nullptr;

                Sleep(1000);

                delete udpClient;
                udpClient = nullptr;

                KillTimer(hWnd, 1);
                Gdiplus::GdiplusShutdown(gdiplusToken);
                PostQuitMessage(0);
                result = 1;
            }
            else result = DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    catch (std::runtime_error e)
    {
        MessageBox(NULL, e.what(), "Error", MB_OK);
    }
    
    return result;
}