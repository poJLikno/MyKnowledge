#ifndef PLAYER_H_
#define PLAYER_H_


#include "main.h"

class Player
{
public:
	float pos_x{}, pos_y{}, angle{};
	unsigned short FOV{}, max_ray_depth{};

	Player(float pos_x, float pos_y, float angle, unsigned short FOV, unsigned short max_ray_depth);
};


#endif