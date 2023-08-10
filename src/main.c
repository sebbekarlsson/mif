#include <mif/utils.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("%d\n", mif_permute_uint32(mif_permute_uint32(1231235U)*45192U));
  return 0;
}
