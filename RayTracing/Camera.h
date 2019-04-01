#pragma once
#include "Ray.h"


Vec3 random_in_unit_disk() {
	Vec3 p;
	do {
		p = 2.0*Vec3(drand48(), drand48(), 0) - Vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

class Camera
{
public:
	Vec3 origin;
	Vec3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
	// ��������camera �� ������������ �� u ˮƽ���� ��v,��ֱ���� ��w ǰ���� 
	Vec3 u, v, w;
	// �ع�ʱ�� 
	float time0, time1;
	// ��ͷ�뾶 
	float lens_radius;

public:
	Camera();
	// fov ����ֱ������ӽǽǶ�  aspect �� ���ݱ�  
	Camera(float vfov, float aspect);
	// lookfrom ��ԭ��λ�� ��lookat ���۲�λ�� �� vup ��ֱ���Ϸ��� ��fov ����ֱ������ӽǽǶ�  aspect �� ���ݱ�  
	Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect);
	// lookfrom ��ԭ��λ�� ��lookat ���۲�λ�� �� vup ��ֱ���Ϸ��� ��fov ����ֱ������ӽǽǶ�  aspect �� ���ݱ�  ,aperture��Ȧ ,focus_dist����
	Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist);
	// lookfrom ��ԭ��λ�� ��lookat ���۲�λ�� �� vup ��ֱ���Ϸ��� ��fov ����ֱ������ӽǽǶ�  aspect �� ���ݱ�  ,aperture��Ȧ ,focus_dist���� t1 t0 �ع�ʱ�� ��
	Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float apertur, float focus_dist, float to, float t1);

	Ray getRay(float u, float v);
};

Camera::Camera()
{
	lower_left_corner = Vec3(-2.0, -1.0, -1.0);
	horizontal = Vec3(4.0, 0.0, 0.0);
	vertical = Vec3(0.0, 2.0, 0.0);
	origin = Vec3(0.0, 0.0, 0.0);
}


Camera::Camera(float vfov, float aspect)
{
	// �Ƕ�ת���� 
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_widgh = aspect * half_height;

	lower_left_corner = Vec3(-half_widgh, -half_height, -1.0);
	horizontal = Vec3(2 * half_widgh, 0.0, 0.0);
	vertical = Vec3(0.0, 2 * half_height, 0.0);
	origin = Vec3(0.0, 0.0, 0.0);
}


Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect)
{
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_widgh = aspect * half_height;
	origin = lookfrom;

	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);

	lower_left_corner = origin - half_widgh * u - half_height * v - w;
	horizontal = 2 * half_widgh * u;
	vertical = 2 * half_height * v;
}


Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
{
	lens_radius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;
	origin = lookfrom;
	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	lower_left_corner = origin - half_width * focus_dist*u - half_height * focus_dist*v - focus_dist * w;
	horizontal = 2 * half_width*focus_dist*u;
	vertical = 2 * half_height*focus_dist*v;
}


Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist, float t0, float t1)
{
	time0 = t0;
	time1 = t1;
	lens_radius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_widgh = aspect * half_height;
	origin = lookfrom;
	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	lower_left_corner = origin - half_widgh * focus_dist * u - half_height * focus_dist *v - focus_dist * w;
	horizontal = 2 * half_widgh * focus_dist * u;
	vertical = 2 * half_height * focus_dist *v;
}

/*
Ray Camera::getRay(float u, float v)
{
	return Ray(origin , lower_left_corner + u*horizontal + v * vertical - origin );
}
*/



/*
Ray Camera::getRay(float s, float t)
{
	Vec3 rd = lens_radius * random_in_unit_disk();
	Vec3 offset = u * rd.x() + v * rd.y();
	return Ray(origin + offset, lower_left_corner + s*horizontal + t * vertical - origin - offset);
}
*/

Ray Camera::getRay(float s, float t)
{
	Vec3 rd = lens_radius * random_in_unit_disk();
	Vec3 offset = u * rd.x() + v * rd.y();
	float time = time0 + drand48() * (time1 - time0);
	return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
}