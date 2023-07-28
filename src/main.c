#include <mif/utils.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  const char* a = "hello world";
  const char* b = "Hello worlc";

  float similar = mif_strcmp(a, b, true);
  printf("similar: %1.6f\n", similar);
  return 0;
}
