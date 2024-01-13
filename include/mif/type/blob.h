#ifndef MIF_BLOB_H
#define MIF_BLOB_H
#include <stdint.h>

typedef struct {
  uint8_t* data;
  int64_t size;
} MifBlob;
#endif
