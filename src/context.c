#include "context.h"

#include <stdio.h>
#include <stdlib.h>

void init_context(GLFWwindow *window) {
  int buffer_width = 0;
  int buffer_height = 0;

  glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;

  if(glewInit() != GLEW_OK) {
    fprintf(stderr, "Glew init was too much to ask for\n");
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  glViewport(0, 0, buffer_width, buffer_height);
}
