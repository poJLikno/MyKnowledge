#include <iostream>
#include <string>
#include <thread>
#include "NetSockets/NetSockets.h"
#include "Window/Window.h"
#include "FileManager/FileManager.h"
#include "KeyboardListener/KeyboardListener.h"
#include "ConfigManager/ConfigManager.h"

#include "GlobalVariables.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    try
    {
        // Variables
        std::string ip = "";
        char remoteResolution[20] = {};

        // Load config file
        try
        {
            ConfigManager::LoadConfig(ip);
        }
        catch (std::runtime_error e)
        {
            ConfigManager::CreateConfig("127.0.0.1;YY;", 13);
            throw std::runtime_error("Config file was created.");
        }

        // TCP
        tcpClient = new TCPClient(ip.c_str(), 8080);
        tcpClient->ConnectToServer();
        tcpClient->ReceiveData(remoteResolution, sizeof(remoteResolution));

        //Parse resolution
        ConfigManager::ParseResolution(remoteResolution, sizeof(remoteResolution), remoteResolutionX, remoteResolutionY);

        // Set coefficients
        cofx = (float)stoi(remoteResolutionX) / (float)winWidth;
        cofy = (float)stoi(remoteResolutionY) / (float)winHeight;

        // UDP
        udpClient = new UDPClient(ip.c_str(), 9090);
        if (imgThr)
            udpClient->SendData("start", 6);
        else
            udpClient->SendData("no", 3);

        // Create window
        window = new Window("ImageTranslator_client", "icon.ico", 100, 100, winWidth, winHeight);
        window->RunMessageLoop();
    }
    catch (std::runtime_error e)
    {
        MessageBox(NULL, e.what(), "Error", MB_OK);
    }

    return EXIT_SUCCESS;
}