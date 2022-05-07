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

void init_screen(struct sscreen *scr, GLuint width, GLuint height);
void free_screen(struct sscreen *scr);
void fill_screen(struct sscreen *scr, double d_blx, double d_bly, double d_trx, double d_try);

#endif SCREEN_H_
