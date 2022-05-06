#include "screen.h"

// TODO not setting precision beforehand (mpf_set_default_prec) might be necessary
void init_screen(struct sscreen *scr, GLuint width, GLuint height){
  scr->width = width;
  scr->height = height;
  mpf_init(scr->dx);
  mpf_init(scr->dy);
  scr->buffer = calloc(width * height, sizeof(mpf_t));
  for(int i = 0; i < width*height, i++) mpf_init(scr->buffer[i]);
}

void free_screen(struct sscreen *scr) {
  for(int i = 0; i < screen->width * screen->height, i++) mpf_clear(screen->buffer[i]);
  mpf_clear(scr->dx);
  mpf_clear(scr->dy);
  free(scr->buffer);
}


// TODO use string instead of double for real more precision
void fill_screen(screen *scr,
		 double *d_blx, // string_bottom-left_x
		 double *d_bly,
		 double *d_trx,
		 double *d_try) {
  mpf_t blx;
  mpf_t bly;
  mpf_t trx;
  mpf_t try;

  mpf_set_d(blx, d_blx);
  mpf_set_d(bly, d_bly);
  mpf_set_d(trx, d_trx);
  mpf_set_d(try, d_try);

  mpf_sub(scr->dx, d_blx, d_trx);
  mpf_sub(scr->dy, d_bly, d_try);

  mpf_div_ui(scr->dx, scr->dx, scr->width);
  mpf_div_ui(scr->dy, scr->dy, scr->height);

  // TODO would it run faster, if scr->width would be "extracted" to a local variable?
  for(GLuint y = 0; y < scr->height; y++) {
    for(GLuint x = 0; x < scr->width; x++) {
      mpf_add(scr->buffer[y*scr->width + x], 
    }
  }
}
