#include <mif/utils.h>
#include <mif/macros.h>
#include <mif/constants.h>
#include <mif/noise.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {

  float buff[16] = {0};

  mif_fillf(buff, 16, 1.0 /20000.0, sqrt);

  mif_print_floats(buff, 16
                   , stdout);
  
  return 0;
}
