#include <mif/fft.h>
#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/types.h>
#include <math.h>
#include <stdint.h>

static void mif_swap(float *v1, float *v2) {
  cplx tmp = *v1;
  *v1 = *v2;
  *v2 = tmp;
}

void mif_fftshift(float *data, int count) {
  int k = 0;
  int c = (int)floorf((float)count / 2);
  // For odd and for even numbers of element use different algorithm
  if (count % 2 == 0) {
    for (k = 0; k < c; k++) mif_swap(&data[k], &data[k + c]);
  } else {
    cplx tmp = data[0];
    for (k = 0; k < c; k++) {
      data[k] = data[c + k + 1];
      data[c + k + 1] = data[k + 1];
    }
    data[c] = tmp;
  }
}

void mif_ifftshift(float *data, int count) {
  int k = 0;
  int c = (int)floorf((float)count / 2);
  if (count % 2 == 0) {
    for (k = 0; k < c; k++) mif_swap(&data[k], &data[k + c]);
  } else {
    cplx tmp = data[count - 1];
    for (k = c - 1; k >= 0; k--) {
      data[c + k + 1] = data[k];
      data[k] = data[c + k];
    }
    data[c] = tmp;
  }
}

static void _fft(cplx buf[], cplx out[], int n, int step) {
  if (step < n) {
    _fft(out, buf, n, step * 2);
    _fft(out + step, buf + step, n, step * 2);

    for (int i = 0; i < n; i += 2 * step) {
      cplx t = cexp(-I * M_PI * (double)i / (double)n) * out[(i + step) % n];
      buf[i / 2] = out[i] + t;
      buf[((i + n) / 2)%n] = out[i] - t;
    }
  }
}

void mif_fft_slow(float* buf_in , float* buf_out, cplx* complex_out, int n, int step) {
  for (int i = 0; i < n; i++) complex_out[i] = buf_in[i];

  _fft(complex_out, complex_out, n, 1);

  for (uint32_t i = 0; i < n; i++) {
    buf_out[i] = crealf(complex_out[i]);
  }
}
void mif_fft_cplx(cplx* buf, cplx* out, int n, int step) {
  if (step < n) {
    mif_fft_cplx(out, buf, n, step * 2);
    mif_fft_cplx(out + step, buf + step, n, step * 2);

    for (int i = 0; i < n; i += 2 * step) {
      cplx t = cexp(-I * M_PI * (double)i / (double)n) * out[(i + step) % n];
      buf[i / 2] = out[i] + t;
      buf[((i + n) / 2)%n] = out[i] - t;
    }
  }
}

void mif_fft(float* buf, float* out, int n, int step) {
  mif_fft_cplx((cplx*)buf, (cplx*)out, n, step);
  /*
  if (step < n) {
    mif_fft(out, buf, n, step * 2);
    mif_fft(out + step, buf + step, n, step * 2);

    for (int i = 0; i < n; i += 2 * step) {
      cplx t = cexp(-I * M_PI * i / n) * out[(i + step) % n];
      buf[i / 2] = out[i] + t;
      buf[((i + n) / 2)%n] = out[i] - t;
    }
  }*/
}

int mif_fft_apply_window(float* fft, float* out, int64_t length, MIFFFTWindowFunction window_func) {
  if (!fft || !out || length <= 0 || !window_func) return 0;

  for (int64_t i = 0; i < length; i++) {
    fft[i] = fft[i] * window_func(i, length);
  }

  return 1;
}

float mif_fft_freq(float* fft, int64_t length, float sample_rate) {
  if (!fft ||  length <= 0 || sample_rate <= 0.000001f) return 0.0f;
  int64_t nr_peaks = mif_count_peaks(fft, length);

  return sample_rate * (float)nr_peaks / (float)length;
}

float mif_fft_window_hanning(int64_t i, int64_t frame_len) {
  return (0.5 * (1.0 - cosf(2.0 * M_PI * (float)i / (float)(frame_len - 1))));
}
float mif_fft_window_hamming(int64_t i, int64_t frame_len) {
  return (0.54 - 0.46 * cosf(2.0 * M_PI * (float)i / (float)(frame_len - 1)));
}
