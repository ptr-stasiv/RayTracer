#pragma once
#include "glm/glm.hpp"
#include "../ray.h"

namespace rt
{
  class Sphere
  {
  private:
    glm::vec3 Center;
    float Radius;
  public:
    Sphere(const glm::vec3& center, const float radius);

    bool Intersection(const Ray& ray, float& t) const;
  };
}
