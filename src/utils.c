#include <mif/utils.h>
#include <mif/constants.h>
#include <mif/macros.h>
#include <mif/hash.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float mif_sign(float x) {
  return x < 0 ? -1 : 1;
}

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
  return mif_safe(v - floorf(v));
}

float mif_cos_n(float v) {
  return 0.5f + (0.5f * cosf(v));
}

float mif_sin_n(float v) {
  return 0.5f + (0.5f * sinf(v));
}

float mif_inv(float v) {
  return mif_safe((1.0f / fmaxf(fabsf(v), MIF_TINY_FLOAT)) * MIF_SIGN(v));
}


float mif_sigmoid(float x) {
  return 1.0f / (1.0 + expf(-x));
}

float mif_gold_ratio_est(float x, float y) {
  if (fabsf(x) <= MIF_TINY_FLOAT) return 0.0f;
  float r = (x + y) / x;

  if (r < MIF_GOLD / 2.0f) return 0.0f;
  if (r > MIF_GOLD * 2.0f) return 0.0f;

  float dist = fabsf(r - (float)MIF_GOLD);

  return mif_smoothstep(0.0f, 1.0f, fmaxf(0.0f, 1.0f - dist));

}

float mif_gold_ratio_est_both(float x, float y) {
  return fmaxf(mif_gold_ratio_est(x, y), mif_gold_ratio_est(y, x));
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


int mif_convolve(
  const float* signal,
  int64_t signal_length,

  const float* kernel,
  int64_t kernel_length,

  float* result,
  int64_t result_length
){

  int64_t wanted_length = signal_length + kernel_length - 1;

  if (result_length < wanted_length) {
    MIF_WARNING(stderr, "result_length must be at least %ld\n", wanted_length);
    return 0;
  }

  size_t n = 0;
  for (n = 0; n < signal_length + kernel_length - 1; n++)
  {
    size_t kmin, kmax, k;

    result[n] = 0;

    kmin = (n >= kernel_length - 1) ? n - (kernel_length - 1) : 0;
    kmax = (n < signal_length - 1) ? n : signal_length - 1;

    for (k = kmin; k <= kmax; k++)
    {
      result[n] += signal[k] * kernel[n - k];
    }
  }

  return 1;
}


int mif_smoothen(
  const float *data,
  int data_len,
  float* out,
  int64_t out_length,
  int quality
) {
  const int kernel_len = MAX(quality, 3);

  float kernel[kernel_len];
  mif_smooth_range(1.0f, kernel, kernel_len);

  return mif_convolve(data, data_len, kernel, kernel_len, out, out_length);
}

void mif_smooth_range(float peak, float* out, int len) {
  if (!out || len <= 0) return;

  len += 1;


  float L = (float)len;
  float half = L / 2.0f;


  for (int i = 1; i < len; i++) {
    float g = (float)i;

    float f = fabsf((half - g)) / (half);

    float v = peak - f*peak;

    out[MAX(0, i-1)] = v;
  }
}

void mif_smooth_range_inv(float *out, int len) {
  if (!out || len <= 0) return;

  int half = len / 2;
  
  for (int i = 0; i < half; i++) {
    out[i] = 1.0f - (((float)i) / ((float)half));
  }

  for (int i = 0; i < half; i++) {
    out[MAX(0, len - (1 + i))] = out[i];
  }
}

int mif_crush(int seed) {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

float mif_rand(float seed) {
  seed += 1.0f;
  int s = (int)ceilf(seed);
  float g = mif_crush(s);


  return mif_safe(mif_fract(cosf(seed) * mif_safe(sqrtf(g))));
}

float mif_get_hash(int64_t index) {
  index = MIF_ABS(index);
  float* buff1 = (float*)mif_hash_data;
  int64_t buff1_len = mif_hash_data_len / sizeof(float);

  return buff1[index % buff1_len];
}

float mif_get_hash2(int64_t index) {
  index = MIF_ABS(index);
  float* buff2 = (float*)mif_hash_data2;
  int64_t buff2_len = mif_hash_data2_len / sizeof(float);

  return buff2[index % buff2_len];
}

uint32_t mif_float_bits_to_uint(float f) {
  union MifFloatUint32 { float f; uint32_t i; };
  union MifFloatUint32 converted;
  converted.f = f;
  return converted.i;
}

float mif_random_float(float min, float max, float seed) {
  uint32_t s = (11U+mif_float_bits_to_uint(seed)) * 5358U;
  uint32_t x = ~s * 3U;
  uint32_t y = 503U * (x << 3U) + s;
  s ^= (s << 17U); s ^= (s >> 13U); s ^= (s << 5U);
  x ^= (x << 4U); x ^= (x >> 2U); x ^= (x << 15U);
  y ^= (y << 11U); y ^= (y >> 9U); y ^= (y << 3U);
  uint32_t n = (s * x + y) + (x ^ y) + (y ^ s);
  uint32_t z = ~n * 42891U;
  n ^= (n << 2U); n ^= (n >> 9U); n ^= (n << 2U);
  float scale = (float)(n*1013U+z) / (float)0xFFFFFFFFU;
  return mif_clamp(min + scale * ( max - min ), min, max);
}

float mif_safe(float v) {
  if (!(isinf(v) || isnan(v))) return v;
  return MIF_TINY_FLOAT;
}

float mif_avg(float* values, int64_t length) {
  if (!values || length <= 0) return 0.0f;


  float avg = 0.0f;

  for (int64_t i = 0; i < length; i++) {
    avg += values[i];
  }

  avg /= (float)length;

  return avg;
}

float mif_avg_abs(float* values, int64_t length) {
  if (!values || length <= 0) return 0.0f;
  float avg = 0.0f;

  for (int64_t i = 0; i < length; i++) {
    avg += fabsf(values[i]);
  }

  avg /= (float)length;

  return avg;
}

float mif_min(float* values, int64_t length, int64_t* index_out) {
  if (!values || length <= 0) return 0.0f;


  float min = INFINITY;

  for (int64_t i = 0; i < length; i++) {
    float v = values[i];
    if (v < min) {
      if (index_out != 0) {
        *index_out = i;
      }
      min = v;
    }
  }

  return min;
}

float mif_max(float* values, int64_t length, int64_t* index_out) {
  if (!values || length <= 0) return 0.0f;

  float max = -INFINITY;

  for (int64_t i = 0; i < length; i++) {
    float v = values[i];

    if (v > max) {
      if (index_out != 0) {
        *index_out = i;
      }
      max = v;
    }
  }

  return max;
}

float mif_max_abs(float* values, int64_t length, int64_t* index_out) {
  if (!values || length <= 0) return 0.0f;

  float max = -INFINITY;

  for (int64_t i = 0; i < length; i++) {
    float v = fabsf(values[i]);

    if (v > max) {
      if (index_out != 0) {
        *index_out = i;
      }
      max = v;
    }
  }

  return max;
}

int64_t mif_count_peaks(float* values, int64_t length) {
  if (!values || length <= 0) return 0;

  float max_v = mif_max_abs(values, length, 0);

  float target = max_v;
  float tolerance = 0.00001f;
  int64_t nr_peaks = 0;

  int last_sign = 42;

  for (int64_t i = 0; i < length; i++) {
    float s = values[i];

    int sign = s < 0.0 ? -1 : 1;

    if (ceilf(s) == 1 && sign != last_sign) {
      nr_peaks += sign;
    }

    last_sign = sign;
  }

  return nr_peaks;
}

static inline int mif_lev_(const char* a, const char* b, int la, int lb) {
  if (la <= 0) return lb;
  if (lb <= 0) return la;
  if (a[la-1] == b[lb-1]) return mif_lev_(a, b, la-1, lb-1);
  int d1 = mif_lev_(a, b, la-1, lb) + 1;
  int d2 = mif_lev_(a, b, la, lb-1) + 1;
  int d3 = mif_lev_(a, b, la-1, lb-1) + 1;
  return MIN(d1, MIN(d2, d3));
}

int mif_lev(const char* a, const char* b) {
  return mif_lev_(a, b, strlen(a), strlen(b));
}

float mif_sgt(float a, float b, float s) {
  float h = mif_clamp(0.5f + 0.5f * (a - b) / s, 0.0f, 1.0f);
  return mif_lerp(0.0, 1.0, h*h*(3.0f-2.0f*h));
}

float mif_slt(float a, float b, float s) {
  float h = mif_clamp(0.5f + 0.5f * (b - a) / s, 0.0f, 1.0f);
  return mif_lerp(0.0f, 1.0f, h*h*(3.0f-2.0f*h));
}

float mif_smin(float a, float b, float k) {
    float h = mif_clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
    return mif_lerp(b, a, h) - k * h * (1.0 - h);
}

float mif_smax(float a, float b, float k) {
    float h = mif_clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
    return mif_lerp(a, b, h) + k * h * (1.0 - h);
}

float mif_smin_fixed(float a, float b, float k) {
  float v1 = mif_smin(a, b, k);

  float m = fminf(a, b);
  int sig = (int)mif_sign(m);

  if ((int)mif_sign(v1) != sig)
    v1 *= -1;

  return v1;
}
float mif_smax_fixed(float a, float b, float k) {
  float v1 = mif_smax(a, b, k);

  float m = fmaxf(a, b);
  int sig = (int)mif_sign(m);

  if ((int)mif_sign(v1) != sig)
    v1 *= -1;

  return v1;
}
