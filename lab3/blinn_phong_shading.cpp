// used tutorial slides for equations

#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  Eigen::Vector3d p = ray.origin + t * ray.direction;
  Eigen::Vector3d rgb(0, 0, 0);
  Eigen::Vector3d L = objects[hit_id]->material->ka * 0.1;
  rgb += L;
  for (int i = 0; i < lights.size(); i++) {
		Eigen::Vector3d dir;
		double max_t;
		lights[i]->direction(p, dir, max_t);
		Ray shadow_ray;
		shadow_ray.origin = p + 1e-9 * n;
		shadow_ray.direction = dir;
		int hit_id_shadow;
		Eigen::Vector3d n_shadow;
		double t_shadow;

		bool shadow = first_hit(shadow_ray, 1e-9, objects, hit_id_shadow, t_shadow, n_shadow);
		if (!shadow || t_shadow > max_t) {
			Eigen::Vector3d v = -ray.direction.normalized();
			Eigen::Vector3d l = shadow_ray.direction;
			Eigen::Vector3d h = (l + v).normalized();

			Eigen::Vector3d light_color = lights[i]->I;
			Eigen::Vector3d ks = objects[hit_id]->material->ks;
			Eigen::Vector3d kd = objects[hit_id]->material->kd;
			double spec_angle = std::max(0.0, n.dot(h));
			double diffuse_angle = std::max(0.0, n.dot(l));
			Eigen::Vector3d specular = (light_color.array() * ks.array() * pow(spec_angle, objects[hit_id]->material->phong_exponent)).matrix();
			Eigen::Vector3d diffuse = (light_color.array() * kd.array() * diffuse_angle).matrix();
			L += diffuse + specular;
		} 
  }
  L = L.array().max(0.0).min(1.0).matrix();
  return L;
}
