#include "sphere.h"

namespace rt
{
  Sphere::Sphere(const glm::vec3& center, const float radius)
    : Center(center), Radius(radius) {}

  bool Sphere::Intersection(const Ray& ray, float& t) const
  {
    float tc = glm::dot(Center - ray.Origin, ray.Direction);
    glm::vec3 point = ray.Origin + ray.Direction * tc;
    float y = glm::length(Center - point);

    if(y > Radius)
      return false;

    float x = sqrt(Radius * Radius - y * y);
    t = t - x;

    if(t < 0)
      t = t + x;
    if(t < 0)
      return false;

    return true;
  }
}
