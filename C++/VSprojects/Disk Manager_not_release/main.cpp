#include "Window/Window.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	const char *app_name_version = "Disk Manager v0.1 beta";
	const char *app_class = "disk_manager_class";

	try
	{
        Window window(app_name_version, false, app_class, 100, 100, 800, 600);

		window.RunMessageLoop();
	}
	catch (std::runtime_error &e)
	{
		MessageBox(NULL, e.what(), "Error", MB_OK);
	}

	return EXIT_SUCCESS;
}