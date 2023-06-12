#include "Player.h"

void Player::Walk()
{
	vec2d<float> facing_2d = GetFacing();
	facing_2d = normalize(facing_2d);

	if (GetKeyState('W') < 0)
	{
		SetX(GetX() + facing_2d.get_x() * speed_);
		SetY(GetY() + facing_2d.get_y() * speed_);
	}
	if (GetKeyState('A') < 0)
	{
		SetX(GetX() - facing_2d.get_y() * speed_);
		SetY(GetY() + facing_2d.get_x() * speed_);
	}
	if (GetKeyState('S') < 0)
	{
		SetX(GetX() - facing_2d.get_x() * speed_);
		SetY(GetY() - facing_2d.get_y() * speed_);
	}
	if (GetKeyState('D') < 0)
	{
		SetX(GetX() + facing_2d.get_y() * speed_);
		SetY(GetY() - facing_2d.get_x() * speed_);
	}
	if (GetKeyState(' ') < 0)
	{
		SetZ(GetZ() + speed_);
	}
	if (GetKeyState('C') < 0)
	{
		SetZ(GetZ() - speed_);
	}
}

void Player::Look(HWND *hWnd, int width, int height)
{
	POINT point = {};
	GetCursorPos(&point);
	ScreenToClient(*hWnd, &point);

	SetAngleXY(GetAngleXY() - float(point.x - width / 2) / 50.f);
	SetAngleXZ(GetAngleXZ() - float(point.y - height / 2) / 50.f);
	SetFacingByAngle();
}
