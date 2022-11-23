#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

  float x = 89.0f;
  float y = 55.0f;
  printf("%12.6f\n", mif_gold_ratio(x, y));

  return 0;
}
