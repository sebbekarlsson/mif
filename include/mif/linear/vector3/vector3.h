#ifndef MIF_LINEAR_VECTOR3_H
#define MIF_LINEAR_VECTOR3_H
#include <stdint.h>

typedef struct {
  float x;
  float y;
  float z;
  float w;
} Vector3;

typedef struct {
  uint32_t x;
  uint32_t y;
  uint32_t z;
  uint32_t w;
} Vector3U32;

typedef struct {
  Vector3 a;
  Vector3 b;
} Vector3Pair;

typedef struct {
  Vector3 a;
  Vector3 b;
  Vector3 c;
} Vector3Triple;

typedef struct {
  Vector3 furthest;
  Vector3 closest;

  int64_t furthest_index;
  int64_t closest_index;
} Vector3Support;

typedef struct {
  Vector3Support a;
  Vector3Support b;
  Vector3 point;
} Vector3SupportPair;

typedef struct {
  int64_t index;
  Vector3 v;
} Vector3Indexed;

typedef struct {
  int64_t index_a;
  int64_t index_b;

  Vector3 a;
  Vector3 b;
} Vector3PairIndexed;

#endif
