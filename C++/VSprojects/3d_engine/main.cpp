#include "Window/Window.h"

#include "Settings/WindowSettings.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	try
	{
		Window window("3d_engine", WinPosX, WinPosY, WinWidth, WinHeight);
		window.RunMessageLoop();
	}
	catch (std::runtime_error e)
	{
		MessageBox(NULL, e.what(), "Error", MB_OK);
	}

	return EXIT_SUCCESS;
}