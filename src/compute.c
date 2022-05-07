#include "compute.h"

static size_t limit = 100;
static mpf_t z_re;
static mpf_t z_im;


static mpf_t tmp_re;
static mpf_t tmp_im;

static bool in_set(mpf_t re, mpf_t im) {
  mpf_mul(tmp_re, re, re);
  mpf_mul(tmp_im, im, im);
  mpf_add(tmp_re, tmp_re, tmp_im);
  mpf_sqrt(tmp_re, tmp_re);
  return mpf_cmp_ui(tmp_re, 2) < 0 ? true : false;
}

/* (a + bi)^2 = a^2 - b^2 + 2abi*/
static void sqr_complex(mpf_t re, mpf_t im) {
  /* use tmp_im as temporary value */
  mpf_mul(tmp_re, re, re);
  mpf_mul(tmp_im, im, im);
  
  /* calc imaginary part */
  mpf_mul(im, re, im);
  mpf_mul_ui(im, im, 2);

  /* calc real part */
  mpf_sub(re, tmp_re, tmp_im);
}

// TODO implement free of inited floats
void init_compute(size_t l) {
  limit = l;
  mpf_init(z_re);
  mpf_init(z_im);
  mpf_init(tmp_re);
  mpf_init(tmp_im);
}

/* f(z) = z^2 + c, z0 = 0
 * r = 2
 * LIMIT = 100
 */
GLuint get_count(mpf_t c_re, mpf_t c_im) {
  GLuint count = 0;
  mpf_set_ui(z_re, 0);
  mpf_set_ui(z_im, 0);
  for(size_t i = 0; i < limit; i++) {
    sqr_complex(z_re, z_im);
    mpf_add(z_re, z_re, c_re);
    mpf_add(z_im, z_im, c_im);
    count++;
    if(!in_set(z_re, z_im)) return count;
  }
  return 0;
}
