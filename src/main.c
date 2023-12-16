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

  Vector3 a = vector3_random(23.921f, VEC3(0.0f, -0.1f, 0.0f), VEC3(0.0f, 1.0f, 0.0f));

  VEC3_PRINT_PRECISE(a);

  return 0;
}
