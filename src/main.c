#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

  float x = 0.8f;
  float y = 0.005f;
  printf("%12.6f, \n", mif_gold_ratio_est(x,  y));

  return 0;
}
