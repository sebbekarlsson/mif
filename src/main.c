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

  Vector3U32 stuff = (Vector3U32){ 381U, 77U, 931U, 116U };


  stuff = vector3U32_permute(stuff);

  printf("%d, %d, %d\n", stuff.x, stuff.y, stuff.z);

  return 0;
}
