#ifndef COMPUTE_H_
#define COMPUTE_H_

#include <string.h>
#include <gmp.h>
#include <GL/glew.h>

typedef struct spoint = point;

struct spoint {
  mpf_t x;
  mpf_t y;
};

#define LIMIT 100

/* get count of iterations of leaving the set
 * returns 0, if it stays in the set
 */
GLuint get_count(mpf_t re, mpf_t im);

#endif /* COMPUTE_H_ */
