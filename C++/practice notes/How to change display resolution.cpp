void ChangeResolution()
{
	DEVMODE dm;
    dm.dmSize = sizeof(DEVMODE);
    int index = 0;
    while (EnumDisplaySettings(NULL, index, &dm))
    {
        if (dm.dmPelsWidth == screen_width && dm.dmPelsHeight == screen_height)
        {
            dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
            LONG result = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);

            if (result == DISP_CHANGE_SUCCESSFUL) break;
            else if (result == DISP_CHANGE_RESTART)
            {
                MessageBox(NULL, "Restart is reqired", "Error", MB_OK);
                break;
            }
            else
            {
                MessageBox(NULL, "Resolution isn't suppored", "Error", MB_OK);
                break;
            }
        }
        index++;
    }
}