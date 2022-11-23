#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

  float x = 89.1f;
  float y = 55.3f;
  printf("%12.6f, %12.6f, %12.6f\n", mif_gold_ratio_factor(x, y), mif_gold_ratio(x, y), mif_gold_ratio_est(x, y));

  return 0;
}
