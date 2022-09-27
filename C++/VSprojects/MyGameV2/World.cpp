#include "World.h"

void World::RayCasting(HDC dc, float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth)
{
	float wallheight = 600.f / World::NearestCross(World::VerticalCross(p_pos_x, p_pos_y, p_angle, max_ray_depth), World::HorizontalCross(p_pos_x, p_pos_y, p_angle, max_ray_depth));

	SetDCBrushColor(dc, RGB(0, 255, 0));
	SetDCPenColor(dc, RGB(0, 255, 0));
	Rectangle(dc, screenwidth / 2, screenheight / 2 - (int)wallheight / 2, screenwidth / 2 + 10, screenheight / 2 + (int)wallheight / 2);

	Rectangle(dc, 10, 10, 60, 60);
}

float World::VerticalCross(float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth)
{
	float min_ray_depth = 0.f;

	for (float x = 0.f; x < (float)screenwidth; x += 100.f)
	{
		float ray_depth = ((float)x - p_pos_x) / cos((float)p_angle * PI / 180.f);
		if (ray_depth > (float)max_ray_depth && ray_depth < 0.f) continue;

		float y = ray_depth * sin(p_angle * PI / 180.f) + p_pos_y;

		if (World::map[(short)(trunc(y) / 100.f)][(short)(x / 100.f)] == 'w' && (min_ray_depth == 0.f || ray_depth < min_ray_depth))
		{
			min_ray_depth = ray_depth;
		}
	}

	return min_ray_depth;
}

float World::HorizontalCross(float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth)
{
	float min_ray_depth = 0.f;

	for (float y = 0.f; y < (float)screenheight; y += 100.f)
	{
		float ray_depth = ((float)y - p_pos_y) / sin((float)p_angle * PI / 180.f);
		if (ray_depth > (float)max_ray_depth && ray_depth < 0.f) continue;

		float x = ray_depth * cos(p_angle * PI / 180.f) + p_pos_x;

		if (World::map[(short)(trunc(y) / 100.f)][(short)(x / 100.f)] == 'w' && (min_ray_depth == 0.f || ray_depth < min_ray_depth))
		{
			min_ray_depth = ray_depth;
		}
	}

	return min_ray_depth;
}

float World::NearestCross(float min_ray_depth_vertical, float min_ray_depth_horizontal)
{
	if (min_ray_depth_vertical <= min_ray_depth_horizontal) return min_ray_depth_vertical;
	else if (min_ray_depth_vertical > min_ray_depth_horizontal) return min_ray_depth_horizontal;
}