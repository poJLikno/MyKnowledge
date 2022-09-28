#ifndef MINIMAP_H_
#define MINIMAP_H_


#include "main.h"

class MiniMap
{
public:
	const char map[screenheight / 100][screenwidth / 100 + 1]
	{
		"wwwwww",
		"......",
		"...ww.",
		"....w.",
		"......",
		"wwwwww"
	};

	float VerticalCross(float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth);

	//float HorizontalCross();

	void ShowMap(HDC dc, float p_pos_x, float p_pos_y, float scale);
};


#endif