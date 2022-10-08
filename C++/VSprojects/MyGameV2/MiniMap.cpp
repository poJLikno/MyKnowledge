#include "MiniMap.h"

void MiniMap::ShowMap(HDC dc, float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth, float p_FOV, float p_delta_angle, float scale)
{
	SetDCPenColor(dc, RGB(50, 50, 50));
	SetDCBrushColor(dc, RGB(50, 50, 50));
	Rectangle(dc, 0 * scale, 0 * scale, screenwidth * scale, screenheight * scale);

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

	float angle = p_angle - p_FOV / 2.f;

	for (float ray_num = 0.f; ray_num < (float)screenwidth; ray_num++)
	{
		if (MiniMap::NearestCross(p_pos_x, p_pos_y, angle, max_ray_depth) != max_ray_depth + 1.f)
		{
			SetDCBrushColor(dc, RGB(255, 255, 0));
			SetDCPenColor(dc, RGB(150, 150, 150));

			float cross_pos_x = p_pos_x + MiniMap::NearestCross(p_pos_x, p_pos_y, angle, max_ray_depth) * cos(angle * PI / 180);
			float cross_pos_y = p_pos_y + MiniMap::NearestCross(p_pos_x, p_pos_y, angle, max_ray_depth) * sin(angle * PI / 180);

			MoveToEx(dc, (short)(p_pos_x * scale), (short)(p_pos_y * scale), NULL);
			LineTo(dc, (short)(cross_pos_x * scale), (short)(cross_pos_y * scale));

			//SetDCPenColor(dc, RGB(255, 255, 0));
			//Rectangle(dc, (short)((cross_pos_x - 5.f) * scale), (short)((cross_pos_y - 5.f) * scale), (short)((cross_pos_x + 5.f) * scale), (short)((cross_pos_y + 5.f) * scale));
		}
		else if (MiniMap::NearestCross(p_pos_x, p_pos_y, angle, max_ray_depth) == max_ray_depth + 1.f)
		{
			SetDCBrushColor(dc, RGB(255, 255, 0));
			SetDCPenColor(dc, RGB(150, 150, 150));

			float cross_pos_x = p_pos_x + (MiniMap::NearestCross(p_pos_x, p_pos_y, angle, max_ray_depth) - 1.f) * cos(angle * PI / 180);
			float cross_pos_y = p_pos_y + (MiniMap::NearestCross(p_pos_x, p_pos_y, angle, max_ray_depth) - 1.f) * sin(angle * PI / 180);

			MoveToEx(dc, (short)(p_pos_x * scale), (short)(p_pos_y * scale), NULL);
			LineTo(dc, (short)(cross_pos_x * scale), (short)(cross_pos_y * scale));

			//SetDCPenColor(dc, RGB(255, 255, 0));
			//Rectangle(dc, (short)((cross_pos_x - 5.f) * scale), (short)((cross_pos_y - 5.f) * scale), (short)((cross_pos_x + 5.f) * scale), (short)((cross_pos_y + 5.f) * scale));
		}

		angle += p_delta_angle;
	}

	SetDCBrushColor(dc, RGB(100, 255, 255));
	SetDCPenColor(dc, RGB(0, 0, 0));
	Rectangle(dc, (short)((p_pos_x - 10.f) * scale), (short)((p_pos_y - 10.f) * scale), (short)((p_pos_x + 10.f) * scale), (short)((p_pos_y + 10.f) * scale));
}

float MiniMap::NearestCross(float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth)
{
	float min_ray_depth_vertical = MiniMap::VerticalCross(p_pos_x, p_pos_y, p_angle, max_ray_depth);

	float min_ray_depth_horizontal = MiniMap::HorizontalCross(p_pos_x, p_pos_y, p_angle, max_ray_depth);

	if (min_ray_depth_vertical <= min_ray_depth_horizontal) return min_ray_depth_vertical;
	else return min_ray_depth_horizontal;
}

float MiniMap::VerticalCross(float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth)
{
	float min_ray_depth = max_ray_depth + 1.f;

	for (float x = 0.f; x < (float)screenwidth; x += 100.f)
	{
		float ray_depth = (x - p_pos_x) / cos(p_angle * PI / 180.f);
		if (ray_depth <= max_ray_depth && ray_depth > 0.f)
		{
			float y = p_pos_y + ray_depth * sin(p_angle * PI / 180.f);
			if (y <= (float)screenheight && y >= 0.f)
			{
				if (MiniMap::map[(short)trunc(y / 100.f)][(short)(x / 100.f)] == 'w' || MiniMap::map[(short)trunc(y / 100.f)][(short)(x / 100.f - 1.f)] == 'w')
				{
					if (min_ray_depth == max_ray_depth + 1.f || ray_depth < min_ray_depth) min_ray_depth = ray_depth;
				}
			}
		}
	}

	return min_ray_depth;
}

float MiniMap::HorizontalCross(float p_pos_x, float p_pos_y, float p_angle, float max_ray_depth)
{
	float min_ray_depth = max_ray_depth + 1.f;

	for (float y = 0.f; y < (float)screenheight; y += 100.f)
	{
		float ray_depth = (y - p_pos_y) / sin(p_angle * PI / 180.f);
		if (ray_depth <= max_ray_depth && ray_depth > 0.f)
		{
			float x = p_pos_x + ray_depth * cos(p_angle * PI / 180.f);
			if (x <= (float)screenwidth && x >= 0.f)
			{
				if (MiniMap::map[(short)trunc(y / 100.f)][(short)(x / 100.f)] == 'w' || MiniMap::map[(short)trunc(y / 100.f - 1.f)][(short)(x / 100.f)] == 'w')
				{
					if (min_ray_depth == max_ray_depth + 1.f || ray_depth < min_ray_depth) min_ray_depth = ray_depth;
				}
			}
		}
	}

	return min_ray_depth;
}