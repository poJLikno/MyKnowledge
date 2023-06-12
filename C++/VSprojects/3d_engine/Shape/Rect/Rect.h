#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../Shape.h"

class Rect : Shape
{
private:
	float x_, y_, z_, a_;

public:
	Rect(float x, float y, float z, float a) : x_(x), y_(y), z_(z), a_(a) {}

	bool FindIntersection(vec3d<float> facing, float x, float y, float z) override final;
};

#endif