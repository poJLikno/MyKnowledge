#ifndef MINIMAP_H_
#define MINIMAP_H_


#include "main.h"

class MiniMap
{
public:
	const char map[screenheight / 100][screenwidth / 100 + 1] =
	{
		"wwwwww",
		"w....w",
		"w.ww.w",
		"...w.w",
		"w....w",
		"wwwwww"
	};

	/*const char map[screenheight / 100][screenwidth / 100 + 1] =
	{
		"www",
		"..w",
		"www"
	};*/

	float VerticalCross(float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth);

	float HorizontalCross(float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth);

	float NearestCross(float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth);

	void ShowMap(HDC dc, float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth, float p_FOV, float p_delta_angle, float scale);
};


#endif