#pragma once
#include "glm/glm.hpp"

namespace rt
{
  struct Ray
  {
    glm::vec3 Origin;
    glm::vec3 Direction;
  };

  //Finding the point on the straight
  inline glm::vec3 PointAt(const Ray& ray, const float t) { return ray.Origin + ray.Direction * t; }
}
