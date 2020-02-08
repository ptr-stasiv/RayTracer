#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out vec2 uvCoord;

void main()
{
  uvCoord = uv;
  gl_Position = vec4(position, 0.0f, 1.0f);
}
