#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

  float sample_rate = 44100.0f;
  int frame_size = 512;
  int64_t one_second = (int64_t)sample_rate;

  float* buff = (float*)calloc(one_second, sizeof(float));

  float freq = 440.0f;



  for (int i = 0; i < one_second; i++) {
    float k = (float)i / sample_rate;
    float time = (float)i / (float)one_second;
    buff[i] = sinf(freq * MIF_TAU * k);
  }


  mif_fft(buff, buff, frame_size);
  float peaks = (float)mif_count_peaks(buff, one_second);
  printf("%12.6f\n", peaks);
  printf("%12.6f\n", mif_fft_freq(buff, one_second, sample_rate));

  //mif_fft_apply_window(buff, buff, 512, mif_fft_window_hamming);

 // printf("max: %12.6f\n", mif_max(buff, 512));

  //mif_ifftshift(buff, 512);

  return 0;
}
