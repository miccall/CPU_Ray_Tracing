#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#pragma warning(disable:4305)
#pragma warning(disable:4244)
const float M_PI = 3.14159;
class Vec3
{
public:
	float e[3];
public:
	Vec3() {};
	Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const Vec3 & operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	inline float operator[] (int i) const { return e[i]; }
	inline float& operator[] (int i) { return e[i]; }
	inline Vec3& operator+=(const Vec3 & v2);
	inline Vec3& operator*=(const Vec3 & v2);
	inline Vec3& operator-=(const Vec3 & v2);
	inline Vec3& operator/=(const Vec3 & v2);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);

	inline float length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	inline float squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void make_unit_vector();
};

using vec3 = Vec3;
static unsigned long long seed = 4;
//������ �����ʽ
inline std::istream& operator>>(std::istream &is, Vec3 &t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

//����� �����ʽ
inline std::ostream& operator<<(std::ostream &os, const Vec3 &t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

//���������
inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

//���������
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

//��������ˣ�for colors )
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

//�����������for colors )
inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
	return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

//һ��������һ������
inline Vec3 operator*(float t, const Vec3 &v) {
	return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

//һ����������һ������
inline Vec3 operator/(Vec3 v, float t) {
	return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

//һ��������һ������
inline Vec3 operator*(const Vec3 &v, float t) {
	return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

//��������ˣ����ڻ�����һ����������for locations
inline float dot(const Vec3 &v1, const Vec3 &v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

//��������ˣ����������һ����������for locations
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
	return Vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}



