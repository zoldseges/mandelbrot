#include "shader.h"

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

static void add_shader(GLuint program,
		       const char *shader_path,
		       GLenum shader_type) {
  GLchar *shader_code = 0;
  GLuint shader = 0;
  GLint result = 0;
  GLchar error_log[1024] = { 0 };
  
  FILE *fp = NULL;
  size_t code_len = 0;
  
  shader = glCreateShader(shader_type);
  if(!shader) {
    printf("Error initializing shader process\n");
    exit(1);
  }

  // read shader code from file
  fp = fopen(shader_path, "r");
  if(fp == NULL) {
    fprintf(stderr, "Error: couldn't open %s\n", shader_path);
    exit(1);
  }
  fseek(fp, 0, SEEK_END);
  code_len = ftell(fp);
  shader_code = calloc(code_len + 1, sizeof(char));
  if(!shader_code) {
    fprintf(stderr,
	    "Error: couldn't alloc mem for the contents of %s\n",
	    shader_path);
    exit(1);
  }
  rewind(fp);
  fread(shader_code, sizeof(char), code_len, fp);
  fclose(fp);
  
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  glShaderSource(shader, 1, &shader_code, &code_len);
  #pragma GCC diagnostic pop
  free(shader_code);
       
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if(!result) {
    glGetShaderInfoLog(shader, sizeof(error_log), NULL, error_log);
    fprintf(stderr,
	    "Error during compiling the shader %s of type %d: `%s`\n",
	    shader_path,
	    shader_type,
	    error_log
	    );
  }

  glAttachShader(program, shader);
}

GLuint compile_shaders() {
  GLuint shader = 0;
  GLint result = 0;
  GLchar error_log[1024] = { 0 };

  shader = glCreateProgram();
  if(!shader) {
    fprintf(stderr, "Error initializing shader program\n");
    exit(1);
  }

  add_shader(shader, "shaders/shader.vert", GL_VERTEX_SHADER);
  add_shader(shader, "shaders/shader.frag", GL_FRAGMENT_SHADER);

  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if(!result) {
    glGetProgramInfoLog(shader, sizeof(error_log), NULL, error_log);
    printf("error linking program: `%s`\n", error_log);
    exit(1);
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if(!result) {
    glGetProgramInfoLog(shader, sizeof(error_log), NULL, error_log);
    printf("error validating program: `%s`\n", error_log);
    exit(1);
  }

  return shader;
}
