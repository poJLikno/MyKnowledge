#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include <math.h>
#include "../Vec/vec3d_type.h"

class Player
{
private:
	float x_, y_, z_, angle_xy_, angle_xz_;
	vec3d<float> facing_;

	float speed_ = 0.05f;

public:
	Player(float x, float y, float z, float angle_xy, float angle_xz) : x_(x), y_(y), z_(z), angle_xy_(angle_xy), angle_xz_(angle_xz),
		facing_(normalize(vec3d<float>(
			cosf(angle_xy * (float)M_PI / 180.f) * cosf(angle_xz *(float)M_PI / 180.f),
			sinf(angle_xy * (float)M_PI / 180.f) * cosf(angle_xz *(float)M_PI / 180.f),
			sinf(angle_xz * (float)M_PI / 180.f)))) {}
	
	// Getters & Setters
	float GetX() const { return x_; }
	void SetX(float x) { x_ = x; }

	float GetY() const { return y_; }
	void SetY(float y) { y_ = y; }

	float GetZ() const { return z_; }
	void SetZ(float z) { z_ = z; }

	float GetAngleXY() const { return angle_xy_; }
	void SetAngleXY(float angle) { angle_xy_ = angle; }

	float GetAngleXZ() const { return angle_xz_; }
	void SetAngleXZ(float angle) { angle_xz_ = angle; }
	
	vec3d<float> GetFacing() const { return facing_; }
	void SetFacing(vec3d<float> facing) { facing_ = normalize(facing); }
	void SetFacingByAngle()
	{
		facing_ = normalize(vec3d<float>(
			cosf(GetAngleXY() * (float)M_PI / 180.f) * cosf(GetAngleXZ() * (float)M_PI / 180.f),
			sinf(GetAngleXY() * (float)M_PI / 180.f) * cosf(GetAngleXZ() * (float)M_PI / 180.f),
			sinf(GetAngleXZ() * (float)M_PI / 180.f)));
	}

	// Walk
	void Walk();

	// Look
	void Look(HWND *hWnd, int width, int height);
};

#endif