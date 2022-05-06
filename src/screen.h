#ifndef SCREEN_H_
#define SCREEN_H_

#include <GL/glew.h>
#include <gmp.h>
#include "compute.h"

struct sscreen {
  GLuint *buffer;
  GLuint width;
  GLuint height;
  mpf_t dx;
  mpf_t dy;
} screen;

void init_screen(screen *scr, GLuint width, GLuint height);
void free_screen(screen *scr);
void fill_screen(screen *scr, char *top_left, char *bot_right);

#endif SCREEN_H_
