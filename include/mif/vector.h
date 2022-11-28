#ifndef MIF_VECTOR_H
#define MIF_VECTOR_H
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  float x;
  float y;
  float z;
  float w;
} V3f;

#define V3F(x, y, z)((V3F){ x, y, z })


#endif
