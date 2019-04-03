#pragma once
#include "Config.h"

// 光线击中的颜色
Vec3 color(const Ray& r, hitable * world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		Vec3 attenuation;
		Vec3 albedo;
		float pdf;
		Vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf))
		{
			vec3 on_light = vec3(213 + drand48()*(343 - 213), 554, 227 + drand48()*(332 - 227));
			vec3 to_light = on_light - rec.p ;
			float distance_squared = to_light.squared_length();
			to_light.make_unit_vector();
			if (dot(to_light, rec.normal) < 0)
				return emitted;
			float light_area = (343 - 213)*(332 - 227);
			float light_cosine = fabs(to_light.y());
			if (light_cosine < 0.00001)
				return emitted;
			pdf = distance_squared / (light_cosine * light_area);
			scattered = Ray(rec.p, to_light, r.time());
			return emitted + albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered) * color(scattered, world, depth + 1) / pdf;
		}
		else
		{
			return emitted;
			//return Vec3(1, 1, 1);
		}

	}
	else
	{
		/*
		background

		Vec3 unit_direction = unit_vector(r.Direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);

		*/

		return Vec3(0, 0, 0);
	}
}


// 伽马矫正 
Vec3 Gamma_Correct(Vec3 col)
{
	return Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
}

/*
Vec3 color(const Ray& r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		Ray scattered;
		Vec3 attenuation;
		Vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return emitted + attenuation*color(scattered, world, depth + 1);
		else
			return emitted;
	}
	else
		return Vec3(0, 0, 0);
}
*/

