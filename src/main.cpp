#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

#include "graphics/window/window.h"
#include "input/input.h"
#include "graphics/shaders/shader_manager.h"

#include "core/ray_tracer.h"

#include <cassert>
#include <cstring>
#include <cmath>

#define ASSERT(x, y) assert(x && y);

#define SCREEN_WIDTH    300
#define SCREEN_HEIGHT   150

float AspectRatio = static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT;
float FOV         = 45.0f;

glm::vec3 Framebuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

GLuint VBO;

rt::Camera Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 15.0f, 30.0f, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));

rt::Sphere Sphere(glm::vec3(0.0f, 0.0f, -10.0f), 2.5f);

void Render();
glm::vec3 CastRay(rt::Ray ray);

void MainLoop();
void UpdateTexture();

void InputHandle();

int main()
{
  GLFWwindow* window = reinterpret_cast<GLFWwindow*>(graphics::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RayTracer"));
  if(!window)
  {
    graphics::TerminateWindow();
    return -1;
  }

  if(!input::SetupInput(window))
    return -1;

  float vertices[] =
  {
    -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f,  0.0f, 1.0f,
    1.0f, 1.0f,   1.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f
  };

  //Create screen vbo

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);


  //Create screen texture

  GLuint screenTexture;
  glGenTextures(1, &screenTexture);
  glBindTexture(GL_TEXTURE_2D, screenTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_FLOAT, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, screenTexture);

  uint8_t shader;
  ASSERT(graphics::CreateShader("../res/shaders/screen_shader.vert", "../res/shaders/screen_shader.frag", shader), "Error compile shader!");
  glUseProgram(shader);

  glUniform1i(glGetUniformLocation(shader, "screenTexture"), 0);

  graphics::WindowLoop(window, MainLoop);

  return 0;
}

void Render()
{
  InputHandle();

  for(int j = 0; j < SCREEN_HEIGHT; ++j)
  {
    for(int i = 0; i < SCREEN_WIDTH; ++i)
    {
      rt::Ray mainRay;
      mainRay.Origin      = Camera.GetPosition();
      mainRay.Direction   = Camera.GetDirection(i, j);

      Framebuffer[i + j * SCREEN_WIDTH] = CastRay(mainRay);
    }
  }
}

void InputHandle()
{
  if(input::Keys[GLFW_KEY_W])
    Camera.Move(rt::CameraMove::FORWARD, 0.01f);
  if(input::Keys[GLFW_KEY_S])
    Camera.Move(rt::CameraMove::BACKWARD, 0.01f);
  if(input::Keys[GLFW_KEY_D])
    Camera.Move(rt::CameraMove::RIGHT, 0.01f);
  if(input::Keys[GLFW_KEY_A])
    Camera.Move(rt::CameraMove::LEFT, 0.01f);
}

glm::vec3 CastRay(rt::Ray ray)
{
  float distance = INFINITY;
  if(Sphere.Intersection(ray, distance))
    return glm::vec3(1.0f, 0.2f, 0.2f);

  return glm::vec3(0.5f, 0.5f, 0.5f);
}

void UpdateTexture()
{
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_FLOAT, &Framebuffer[0]);
}

void MainLoop()
{
  Render();
  UpdateTexture();

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glDrawArrays(GL_QUADS, 0, 8);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
