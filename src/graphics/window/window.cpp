#include "window.h"

namespace graphics
{
  void* CreateWindow(const uint16_t width, const uint16_t height, const std::string title)
  {
    if(!glfwInit())
      return nullptr;

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!window)
      return nullptr;

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
      return nullptr;

    return window;
  }

  void WindowLoop(GLFWwindow* window, void (*func)(void))
  {
    while(!glfwWindowShouldClose(window))
    {
      glfwPollEvents();

      //Call user main function
      func();

      glfwSwapBuffers(window);
    }
  }

  void TerminateWindow()
  {
    glfwTerminate();
  }
}
