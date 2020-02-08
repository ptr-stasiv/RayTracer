#version 460 core

out vec4 Frag;

layout(binding = 0) uniform sampler2D screenTexture;

in vec2 uvCoord;

void main()
{
  Frag = texture(screenTexture, uvCoord);
}
