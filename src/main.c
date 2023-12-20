#include <mif/utils.h>
#include <mif/macros.h>
#include <mif/constants.h>
#include <mif/noise.h>
#include <mif/linear/vector3/all.h>
#include <mif/linear/vector4/all.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

Vector4 yo() {
  return VEC41(0);
}

int main(int argc, char *argv[]) {


  Vector4 v = VEC4(0, 0, 0, 0);

  v = vector4_set(v, 3, 1.0f);

  VEC4_PRINT_PRECISE(v);

  return 0;
}
