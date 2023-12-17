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


  Vector3 r = vector3_random(VEC3(3.3f, 11.381f, 0.3812f), 0.0f, 1.0f);

  VEC3_PRINT_PRECISE(r);

  return 0;
}
