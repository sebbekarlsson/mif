#include <mif/utils.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  printf("%12.6f\n", mif_slt(0.2f, 0.3f, 0.5f));
  
  return 0;
}
