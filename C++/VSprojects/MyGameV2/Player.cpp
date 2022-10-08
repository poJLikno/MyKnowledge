#include "Player.h"

Player::Player(float pos_x, float pos_y, float angle, float FOV, float max_ray_depth)
{
	Player::pos_x = pos_x;
	Player::pos_y = pos_y;
	Player::angle = angle;
	Player::FOV = FOV;
	Player::max_ray_depth = max_ray_depth;
	Player::delta_angle = FOV / (float)screenwidth;
}

void Player::CheckKeys()
{
	if (GetKeyState('W') < 0)
	{
		Player::pos_x += 5.f * cos(Player::angle * PI / 180.f);
		Player::pos_y += 5.f * sin(Player::angle * PI / 180.f);
	}
	if (GetKeyState('A') < 0)
	{
		Player::pos_x += 5.f * cos((Player::angle - 90.f) * PI / 180.f);
		Player::pos_y += 5.f * sin((Player::angle - 90.f) * PI / 180.f);
	}
	if (GetKeyState('S') < 0)
	{
		Player::pos_x += 5.f * cos((Player::angle + 180.f) * PI / 180.f);
		Player::pos_y += 5.f * sin((Player::angle + 180.f) * PI / 180.f);
	}
	if (GetKeyState('D') < 0)
	{
		Player::pos_x += 5.f * cos((Player::angle + 90.f) * PI / 180.f);
		Player::pos_y += 5.f * sin((Player::angle + 90.f)  * PI / 180.f);
	}
}

void Player::CheckMouse()
{
	GetCursorPos(&c_pos);

	if (c_pos.x != screenwidth / 2)
	{
		Player::angle += ((float)c_pos.x - (float)screenwidth / 2.f) / 10.f;
		SetCursorPos(screenwidth / 2, screenheight / 2);
	}
}