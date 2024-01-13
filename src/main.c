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

Vector4 yo() {
  return VEC41(0);
}

int main(int argc, char *argv[]) {


  #if 0
  int x = 42;

  int tmp1 = 0;
  int tmp2 = 0;

  MifBlob data = (MifBlob){ .data = (uint8_t*)&x, .size = sizeof(int) };

  MifBlob compressed = {
    .data = (uint8_t*)&tmp1,
    .size = sizeof(int)
  };
  if (!mif_compress(data, &compressed)) return 1;

  MifBlob decompressed = {
    .data = (uint8_t*)&tmp2,
    .size = sizeof(int)
  };
  if (mif_uncompress(compressed, &decompressed)) {
    printf("%d\n", *(int*)&decompressed.data[0]);
  }


  #endif

  /////////// compress
  const char* name = "john";
  int64_t len = strlen(name);
  
  char buff[256] = {0};
  char buff2[256] = {0};

  int* ptr = (int*)&buff[0];
  int64_t s = 0;
  for (int64_t i = 0; i < len; i+=2) {
    char c1 = name[i];
    char c2 = name[i+1];

    int c = mif_cantor(c1, c2);
    memcpy(ptr, &c, sizeof(int));
    ptr += sizeof(int);
    s += sizeof(int);
  }

  /////////// de-compress
  ptr = (int*)&buff[0];
  int64_t out_len = 0;
  for (int64_t i = 0; i < s; i+=sizeof(int)) {
    int c = *(ptr + i);
    int x = 0;
    int y = 0;
    mif_decant(c, &x, &y);
    buff2[out_len++] = x; 
    buff2[out_len++] = y; 
  }

  printf("%s\n", buff2);

  return 0;
}
