#include "Shader.hpp"

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
  int success;
  char infoLog[512];

  GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
  GLuint fragShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

  id = glCreateProgram();
  glAttachShader(id, vertexShader);
  glAttachShader(id, fragShader);
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    std::cout << "Linking error: " << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);
}

void Shader::activate() {
  glUseProgram(id);
}

std::string Shader::loadShaderSrc(const char *filePath) {
  std::ifstream file;
  std::stringstream buf;
  std::string ret = "";

  file.open(filePath);
  if (file.is_open()) {
    buf << file.rdbuf();
    ret = buf.str();
  } else {
    std::cout << "Could not read " << filePath << std::endl;
  }

  file.close();

  return ret;
}
GLuint Shader::compileShader(const char *filePath, GLenum type) {
  int success;
  char infoLog[512];

  GLuint ret = glCreateShader(type);
  std::string shaderSrc = loadShaderSrc(filePath);
  const GLchar* shader = shaderSrc.c_str();
  glShaderSource(ret, 1, &shader, NULL);
  glCompileShader(ret);

  glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(ret, 512, NULL, infoLog);
    std::cout << "Error with fragment shader compilation: " << infoLog
              << std::endl;
  }

  return ret;
}

void Shader::setMat4(const std::string &name, glm::mat4 val) {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}