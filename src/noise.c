#include <mif/noise.h>
#include <mif/utils.h>
#include <math.h>


#define FLOOR(X) _Generic(X, float: floor_float, V2f: v2_floor)(X)
#define FRACT(X) _Generic(X, float: mif_fract, V2f: v2_fract)(X)
#define SMOOTHSTEP(E0, E1, X) _Generic(X, float: mif_smoothstep, V2f: v2_smoothstep)(E0, E1, X)
#define MIX(VA, VB, F) _Generic((VA), float: mif_lerp, V2f: v2_mix)(VA, VB, F)

static float floor_float(float p) {
  return floorf(p);
}

static V2f v2_floor(V2f p) {
  p.x = floorf(p.x);
  p.y = floorf(p.y);
  return p;
}

static V2f v2_fract(V2f p) {
  p.x = mif_fract(p.x);
  p.y = mif_fract(p.y);
  return p;
}

static V2f v2_smoothstep(float edge0, float edge1, V2f p) {
  p.x = mif_smoothstep(edge0, edge1, p.x);
  p.y = mif_smoothstep(edge0, edge1, p.y);
  return p;
}

static V2f v2_mix(V2f a, V2f b, float f) {
  return V2F(mif_lerp(a.x, b.x, f), mif_lerp(a.y, b.y, f));
}

static V2f v2_add(V2f a, V2f b) {
  return V2F(a.x + b.x, a.y + b.y);
}

static float hash21(V2f p, uint32_t seed) {
  uint32_t x = mif_float_bits_to_uint(p.x);
  uint32_t y = mif_float_bits_to_uint(p.y);
  uint32_t z = mif_permute_uint32(seed);

  return (float)mif_permute_uint32(x * 5013U + y * 1013U + z * 522U) / (float)0xFFFFFFFFU;
}


float mif_noise21(V2f p, uint32_t seed) {
  V2f id = FLOOR(p);
  V2f lv = FRACT(p);
  lv = SMOOTHSTEP(0.0f, 1.0f, lv);

  float a = MIX(hash21(v2_add(id, V2F(0, 0)), seed), hash21(v2_add(id, V2F(1, 0)), seed), lv.x);
  float b = MIX(hash21(v2_add(id, V2F(0, 1)), seed), hash21(v2_add(id, V2F(1, 1)), seed), lv.x);
  return MIX(a, b, lv.y);
}
