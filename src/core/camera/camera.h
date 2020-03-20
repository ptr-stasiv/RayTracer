#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace rt
{
  #define CAMERA_SPEED        15.0f
  #define CAMERA_FOV          45.0f
  #define CAMERA_YAW          -90.0f
  #define CAMERA_PITCH        0.0f
  #define CAMERA_SENSETIVITY  0.05f

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
    glm::vec3 BasePosition;
    glm::vec3 Target;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;

    float Speed;
    float FOV;
    float Yaw;
    float Pitch;

    glm::vec2 ScreenSize;
    float     AspectRatio;
  public:
    explicit Camera(const glm::vec3 position = glm::vec3(0.0f), const glm::vec3 target = glm::vec3(0.0f, 0.0f, 1.0f), const float speed = CAMERA_SPEED, const float fov = CAMERA_FOV, const glm::vec2 screenSize = glm::vec2(300.0f, 300.0f));

    //Move camera in that direction which is pass in function
    void Move(const CameraMove move, const float deltaTime);

    //Handle mouse to rotate camera
    void ProcessMouse(const float mouseX, const float mouseY);

    glm::vec3 GetPosition() const;
    glm::vec3 GetPosition(glm::vec3 position) const;
    glm::vec3 GetDirection(const int x, const int y) const;

  private:
    //Return look at matrix
    glm::mat4 GetViewMatrix() const;
  };
}
