#include "camera.h"

namespace rt
{
  Camera::Camera(const glm::vec3 position, const glm::vec3 target, const float speed)
    : Position(position), Target(target), Speed(speed)
  {
    Forward = glm::normalize(Position - Target);
    Right   = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), Forward));
    Up      = glm::normalize(glm::cross(Forward, Right));
  }

  glm::mat4 Camera::GetViewMatrix() const
  {
    return glm::lookAt(Position, Position + Forward, Up);
  }

  void Camera::Move(const CameraMove move, const float deltaTime)
  {
    switch(move)
    {
      case CameraMove::FORWARD:  Position += -Forward * (Speed * deltaTime);   break;
      case CameraMove::BACKWARD: Position += Forward * (Speed * deltaTime);  break;
      case CameraMove::RIGHT:    Position += Right * (Speed * deltaTime);     break;
      case CameraMove::LEFT:     Position += -Right * (Speed * deltaTime);    break;
      case CameraMove::UP:       Position += Up * (Speed * deltaTime);        break;
      case CameraMove::DOWN:     Position += -Up * (Speed * deltaTime);       break;
    }
  }
}
