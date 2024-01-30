#include <mif/utils.h>
#include <mif/macros.h>
#include <mif/constants.h>
#include <mif/noise.h>
#include <mif/linear/vector3/all.h>
#include <mif/linear/vector4/all.h>
#include <mif/compress.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


int main(int argc, char *argv[]) {

  Vector3 v = VEC3(1, 1, 0.9999f);


  printf("uniform: %s.\n", vector3_is_uniform(v, 0.003f) ? "true" : "false");


  return 0;
}
