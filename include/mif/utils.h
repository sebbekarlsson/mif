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

#define MIF_ABS(v) ((v) < 0 ? ((v) * -1) : (v))

float mif_clamp(float v, float min, float max);

float mif_lerp(float from, float to, float scale);

float mif_smoothstep(float edge0, float edge1, float value);

float mif_fract(float v);

float mif_cos_n(float v);

float mif_sin_n(float v);

float mif_inv(float v);

float mif_sigmoid(float x);

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

void mif_smooth_range_inv(float peak, float* out, int len);

int mif_crush(int seed);

float mif_rand(float seed);

float mif_random_float(float min, float max, float seed);

float mif_safe(float v);

float mif_avg(float* values, int64_t length);

float mif_avg_abs(float* values, int64_t length);

float mif_min(float* values, int64_t length, int64_t* index_out);

float mif_max(float* values, int64_t length, int64_t* index_out);

float mif_max_abs(float* values, int64_t length, int64_t* index_out);

int64_t mif_count_peaks(float* values, int64_t length);

float mif_get_hash(int64_t index);
float mif_get_hash2(int64_t index);

int mif_lev(const char* a, const char* b);

uint32_t mif_float_bits_to_uint(float f);

#endif
