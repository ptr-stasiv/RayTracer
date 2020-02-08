#define GLEW_STATIC
#include "GL/glew.h"

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <sstream>

namespace graphics
{
  //Read specified file return true if file load successfully
  bool ReadFile(const char* path, std::string& result);

  //Create GLSL shaders(Vertex and Fragment) and return true if there no error
  bool CreateShader(const char* vpath, const char* fpath, uint8_t& id);
}
