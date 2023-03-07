#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(vec3 c, float r) : center(c), radius(r) {};

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

	vec3 center;
	float radius{};
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	auto oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius*radius;

	auto discriminant = b*b - a*c;
	if (discriminant < 0)
	{
		return false;
	}

	auto sqrtd = sqrt(discriminant);
	auto root = (-b - sqrtd) / a;

	if (root < t_min || t_max < root)
	{
		root = (-b + sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	return true;
}