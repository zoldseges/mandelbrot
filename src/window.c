#include "window.h"

#include <stdlib.h>
#include <stdio.h>

GLFWwindow *init_window(int width, int height) {
  GLFWwindow *window = NULL;

  /* initialize glfw */
  if(!glfwInit()) {
    fprintf(stderr, "GLFW pooped itself while initializing\n");
    glfwTerminate();
    exit(1);
  }

  /* opengl version */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  /* core profile == no backwards compatibility */
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  /* setup forward compatibility */
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(width,
			    height,
			    "Mandelbrot",
			    NULL,
			    NULL);

  if(!window) {
    fprintf(stderr, "GLFW pooped itself while creating a window\n");
    glfwTerminate();
    exit(1);
  }

  return window;
}
