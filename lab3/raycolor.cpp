// used tutorial slides for equations

#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
   if (num_recursive_calls > 8) {
	  return false;
   }
    rgb = Eigen::Vector3d(0, 0, 0);
	int hit_id;
	double t;
	Eigen::Vector3d n;

	bool hit = first_hit(ray, min_t, objects, hit_id, t, n);
	if (hit == false) {
		return false;
	}
	rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

	Eigen::Vector3d q = ray.origin + t * ray.direction;
	Ray mirror_ray;
	mirror_ray.origin = q + 1e-9 * n;
	mirror_ray.direction = reflect(ray.direction, n);

	Eigen::Vector3d reflected_rgb;
    Eigen::Vector3d km = objects[hit_id]->material->km;
	bool reflected_hit = raycolor(mirror_ray, 1e-9, objects, lights, num_recursive_calls + 1, reflected_rgb);
	if (reflected_hit) {
		rgb += (km.array() * reflected_rgb.array()).matrix();
	}

	return true;
}
