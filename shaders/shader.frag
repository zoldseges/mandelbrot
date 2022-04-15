#version 330

#define LIMIT 100

in vec4 frag_pos;

out vec4 outcolor;

struct Comp {
  float re;
  float im;
};

Comp add(Comp a, Comp b) {
  return Comp(a.re + b.re, a.im + b.im);
}

Comp mul(Comp a, Comp b) {
  return Comp(a.re * b.re - a.im * b.im, a.re * b.im + b.re * a.im);
}

float dist(Comp a) {
  return a.re * a.re + a.im * a.im;
}

void main()
{
  vec4 color = vec4(0,0,0,0);
  Comp c = Comp(frag_pos.x, frag_pos.y);
  Comp z = Comp(0, 0);
  int count = 0;
  for(count = 0; count <= LIMIT; count++) {
    z = add(mul(z, z), c);
    if (dist(z) >= 4) {
      color = vec4(float(count) / LIMIT, 0, 0, 0);
      break;
    }
  }
  outcolor = color;
}
