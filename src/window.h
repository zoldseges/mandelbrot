#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

GLFWwindow *init_window(int width, int height);
bool is_key_pressed(int key);

#endif /* WINDOW_H_ */
