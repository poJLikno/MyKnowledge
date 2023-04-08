#include "ControlDevices.h"

bool ControlDevices::Contains(std::string main_str, std::string part_str)
{
    if (main_str.size() >= part_str.size())
    {
        for (size_t i = 0; i < main_str.size(); i++)
        {
            if (i + part_str.size() <= main_str.size())
            {
                for (size_t j = 0; j < part_str.size(); j++)
                {
                    if (main_str.at(i + j) != part_str.at(j))
                        break;
                    else if (main_str.at(i + part_str.size() - 1) == part_str.at(part_str.size() - 1))
                        return true;
                }
            }
        }
    }

    return false;
}

void ControlDevices::operator()(char *buffer)
{
    str = buffer;
    if (str == lbtndown_str)
    {
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
    }
    else if (str == lbtnup_str)
    {
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
    }
    else if (str == rbtndown_str)
    {
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
    }
    else if (str == rbtnup_str)
    {
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
    }
    else if (str == mbtndown_str)
    {
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, point.x, point.y, 0, 0);
    }
    else if (str == mbtnup_str)
    {
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_MIDDLEUP, point.x, point.y, 0, 0);
    }
    else if (Contains(str, wheel_str))
    {
        str.erase(0, 5);
        std::cout << str << '\n';
        GetCursorPos(&point);
        mouse_event(MOUSEEVENTF_WHEEL, point.x, point.y, (DWORD)std::stoi(str), 0);
    }
    else if (Contains(str, move_str))
    {
        str.erase(0, 4);
        std::cout << str << '\n';
        auto x = [&]()
        {
            std::string x = "";
            for (size_t i = 0; i < str.size(); i++)
            {
                if (str.at(i) == ':')
                {
                    str.erase(0, i + 1);
                    break;
                }
                x += str.at(i);
            }

            return x;
        };

        int xx = std::stoi(x());
        int yy = std::stoi(str);
        std::cout << xx << " : " << yy << '\n';
        SetCursorPos(xx, yy);
    }
    else if (Contains(str, down_str))
    {
        str.erase(0, 4);
        keybd_event((BYTE)std::stoi(str.c_str()), MapVirtualKey((UINT)std::stoi(str.c_str()), 0), 0, 0);
    }
    else if (Contains(str, up_str))
    {
        str.erase(0, 2);
        keybd_event((BYTE)std::stoi(str.c_str()), MapVirtualKey((UINT)std::stoi(str.c_str()), 0), KEYEVENTF_KEYUP, 0);
    }
}