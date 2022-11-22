#include <mif/utils.h>
#include <mif/constants.h>
#include <math.h>

float mif_clamp(float v, float min, float max) {
  return fmaxf(min, fminf(max, v));
}

float mif_lerp(float from, float to, float scale) {
  return from + (to - from) * scale;
}

float mif_smoothstep(float edge0, float edge1, float value) {
  value = mif_clamp((value - edge0) / (edge1 - edge0), 0.0f, 1.0f);
  return value * value * (3.0f - 2.0 * value);
}

float mif_fract(float v) {
  return v - floorf(v);
}

float mif_cos_n(float v) {
  return 0.5f + (0.5f * cosf(v));
}

float mif_sin_n(float v) {
  return 0.5f + (0.5f * sinf(v));
}

float mif_inv(float v) {
  return (1.0f / fmaxf(fabsf(v), MIF_TINY_FLOAT)) * MIF_SIGN(v);
}

float mif_gold_ratio(float x, float y) {
  if (fabsf(x) <= MIF_TINY_FLOAT) return 0.0f;
  float r = (x + y) / x;
  float d = fabs(MIF_GOLD - r);

  return 1.0f - d;
}

int mif_cantor(int k1, int k2) {
  return ((k1 + k2) * (k1 + k2 + 1)) / 2 + k2;
}

void mif_decant(int c, int* x, int* y) {
  int w = floorf((sqrtf(c * 8 + 1) - 1) / 2);
  *y = c - (w * (w + 1)) / 2;
  *x = w - *y;
}

bool mif_isodd(int v) {
  return v % 2 != 0;
}

int mif_collatz(int v) {
  return mif_isodd(v) ? ((3 * v) + 1) : (v / 2);
}

void mif_convolve(float *invec, int len, float *kernel, int kernel_len, float dry, float wet) {
  for (uint64_t i = kernel_len / 2; i < len - kernel_len / 2; ++i) {
    for (uint64_t j = 0; j < kernel_len + 1; j++) {
      invec[i - kernel_len / 2] =
          ((invec[i - kernel_len / 2] * dry) +
           (wet * (invec[i - kernel_len / 2 + j] * (kernel[j]))));
    }
  }
}

void mif_smoothen(float *data, int data_len, float dry, float wet) {
  float kernel[15] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.5f, 0.6f, 1.0f,
                      0.6f, 0.5f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f};

  mif_convolve(data, data_len, kernel, 15, dry, wet);
}
