#ifndef PLAYER_H_
#define PLAYER_H_


#include "main.h"

class Player
{
public:
	float pos_x{}, pos_y{}, angle{}, max_ray_depth{};
	unsigned short FOV{};

	Player(float pos_x, float pos_y, float angle, unsigned short FOV, float max_ray_depth);
};


#endif
