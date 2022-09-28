#ifndef WORLD_H_
#define WORLD_H_


#include "main.h"

class World
{
private:
	const char map[screenheight / 100][screenwidth / 100 + 1]
	{
		"wwwwww",
		"......",
		"...ww.",
		"....w.",
		"......",
		"wwwwww"
	};

	float HorizontalCross(float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth);

	float VerticalCross(float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth);

	float NearestCross(float min_ray_depth_vertical, float min_ray_depth_horizontal);

public:
	void RayCasting(HDC dc, float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth);
};


#endif