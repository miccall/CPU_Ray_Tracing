#include "Ray.h"

extern float drand48();
extern Vec3 Random_in_unitt_cube();

//Ĭ�Ϲ��캯�� 
Ray::Ray() {

}

// ���캯�� �� a ������ԭ�� �� b �� ���߷��� 
Ray::Ray(const Vec3 & a, const Vec3 & b)
{
	A = a;
	B = b;
	_time = 0.0;
}

Ray::Ray(const Vec3 & a, const Vec3 & b, float ti)
{
	A = a;
	B = b;
	_time = ti;
}

Vec3 Ray::Origin() const
{
	return A;
}

float Ray::time()const
{
	return _time;
}

Vec3 Ray::Direction() const
{
	return B;
}

Vec3 Ray::point_at_parameter(float t) const
{
	return  A + B * t;
}