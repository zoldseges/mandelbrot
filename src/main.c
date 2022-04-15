#include <stdio.h>
#include <string.h>

#include "window.h"
#include "context.h"
#include "shader.h"

typedef struct Mesh {
  GLuint VBO;
  GLuint VAO;
  GLuint IBO;
} Mesh;

// TODO swich to 2D model instead of 3D
void create_plane(Mesh *mesh) {

  GLfloat vertices[] = {
    -1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, -1.0, 0.0,
    -1.0, -1.0, 0.0,
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,
  };

  glGenVertexArrays(1, &mesh->VAO);
  glBindVertexArray(mesh->VAO);

  glGenBuffers(1, &mesh->IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glGenBuffers(1, &mesh->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  glBindVertexArray(0);
}

int main(int argc, char *argv[]) {
  GLFWwindow *window = init_window(800, 600);
  GLuint shader = 0;
  Mesh plane = { 0 };
  init_context(window);

  shader = compile_shaders();
  create_plane(&plane);
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);

    glBindVertexArray(plane.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane.IBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glUseProgram(0);

    glfwSwapBuffers(window);
  }
  return 0;
}
