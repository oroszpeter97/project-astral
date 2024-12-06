#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Shader {
public:
  unsigned int id;

  Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
  void activate();

  std::string loadShaderSrc(const char *filePath);
  GLuint compileShader(const char *filePath, GLenum type);

  void setMat4(const std::string &name, glm::mat4 val);
};

#endif