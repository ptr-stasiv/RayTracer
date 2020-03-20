#include "camera.h"

namespace rt
{
  Camera::Camera(const glm::vec3 position, const glm::vec3 target, const float speed, const float fov, const glm::vec2 screenSize)
    : Position(position), BasePosition(position), Target(target), Speed(speed), FOV(fov), ScreenSize(screenSize),
      Yaw(CAMERA_YAW), Pitch(CAMERA_PITCH)
  {
    Forward = glm::normalize(Position - Target);
    Right   = glm::normalize(glm::cross(Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    Up      = glm::normalize(glm::cross(Right, Forward));

    AspectRatio = screenSize.x / screenSize.y;
  }

  glm::mat4 Camera::GetViewMatrix() const { return glm::lookAt(Position, Position + Forward, Up); }
  glm::vec3 Camera::GetPosition() const { return GetViewMatrix() * glm::vec4(BasePosition, 1.0f); }
  glm::vec3 Camera::GetPosition(glm::vec3 position) const { return GetViewMatrix() * glm::vec4(position, 1.0f); }

  glm::vec3 Camera::GetDirection(const int x, const int y) const
  {
    glm::vec2 ndc;
    ndc.x = (x + 0.5f) / ScreenSize.x;
    ndc.y = (y + 0.5f) / ScreenSize.y;

    glm::vec2 pixel;
    pixel.x = (2.0f * ndc.x - 1.0f) * AspectRatio * glm::tan(glm::radians(FOV / 2.0f));
    pixel.y = (1.0f - 2.0f * ndc.y) * glm::tan(glm::radians(FOV / 2.0f));

    return glm::normalize(glm::vec3(pixel, -1.0f));
  }

  void Camera::Move(const CameraMove move, const float deltaTime)
  {
    switch(move)
    {
      case CameraMove::FORWARD:  Position += Forward * (Speed * deltaTime);   break;
      case CameraMove::BACKWARD: Position += -Forward * (Speed * deltaTime);  break;
      case CameraMove::RIGHT:    Position += Right * (Speed * deltaTime);     break;
      case CameraMove::LEFT:     Position += -Right * (Speed * deltaTime);    break;
      case CameraMove::UP:       Position += -Up * (Speed * deltaTime);       break;
      case CameraMove::DOWN:     Position += Up * (Speed * deltaTime);        break;
    }
  }

  void Camera::ProcessMouse(const float mouseX, const float mouseY)
  {
    Yaw   += mouseX * CAMERA_SENSETIVITY;
    Pitch += mouseY * CAMERA_SENSETIVITY;

    glm::vec3 forward(0.0f);
    forward.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    forward.y = glm::sin(glm::radians(Pitch));
    forward.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));

    Forward = glm::normalize(forward);
    Right   = glm::normalize(glm::cross(Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    Up      = glm::normalize(glm::cross(Right, Forward));
  }
}
