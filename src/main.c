#include <stdio.h>
#include <string.h>

#include "window.h"
#include "context.h"
#include "shader.h"



int main(int argc, char *argv[]) {
  GLFWwindow *window = init_window(800, 600);
  init_context(window);

  compile_shaders();
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
  return 0;
}
