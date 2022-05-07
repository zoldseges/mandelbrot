#include "compute.h"

static size_t limit = 100;
static mpf_t z_re;
static mpf_t z_im;


static bool in_set(mpf_t re, mpf_t im) {
  mpf_pow_ui(re, re, 2);
  mpf_pow_ui(im, im, 2);
  mpf_add(re, re, im);
  mpf_sqrt(re, re);
  return mpf_cmp_ui(re, 2) > 2 ? true : false;
}

static mpf_t sqr_re;
static mpf_t sqr_im;

/* (a + bi)^2 = a^2 - b^2 + 2abi*/
static void sqr_complex(mpf_t re, mpf_t im) {
  /* use sqr_im as temporary value */
  mpf_mul(sqr_re, re, re);
  mpf_mul(sqr_im, im, im);
  
  /* calc imaginary part */
  mpf_mul(im, re, im);
  mpf_mul_ui(im, im, 2);

  /* calc real part */
  mpf_sub(re, sqr_re, sqr_im);
}

void init_compute(size_t l) {
  limit = l;
  mpf_init(z_re);
  mpf_init(z_im);
  mpf_init(sqr_re);
  mpf_init(sqr_im);
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
    
    if(!in_set(c_re, c_im)) return 0;
    count++;
  }
  return count;
}
