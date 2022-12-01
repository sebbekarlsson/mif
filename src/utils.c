#include <mif/utils.h>
#include <mif/constants.h>
#include <mif/macros.h>
#include <mif/hash.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

float mif_random_float(float min, float max, float seed) {
  float* buff = (float*)mif_hash_data;
  int64_t buff_len = mif_hash_data_len / sizeof(float);
  float max_v = mif_max_abs(buff, buff_len, 0);

  int crushed = MIF_ABS(mif_crush((int)((seed * 0.1f) / 2) + (MIF_PI*6)));
  crushed = (int)((float)crushed * max_v);
  int idx0 = crushed % buff_len;

  float a = fabsf(buff[idx0]);

  int idx1 = (int)(a * (crushed / 2)) % buff_len;

  float b = fabsf(buff[idx1]);

  int idx2 = (int)(a * b * (idx0)) % buff_len;

  float c = fabsf(buff[idx2]);


  float d = ((a + b + c) / 3.0f) / fmaxf(max_v, 0.00001f);
  float e = mif_fract(cosf((float)(crushed) * M_PI));
  float f = mif_fract(sinf(seed / M_PI) / M_PI);



  float scale = mif_fract(atan2f(atan2f(d, e), f));//rand() / (float) RAND_MAX; /* [0, 1.0] */
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


  float target = 1.0f;
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
