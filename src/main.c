#include <mif/utils.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  printf("%12.6f\n", mif_smin_fixed(0.5f, 0.8f, 9.5f));
  
  return 0;
}
