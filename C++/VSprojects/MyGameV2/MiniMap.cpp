#include "MiniMap.h"

void MiniMap::ShowMap(HDC dc, float p_pos_x, float p_pos_y, float scale)
{
	SetDCPenColor(dc, RGB(0, 0, 0));
	SetDCBrushColor(dc, RGB(255, 150, 100));


	for (float y = 0; y < (float)screenheight; y += 100.f)
	{
		for (float x = 0; x < (float)screenwidth; x += 100.f)
		{
			if (MiniMap::map[(short)trunc(y / 100.f)][(short)trunc(x / 100.f)] == 'w')
			{
				Rectangle(dc, (short)(x * scale), (short)(y * scale), (short)((x + 100.f) * scale), (short)((y + 100.f) * scale));
			}
		}
	}

	Rectangle(dc, (short)((p_pos_x - 20.f) * scale), (short)((p_pos_y - 20.f) * scale), (short)((p_pos_x + 20.f) * scale), (short)((p_pos_y + 20.f) * scale));
}

float MiniMap::VerticalCross(float p_pos_x, float p_pos_y, float p_angle, unsigned short max_ray_depth)
{
	float min_ray_depth = 0.f;

	for (float x = 0.f; x < (float)screenwidth; x += 100.f)
	{
		float ray_depth = ((float)x - p_pos_x) / cos((float)p_angle * PI / 180.f);
		if (ray_depth < (float)max_ray_depth && ray_depth > 0.f)
		{
			float y = ray_depth * sin(p_angle * PI / 180.f) + p_pos_y;

			if (MiniMap::map[(short)(trunc(y) / 100.f)][(short)(x / 100.f)] == 'w' && (min_ray_depth == 0.f || ray_depth < min_ray_depth))
			{
				min_ray_depth = ray_depth;
			}
		}
	}

	return min_ray_depth;
}