#include <mif/constants.h>
#include <mif/utils.h>
#include <mif/fft.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (int argc, char* argv[]) {
  int dist = mif_lev("hello", "hello");

  printf("dist: %d\n", dist);

  return 0;
}
