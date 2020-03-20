#include "shader_manager.h"

namespace graphics
{
  bool ReadFile(const char* path, std::string& result)
  {
    std::ifstream file;
    file.open(path);

    if(!file.is_open())
      return false;

    std::stringstream ss;
    ss << file.rdbuf();

    result = ss.str();
    return true;
  }

  bool CreateShader(const char* vpath, const char* fpath, uint8_t& id)
  {
    std::string vstr;
    std::string fstr;

    if(!ReadFile(vpath, vstr))
      return false;
    if(!ReadFile(fpath, fstr))
      return false;

    char* sources[2];
    sources[0] = const_cast<char*>(vstr.c_str());
    sources[1] = const_cast<char*>(fstr.c_str());

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &sources[0], nullptr);
    glCompileShader(vertexShader);

    GLint status = 0;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(!status)
    {
      glDeleteShader(vertexShader);
      return false;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &sources[1], nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(!status)
    {
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);
      return false;
    }

    GLuint resID = glCreateProgram();
    glAttachShader(resID, vertexShader);
    glAttachShader(resID, fragmentShader);
    glLinkProgram(resID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(resID, GL_LINK_STATUS, &status);
    if(!status)
      return false;

    id = resID;
    return true;
  }
}
