#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>

#include "Shader.hpp"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
  int success;
  char infoLog[512];

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "ProjectAstral", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  Shader shader("../assets/vertex_core.glsl", "../assets/fragment_core.glsl");
  Shader shader2("../assets/vertex_core.glsl", "../assets/fragment_core2.glsl");

  // Vertex array
  float vertices[] = {0.5f, 0.5f, 0.0f, 1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
                      0.0f, 0.5f, 1.0f, 0.75f, -0.5f, -0.5f, 0.0f,  0.6f,
                      1.0f, 0.2f, 0.5f, -0.5f, 0.0f,  1.0f,  0.2f,  1.0f};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  // VAO, VBO, EBO
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind VAO
  glBindVertexArray(VAO);
  // Bind VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Bind EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Set attribute pointer
  // Positions
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // Colors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 trans2 = glm::mat4(1.0f);
  trans2 = glm::scale(trans2, glm::vec3(1.5f));
  shader.activate();
  shader.setMat4("transform", trans);
  shader2.activate();
  shader2.setMat4("transform", trans);

  while (!glfwWindowShouldClose(window)) {
    // Input
    processInput(window);

    // Rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f));
    trans2 = glm::rotate(trans2, glm::radians((float)glfwGetTime() / -100.0f),
                         glm::vec3(0.0f, 0.0f, 1.0f));
    shader.activate();
    shader.setMat4("transform", trans);
    shader2.activate();
    shader2.setMat4("transform", trans2);

    // Draw shapes
    glBindVertexArray(VAO);
    shader.activate();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    shader2.activate();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,
                   (void *)(3 * sizeof(GLuint)));

    // Send new frame to window
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
