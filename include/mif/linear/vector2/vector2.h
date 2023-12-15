#ifndef MIF_LINEAR_VECTOR3_H
#define MIF_LINEAR_VECTOR3_H
#include <stdint.h>

typedef struct {
  float x;
  float y;
  float z;
  float w;
} Vector2;

typedef struct {
  Vector2 a;
  Vector2 b;
} Vector2Pair;

typedef struct {
  Vector2 a;
  Vector2 b;
  Vector2 c;
} Vector2Triple;

typedef struct {
  Vector2 furthest;
  Vector2 closest;

  int64_t furthest_index;
  int64_t closest_index;
} Vector2Support;

typedef struct {
  Vector2Support a;
  Vector2Support b;
  Vector2 point;
} Vector2SupportPair;

typedef struct {
  int64_t index;
  Vector2 v;
} Vector2Indexed;

typedef struct {
  int64_t index_a;
  int64_t index_b;

  Vector2 a;
  Vector2 b;
} Vector2PairIndexed;

#endif
