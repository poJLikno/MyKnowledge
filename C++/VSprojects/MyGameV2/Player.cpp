#include "Player.h"

Player::Player(float pos_x, float pos_y, float angle, unsigned short FOV, float max_ray_depth)
{
	Player::pos_x = pos_x;
	Player::pos_y = pos_y;
	Player::angle = angle;
	Player::FOV = FOV;
	Player::max_ray_depth = max_ray_depth;
}
