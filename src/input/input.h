#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace input
{
  extern bool Keys[1024];

  //Setup GLFW input
  bool SetupInput(GLFWwindow* window);
}
