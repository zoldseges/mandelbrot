#ifndef COMPUTE_H_
#define COMPUTE_H_

#include <string.h>
#include <stdbool.h>
#include <gmp.h>
#include <GL/glew.h>

// TODO use polar system instead?

/* get count of iterations of leaving the set
 * returns 0, if it stays in the set
 */
void set_limit(size_t limit);
GLuint get_count(mpf_t re, mpf_t im);

#endif /* COMPUTE_H_ */
