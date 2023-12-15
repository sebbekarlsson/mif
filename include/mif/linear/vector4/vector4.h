#ifndef MIF_LINEAR_VECTOR4_H
#define MIF_LINEAR_VECTOR4_H
#include <stdint.h>

typedef struct {
  float x;
  float y;
  float z;
  float w;
} Vector4;

typedef struct {
  Vector4 a;
  Vector4 b;
} Vector4Pair;

typedef struct {
  Vector4 a;
  Vector4 b;
  Vector4 c;
} Vector4Triple;

typedef struct {
  Vector4 furthest;
  Vector4 closest;

  int64_t furthest_index;
  int64_t closest_index;
} Vector4Support;

typedef struct {
  Vector4Support a;
  Vector4Support b;
  Vector4 point;
} Vector4SupportPair;

typedef struct {
  int64_t index;
  Vector4 v;
} Vector4Indexed;

typedef struct {
  int64_t index_a;
  int64_t index_b;

  Vector4 a;
  Vector4 b;
} Vector4PairIndexed;

#endif
