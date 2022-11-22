#include <mif/fft.h>
#include <mif/constants.h>
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
      cplx t = cexp(-I * M_PI * i / n) * out[i + step];
      buf[i / 2] = out[i] + t;
      buf[(i + n) / 2] = out[i] - t;
    }
  }
}

void mif_fft(float buf[], int n) {
  cplx out[n];
  for (int i = 0; i < n; i++) out[i] = buf[i];

  _fft(out, out, n, 1);

  for (uint32_t i = 0; i < n; i++) {
    buf[i] = creal(out[i]);
  }
}
