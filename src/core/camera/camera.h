#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace rt
{
  enum class CameraMove
  {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT,
    UP,
    DOWN,
  };

  class Camera
  {
  private:
    glm::vec3 Position;
    glm::vec3 Target;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;

    float Speed;
  public:
    explicit Camera(const glm::vec3 position = glm::vec3(0.0f), const glm::vec3 target = glm::vec3(0.0f, 0.0f, 1.0f), const float speed = 15.0f);

    //Move camera in that direction which is pass in function
    void Move(const CameraMove move, const float deltaTime);

    //Return look at matrix
    glm::mat4 GetViewMatrix() const;

    inline glm::vec3 GetPosition() const { return Position; }
  };
}
