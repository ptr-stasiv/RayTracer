#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <cstdint>
#include <string>

namespace graphics
{
  //Create window and initialize GLFW and GLEW
  //Return nullptr if something going wrong
  void* CreateWindow(const uint16_t width, const uint16_t height, const std::string title);

  //Main loop function, update window and handle input events
  void WindowLoop(GLFWwindow* window, void (*func)(void));

  void TerminateWindow();
}
