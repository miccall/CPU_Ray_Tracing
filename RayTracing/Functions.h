#pragma once
#include "Ray.h"

class MicFunc
{
public:

	MicFunc();
	~MicFunc();
	// 随机数 
	static float drand48()
	{
		const long long  m = 0x100000000LL, ra = 0x5DEECE66DLL;
		int rc = 0xB16;
		seed = (ra * seed + rc) & 0xFFFFFFFFFFFFLL;
		unsigned int x = seed >> 16;
		return (float)((double)x / (double)m);
	}
	// 随机反射点 
	static Vec3 Random_in_unitt_cube()
	{
		Vec3 p;
		do
		{
			p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);

		} while (/*p.squared_length() >= 1.0 */ dot(p, p) >= 1.0);
		return p;
	}

	static inline Vec3 Random_cosine_direction()
	{
		float r1 = drand48();
		float r2 = drand48();
		float z = sqrt(1 - r2);
		float phi = 2 * M_PI * r1;
		float x = cos(phi) * 2 * sqrt(r2);
		float y = sin(phi) * 2 * sqrt(r2);
		return Vec3(x, y, z);
	}
	//归一化向量
	static inline Vec3 unit_vector(Vec3 v) {
		return v / v.length();
	}

private:

};

MicFunc::MicFunc()
{
}

MicFunc::~MicFunc()
{
}
