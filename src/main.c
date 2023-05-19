#include <mif/utils.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  int n = 15;
  float nums[n];
  memset(&nums, 0, sizeof(float)*n);

  mif_smooth_range_inv(1.0f, nums, n);

  for (int i = 0; i < n; i++) {
    printf("%f\n", nums[i]);
  }
  
  return 0;
}
