#version 330

#define LIMIT 100
#define Pow2(x) ((x)*(x))
#define saturate(x) clamp((x),0.0,1.0)

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

vec4 viridisColormap(float k) {
    float x = saturate(k);
    vec4 irr;
    vec4 v31 = vec4(1.0, x, x * x, 0);
    vec4 v32 = v31 * v31.z * x;

    const vec4 krp1 = vec4(0.039908, 0.452562, 69.9753,0);
    const vec4 krp2 = vec4(-0.248869, 0.610199, 12.2464,0);
    const vec4 kr1 = vec4(0.269227, 0.47499, -2.9514,0);
    const vec4 kr2 = vec4(5.37388, -2.13208, 0,0);
    irr.x = dot(kr1, v31) + dot(kr2, v32) +
        krp1.x * exp(-krp1.z * Pow2(x - krp1.y)) +
        krp2.x * exp(-krp2.z * Pow2(x - krp2.y));

    const vec4 kgp1 = vec4(-0.106982, 0.461882, 7.16574,0);
    const vec4 kg1 = vec4(0.0249171, 1.69456, -0.801966,0);
    irr.y = dot(kg1, v31) + kgp1.x * exp(-kgp1.z * Pow2(x - kgp1.y));

    const vec4 kbp1 = vec4(-0.806146, 0.820469, 11.9012,0);
    const vec4 kbp2 = vec4(0.206473, -0.596378, -1.70402,0);
    const vec4 kb1 = vec4(-0.048423, 0.729215, -2.04136,0);
    const vec4 kb2 = vec4(-19.2609, 51.8115, -46.3694,0);
    irr.z = dot(kb1, v31) + dot(kb2, v32) +
        kbp1.x * exp(-kbp1.z * Pow2(x - kbp1.y)) +
        kbp2.x * exp(-kbp2.z * Pow2(x - kbp2.y));

    return saturate(irr);
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
//      color = vec4(1-(float(count) / LIMIT), 0, 0, 0);
      color = viridisColormap(float(count)/LIMIT);
      break;
    }
  }
  outcolor = color;
}
