#include <mif/utils.h>
#include <mif/macros.h>
#include <mif/constants.h>
#include <mif/noise.h>
#include <mif/linear/vector3/all.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {

  Vector3 a = VEC3(1, 2, 3);
  Vector3 b = VEC3(-1, -2, 1);

  Vector3 c = vector3_lerp(a, b, VEC3(1, 0, 1));
  Vector3Pair p = vector3_tangents_approx(vector3_unit(c));

  VEC3_PRINT_PRECISE(p.a);
  VEC3_PRINT_PRECISE(p.b);
  
  return 0;
}
