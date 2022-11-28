#ifndef MIF_UTILS_H
#define MIF_UTILS_H
#include <stdbool.h>
#include <stdint.h>

#define MIF_SIGN(v) (v < 0.0f ? -1.0f : 1.0f)

#ifndef MAX
#define MAX(a, b) (a > b ? a : b)
#endif

#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif

float mif_clamp(float v, float min, float max);

float mif_lerp(float from, float to, float scale);

float mif_smoothstep(float edge0, float edge1, float value);

float mif_fract(float v);

float mif_cos_n(float v);

float mif_sin_n(float v);

float mif_inv(float v);

float mif_gold_ratio_est(float x, float y);

float mif_gold_ratio_est_both(float x, float y);

int mif_cantor(int x, int y);

void mif_decant(int c, int* x, int* y);

bool mif_isodd(int v);

int mif_collatz(int v);

int mif_smoothen(
  const float *data,
  int data_len,
  float* out,
  int64_t out_length,
  int quality
);


int mif_convolve(
  const float* signal,
  int64_t signal_length,

  const float* kernel,
  int64_t kernel_length,

  float* result,
  int64_t result_length
);


void mif_smooth_range(float peak, float* out, int len);

int mif_crush(int seed);

float mif_rand(float seed);

float mif_safe(float v);


float mif_avg(float* values, int64_t length);

float mif_min(float* values, int64_t length, int64_t* index_out);

float mif_max(float* values, int64_t length, int64_t* index_out);

int64_t mif_count_peaks(float* values, int64_t length);


#endif
