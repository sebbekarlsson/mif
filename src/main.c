#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (int argc, char* argv[]) {
  //int dist = mif_lev("hello", "hello");

  //printf("dist: %d\n", dist);

  for (int i = 0; i < 100; i++) {
    float f = mif_random_float(0.0f, 10.0f, (float)i);
    printf("%f\n", f);
  }
  return 0;
}
