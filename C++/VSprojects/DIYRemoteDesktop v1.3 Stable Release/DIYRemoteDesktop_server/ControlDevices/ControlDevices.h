#ifndef CONTROL_DEVICES_H
#define CONTROL_DEVICES_H

#include <iostream>
#include <string>
#include <Windows.h>

class ControlDevices
{
private:
	std::string str;
	POINT point = {};

	const std::string lbtndown_str = "lbtndown";
	const std::string lbtnup_str = "lbtnup";
	const std::string rbtndown_str = "rbtndown";
	const std::string rbtnup_str = "rbtnup";
	const std::string mbtndown_str = "mbtndown";
	const std::string mbtnup_str = "mbtnup";
	const std::string wheel_str = "wheel";
	const std::string move_str = "move";

	const std::string down_str = "down";
	const std::string up_str = "up";

	bool Contains(std::string main_str, std::string part_str);

public:
	void operator()(char *buffer);
};

#endif