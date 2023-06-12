#ifndef SHAPE_H
#define SHAPE_H

#include "../Vec/vec3d_type.h"

class Shape
{
public:
	virtual bool FindIntersection(vec3d<float> facing, float x, float y, float z) = 0;
};

#endif