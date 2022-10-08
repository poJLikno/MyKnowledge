#ifndef PLAYER_H_
#define PLAYER_H_


#include "main.h"

class Player
{
public:
	float pos_x{}, pos_y{}, angle{}, max_ray_depth{}, FOV{}, delta_angle{};
	POINT c_pos{};

	Player(float pos_x, float pos_y, float angle, float FOV, float max_ray_depth);

	void CheckKeys();

	void CheckMouse();
};


#endif