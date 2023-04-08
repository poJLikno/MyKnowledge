#include <iostream>
#include <thread>
#include <string>
#include "NetSockets/NetSockets.h"
#include "FileManager/FileManager.h"
#include "ConfigManager/ConfigManager.h"
#include "ImageManager/ImageManager.h"
#include "ControlDevices/ControlDevices.h"
#include <Windows.h>
#include <Gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

ULONG_PTR gdiplusToken;

int main(int argc, const char *argv[])
{
	try
	{
		//Variables
		std::string resolutionX = "",
			resolutionY = "",
			quality = "";

		bool connectionFlag = false;
		char *data = nullptr, buff[16] = {};

		// Load config file
		try
		{
			ConfigManager::LoadConfig(resolutionX, resolutionY, quality);
			std::cout << "Image resolution: " << resolutionX << 'x' << resolutionY << '\n' << "Image quality: " << quality << "%\n";
		}
		catch (std::runtime_error e)
		{
			ConfigManager::CreateConfig("1920x1080;10;", 13);
			throw std::runtime_error("Config file was created.");
		}

		// Initialize GDI+
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		// Initialization
		std::cout << "Start working...\n";

		// UDP
		UDPServer udpServer(9090);
		udpServer.BindSocket();

		// TCP
		TCPServer tcpServer(8080);
		tcpServer.BindSocket();
		tcpServer.ListenPort();

		// Input thread
		std::thread inputThread([&]
			{
				char keyCode[20] = {};
				ControlDevices controlDevices;

				while (tcpServer.AcceptConnection())
				{
					std::cout << "TCP connected\n";
					connectionFlag = true;

					// Send screen resolution
					char resolution[20];
					snprintf(resolution, sizeof(resolution), "%dx%d", stoi(resolutionX), stoi(resolutionY));
					tcpServer.SendData(resolution, sizeof(resolution));

					// Receiving loop
					while (tcpServer.ReceiveData(keyCode, sizeof(keyCode)) > 0)
					{
						std::cout << keyCode << '\n';
						controlDevices(keyCode);
						ZeroMemory(keyCode, sizeof(keyCode));
					}

					std::cout << "TCP disconnected\n";
					connectionFlag = false;
				}
			});
		inputThread.detach();

		// Main loop
		while (true)
		{
			udpServer.ReceiveData(buff, sizeof(buff));
			std::string bu(buff);
			std::cout << "UDP connected\n" << bu << '\n';
			ZeroMemory(buff, sizeof(buff));

			// Send image
			while (connectionFlag)
			{
				if (bu == std::string("start"))
				{
					size_t fileSize = 0;
					
					// Get screen
					FileManager::SaveScreenshot(resolutionX, resolutionY, quality);

					// Get image
					fileSize = FileManager::GetFileSize("image.jpg");
					data = new char[fileSize] {};
					FileManager::ReadFile("image.jpg", data, fileSize);

					// Send image
					udpServer.SendData(std::to_string(fileSize).c_str(), 16);
					udpServer.SendData(data, fileSize);

					// Clean up
					ZeroMemory(data, fileSize);
					delete[] data;
					data = nullptr;
				}
			}
			
			std::cout << "UDP disconnected\n";
		}

		// Clean up
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}

	return EXIT_SUCCESS;
}