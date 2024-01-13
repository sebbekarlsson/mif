#include <mif/compress.h>
#include <mif/macros.h>
#include <mif/utils.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

static inline int cantor(int16_t k1, int16_t k2) {
  return ((k1 + k2) * (k1 + k2 + 1)) / 2 + k2;
}

static inline void decant(int16_t c, int16_t* x, int16_t* y) {
  int w = (int)floorf((sqrt((double)c * 8.0 + 1.0) - 1.0) / 2.0);
  *y = c - (w * (w + 1)) / 2;
  *x = w - *y;
}

int mif_compress(MifBlob data, MifBlob* out) {
  MIF_ASSERT_RETURN(data.data != 0, 0);
  MIF_ASSERT_RETURN(data.size > 0, 0);
  MIF_ASSERT_RETURN(out->data != 0, 0);
  MIF_ASSERT_RETURN(out->size >= (data.size / 2) + 1, 0);


  uint8_t* ptr = &out->data[0];
  
  for (int64_t i = 0; i < data.size; i+=2) {
    uint8_t c1 = data.data[i];
    uint8_t c2 = data.data[(i+1)%data.size];
    int16_t c = cantor(c1, c2);

    memcpy(ptr, &c, sizeof(int16_t)); ptr += sizeof(int16_t);
  }

  return 1;
}

int mif_uncompress(MifBlob data, MifBlob* out) {
  MIF_ASSERT_RETURN(data.data != 0, 0);
  MIF_ASSERT_RETURN(data.size > 0, 0);
  MIF_ASSERT_RETURN(out->data != 0, 0);
  //MIF_ASSERT_RETURN(out->size >= (data.size * 2), 0);

  int64_t out_size = 0;

  uint8_t* ptr = &out->data[0];
  
  for (int64_t i = 0; i < data.size/2; i++) {
    uint8_t c1 = data.data[i];
    int16_t x = 0;
    int16_t y = 0;

    decant(c1, &x, &y);

    printf("c1: %d, x: %d, y: %d\n", c1, x, y);
    memcpy(ptr, &x, sizeof(int16_t)); ptr += sizeof(int16_t);
    memcpy(ptr, &y, sizeof(int16_t)); ptr += sizeof(int16_t);
    //out_size += sizeof(uint8_t)*2;
  }

  out->size = out_size;

  return 1;
}
