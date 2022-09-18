#include <iostream>
#include <string>

using namespace std;

void operations(string val);


int main()
{
	setlocale(LC_ALL, "Russian");

	cout << " ривые ручки продакшн представл€ют: \nDIY-CMD(winVersion-2.3)\n" << endl;
	while (1) {
		string command;
		cout << "DIY@cmd>>> ";
		cin >> command;
		cout << "" << endl;
		cin.ignore(32767, '\n');
		if (command == ("exit")) {
			break;
		}
		else {
			operations(command);
		}
	}

	return 0;
}

void operations(string val) {
	if (val == ("") || val == (" "));
	else if (val == ("clean")) {
		system("cls");
		cout << "" << endl;
	}
	else if (val == ("cmd")) {
		system("cmd");
		cout << "" << endl;
	}
	else if (val == ("diskpart")) {
		system("diskpart");
		cout << "" << endl;
	}
	else if (val == ("run")) {
		char symb = '\\';
		const char* nee = "\\\\";
		char possymb;
		string way;
		string name;
		cout << "enter way to file: ";
		getline(cin, way);
		cout << "" << endl;
		cout << "enter file name: ";
		getline(cin, name);
		for (int i = 0; i < way.length(); i++) {
			if (way[i] == symb) {
				way[i] = *nee;
			}
			else;
		}
		string buf = "start /D \"" + way + "\\" + "\" " + name;
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "" << endl;
	}
	else if (val == ("ipinfo")) {
		system("ipconfig /all");
		cout << "" << endl;
	}
	else if (val == ("wifilist")) {
		string name;
		system("netsh wlan show profile");
		cout << "" << endl;
		cout << "more details about: ";
		getline(cin, name);
		if (name == ("")) { cout << "" << endl; }
		else {
			string buf = "netsh wlan show profile name=\"" + name + "\" key=clear";
			const char* bufer = buf.c_str();
			cout << "" << endl;
			system(bufer);
			cout << "" << endl;
		}
	}
	else if (val == ("sysinfo")) {
		system("systeminfo");
		system("wmic baseboard list brief");
		system("winsat cpu Цv");
		system("wmic MEMORYCHIP get BankLabel, DeviceLocator, Capacity, Speed");
		system("wmic diskdrive get model, size");
		system("wmic logicaldisk get name, Size");
		system("wmic sounddev get Caption");
		system("wmic path win32_VideoController get name");
		system("wmic nic get caption");
		cout << "" << endl;
	}
	else if (val == ("soft")) {
		cout << "please wait...\n" << endl;
		system("wmic product get name");
	}
	else if (val == ("tslist")) {
		system("tasklist");
		cout << "" << endl;
	}
	else if (val == ("drivers")) {
		system("driverquery");
		cout << "" << endl;
	}
	else if (val == ("ping")) {
		string address;
		string myCount;
		cout << "enter address: ";
		getline(cin, address);
		cout << "" << endl;
		cout << "enter packeges count: ";
		getline(cin, myCount);
		string buf = "ping " + address + " -n " + myCount;
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "" << endl;
	}
	else if (val == ("tree")) {
		string way;
		cout << "enter way to folder: ";
		getline(cin, way);
		string buf = "tree \"" + way + "\" /f /a";
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "" << endl;
	}
	else if (val == ("addfolder")) {
		string name;
		string way;
		cout << "enter way for create: ";
		getline(cin, way);
		cout << "" << endl;
		cout << "enter name: ";
		getline(cin, name);
		cout << "" << endl;
		string buf = "mkdir \"" + way + "\\" + name + "\"";
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "process complete\n" << endl;
	}
	else if (val == ("addfile")) {
		string name;
		string way;
		cout << "enter way for create: ";
		getline(cin, way);
		cout << "" << endl;
		cout << "enter name: ";
		getline(cin, name);
		cout << "" << endl;
		cout << "(ctrl + z and enter to save)\nwrite text: " << endl;
		string buf = "copy con \"" + way + "\\" + name + "\"";
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "\nprocess complete\n" << endl;
	}
	else if (val == ("delfolder")) {
		string way;
		cout << "enter way for delete: ";
		getline(cin, way);
		cout << "" << endl;
		string buf = "rmdir /s \"" + way + "\"";
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "\nprocess complete\n" << endl;
	}
	else if (val == ("delfile")) {
		string way;
		cout << "enter way for delete: ";
		getline(cin, way);
		string buf = "del \"" + way + "\"";
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "\nprocess complete\n" << endl;
	}
	else if (val == ("content")) {
		string way;
		cout << "enter way to file: ";
		getline(cin, way);
		cout << "" << endl;
		cout << "Viewing: \n" << endl;
		string buf = "type \"" + way + "\"";
		const char* bufer = buf.c_str();
		system(bufer);
		cout << "\n" << endl;
	}
	else if (val == ("py3host")) {
		cout << "(ctrl + c) for close\n" << endl;
		system("python -m http.server");
		cout << "\n" << endl;
	}
	else cout << "unknown command\n" << endl;
}
