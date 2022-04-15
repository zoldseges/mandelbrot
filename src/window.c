#include "window.h"

#include <stdlib.h>
#include <stdio.h>

#define KEY_COUNT 1024

static bool glob_keys[KEY_COUNT];

static void handle_resize(GLFWwindow *window, int width, int height) {
  int min = width < height ? width : height;
  glViewport(0, 0, min, min);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static void handle_keys(GLFWwindow* window,
			int key,
			int code,
			int action,
			int mode) {
  if(key >= 0 && key < KEY_COUNT) {
    if(action == GLFW_PRESS) {
      glob_keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      glob_keys[key] = false;
    }
  }
}
#pragma GCC diagnostic pop

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

  /* callbacks */
  glfwSetFramebufferSizeCallback(window, handle_resize);
  glfwSetKeyCallback(window, handle_keys);
  return window;
}

bool is_key_pressed(int key) {
  return glob_keys[key];
}
