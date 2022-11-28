#ifndef MIF_FFT_H
#define MIF_FFT_H
#include <stdint.h>
void mif_fft(float* buf_in , float* buf_out, int n);
void mif_ifftshift(float *data, int count);
void mif_fftshift(float *data, int count);


float mif_fft_freq(float* fft, int64_t length, float sample_rate);

typedef float (*MIFFFTWindowFunction)(int64_t i, int64_t frame_len);

float mif_fft_window_hanning(int64_t i, int64_t frame_len);
float mif_fft_window_hamming(int64_t i, int64_t frame_len);

int mif_fft_apply_window(float* fft, float* out, int64_t length, MIFFFTWindowFunction window_func);
#endif
