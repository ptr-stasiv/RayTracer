#include "input.h"

namespace input
{
  bool Keys[1024];

  void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if(action == GLFW_PRESS)
      Keys[key] = true;
    if(action == GLFW_RELEASE)
      Keys[key] = false;
  }

  bool SetupInput(GLFWwindow* window)
  {
    if(!window)
      return false;

    glfwSetKeyCallback(window, KeyboardCallback);

    return true;
  }
}
