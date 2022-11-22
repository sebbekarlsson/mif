#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

  for (int i = 0; i < 100; i++) {
    printf("%12.6f\n", mif_rand(i));
  }

  return 0;
}
