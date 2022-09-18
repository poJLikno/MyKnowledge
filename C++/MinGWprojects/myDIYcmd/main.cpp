#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

char command[301];
char *user = getenv("USERNAME");

bool same(char sample[]);
void operations();

int main()
{
    printf("Crazy hands present...\nDIY-CMD(winVersion - 3.0)");

	while (1)
    {
        memset(command, 0, sizeof(command));

		printf("\n%s@DIY_cmd-> ", user);
		scanf("%s", command);
        if (same("exit")) break;
		else operations();
	}


	return 0;
}

bool same(char sample[])
{
    bool answer = 1;
    for (int i = 0; i < sizeof(sample) / 2; i++)
    {
        if (!answer) break;
        answer = (command[i] == sample[i]) ? 1 : 0;
    }
    return answer;
}

void operations()
{
	if (same("clean"))
    {
		system("cls");
		printf("Ugly hands present...\nDIY-CMD(winVersion - 3.0)");
	}
	else if (same("cmd"))
	{
        printf("\n");
		system("cmd");
	}
	else if (same("diskpart")) system("diskpart");
	else if (same("run"))
	{
	    char way[1001];
	    char name[1001];
	    char buf[2002];
        printf("enter way to file: ");
        scanf("%s", way);
        printf("enter file name: ");
        scanf("%s", name);
		snprintf(buf, 2002, "start /D \"%s\\\" %s", &way, &name);
		system(buf);
	}
	else if (same("ipinfo")) system("ipconfig /all");
	else if (same("con_list"))
    {
        char name[301];
	    char buf[2002];
		system("netsh wlan show profile");
        printf("more details about: ");
        scanf("%s", name);
		if (name[0] == 'c' && name[1] == 'a' && name[2] == 'n' && name[3] == 'c' && name[4] == 'e' && name[5] == 'l');
		else
        {
            snprintf(buf, 2002, "netsh wlan show profile name=\"%s\" key=clear", name);
			system(buf);
		}
	}
	else if (same("sysinfo"))
    {
		system("systeminfo");
		system("wmic baseboard list brief");
		system("winsat cpu –v");
		system("wmic MEMORYCHIP get BankLabel, DeviceLocator, Capacity, Speed");
		system("wmic diskdrive get model, size");
		system("wmic logicaldisk get name, Size");
		system("wmic sounddev get Caption");
		system("wmic path win32_VideoController get name");
		system("wmic nic get caption");
	}
	else if (same("soft"))
    {
		printf("please wait...\n");
		system("wmic product get name");
	}
	else if (same("ts_list"))
	{
		system("tasklist");
	}
	else if (same("drivers"))
	{
		system("driverquery");
	}
	else if (same("ping"))
	{
	    char address[501];
	    char packcount[501];
	    char buf[2002];
		printf("enter address: ");
		scanf("%s", address);
		printf("enter count of packeges: ");
		scanf("%s", packcount);
		snprintf(buf, 2002, "ping %s -n %s", address, packcount);
		system(buf);
	}
	else if (same("tree"))
    {
		char way[501];
		char buf[2002];
		printf("enter way to folder: ");
		scanf("%s", way);
		printf("\n");
        snprintf(buf, 2002, "tree \"%s\" /f /a", way);
		system(buf);
	}
	else if (same("add_folder"))
    {
		char way[501];
		char buf[2002];
        printf("enter way & name to create folder: ");
		scanf("%s", way);
		snprintf(buf, 2002, "mkdir \"%s\"", way);
		system(buf);
		printf("process complete...\n");
	}
	else if (same("add_file"))
    {
		char way[501];
		char buf[2002];
        printf("enter way & name to create file: ");
		scanf("%s", way);
		printf("(ctrl + z and enter to save)\nwrite text: ");
        snprintf(buf, 2002, "copy con \"%s\"", way);
		system(buf);
		printf("process complete...\n");
	}
	else if (same("del_folder"))
    {
		char way[501];
		char buf[2002];
        printf("enter way of folder to delete: ");
		scanf("%s", way);
        snprintf(buf, 2002, "rmdir /s \"%s\"", way);
		system(buf);
		printf("process complete...\n");
	}
	else if (same("del_file"))
    {
		char way[501];
		char buf[2002];
        printf("enter way of file to delete: ");
		scanf("%s", way);
        snprintf(buf, 2002, "del \"%s\"", way);
		system(buf);
		printf("process complete...\n");
	}
	else if (same("content"))
	{
		char way[501];
		char buf[2002];
        printf("enter way to file: ");
		scanf("%s", way);
        printf("Viewing: \n\n");
        snprintf(buf, 2002, "type \"%s\"", way);
		system(buf);
	}
	else printf("unknown command\n");
}
