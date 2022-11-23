#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

  float x = 88.0f;
  float y = 59.0f;
  printf("%12.6f, \n", mif_gold_ratio_est_both(y,  x));

  return 0;
}
