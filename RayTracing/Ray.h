#pragma once
#include "Vec3.h"

class Ray
{
public:
	Ray();
	Ray(const Vec3 & a , const Vec3 & b );
	Ray(const Vec3 & a, const Vec3 & b, float ti);
	Vec3 Origin() const;
	Vec3 Direction() const; 
	float time() const;
	Vec3 point_at_parameter(float t) const;

	Vec3 A;
	Vec3 B;
	float _time;
};


