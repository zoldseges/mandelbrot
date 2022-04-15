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

void print_mat(GLfloat mat4[]) {
  printf("----------------------------\n");
  for(int j = 0; j < 4; j++) {
    printf("[");
    for(int i = 0; i < 4; i++) {
      if( i != 0 ) printf(", ");
      printf("%5.2f", mat4[4*j + i]);
    }
    printf("]\n");
  }
}

void set_identity_matrix(GLfloat mat4[]) {
  for(int i = 0; i < 16; i++) {
    if(i % 5 == 0) mat4[i] = 1;
    else mat4[i] = 0;
  }
}

void multiply_matrix(GLfloat a_mat4[], const GLfloat b_mat4[]) {
  GLfloat a_orig[16];
  memcpy(a_orig, a_mat4, 16*sizeof(GLfloat));
  for(int j = 0; j < 4; j++) {
    for(int i = 0; i < 4; i++) {
      GLfloat acc = 0;
      for(int x = 0; x < 4; x++) {
	acc += a_orig[4*j + x] * b_mat4[4*x + i % 4];
      }
      a_mat4[4*j + i] = acc;
    }
  }
}

void scale_mat(GLfloat mat4[], GLfloat vec3[]) {
  GLfloat transform[16];
  set_identity_matrix(transform);
  for(int i = 0; i < 3; i++) {
    transform[i*5] *= vec3[i];
  }
  multiply_matrix(mat4, transform);
}

void translate_mat(GLfloat mat4[], GLfloat vec3[]) {
  GLfloat transform[16];
  set_identity_matrix(transform);
  for(int i = 0; i < 3; i++) {
    transform[3+i*4] += vec3[i];
  }
  multiply_matrix(mat4, transform);
}

// TODO swich to 2D model instead of 3D
void create_plane(Mesh *mesh) {

  GLfloat vertices[] = {
    -2.0, 2.0, 0.0,
    2.0, 2.0, 0.0,
    2.0, -2.0, 0.0,
    -2.0, -2.0, 0.0,
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

void handle_keys(GLfloat *scale, GLfloat *x, GLfloat *y) {
  GLfloat dscale = 1.01;
  GLfloat dmov = 0.01 / *scale;

  if (is_key_pressed(GLFW_KEY_W)) {
    *y -= dmov;
  }
  if (is_key_pressed(GLFW_KEY_S)) {
    *y += dmov;
  }
  if (is_key_pressed(GLFW_KEY_D)) {
    *x -= dmov;
  }
  if (is_key_pressed(GLFW_KEY_A)) {
    *x += dmov;
  }

  if (is_key_pressed(GLFW_KEY_K)) {
    *scale *= dscale;
  }
  if (is_key_pressed(GLFW_KEY_J)) {
    *scale /= dscale;
  }
}

int main(int argc, char *argv[]) {
  GLFWwindow *window = init_window(800, 600);
  GLuint shader = 0;
  GLuint uniform_model = 0;
  Mesh plane = { 0 };
  GLfloat model[16] = {0};

  /* movement */
  GLfloat scale = 0.5;
  GLfloat x = 0.0;
  GLfloat y = 0.0;
  
  init_context(window);

  compile_shaders(&shader, &uniform_model);
  create_plane(&plane);

  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    
    handle_keys(&scale, &x, &y);

    /* tranformations */
    set_identity_matrix(model);
    GLfloat scale_vec[] = {scale, scale, 0.0};
    scale_mat(model, scale_vec);
    GLfloat trans_vec[] = {x, y, 0.0};
    translate_mat(model, trans_vec);

    glUniformMatrix4fv(uniform_model, 1, GL_TRUE, model);

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
