#include <mif/linear/vector2/operations.h>
#include <mif/linear/vector2/macros.h>
#include <mif/utils.h>
#include <math.h>

Vector2 vector2_add(Vector2 a, Vector2 b) {
  return VEC2(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector2 vector2_sub(Vector2 a, Vector2 b) {
  return VEC2(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector2 vector2_div(Vector2 a, Vector2 b) {
  return (Vector2){
    .x = a.x / b.x,
    .y = a.y / b.y,
    .z = a.z / b.z
  };
}

Vector2 vector2_mul(Vector2 a, Vector2 b) {
  return VEC2(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector2 vector2_scale(Vector2 a, float s) {
  return VEC2(a.x * s, a.y * s, a.z * s);
}

///////////////////////////////////////////////////////////////////

Vector2 vector2_cross(Vector2 a, Vector2 b) {
  return VEC2(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

Vector2 vector2_reflect(Vector2 I, Vector2 N) {
  return vector2_sub(I, vector2_mul(vector2_scale(N, 2.0f), vector2_mul(I, N)));
}

Vector2 vector2_refract(Vector2 I, Vector2 N, float eta) {
  float cosi = vector2_dot(I, N);
  float k = 1.0f - eta * eta * (1.0f - cosi * cosi);
  return k < 0.0f ? VEC21(0) : vector2_sub(vector2_scale(I, eta), vector2_scale(N, eta * cosi + sqrtf(k)));
}

Vector2 vector2_triple_product(Vector2 a, Vector2 b, Vector2 c) {
  return vector2_cross(a, vector2_cross(b, c));
}

Vector2 vector2_unit(Vector2 a) {
  float mag = vector2_mag(a);

  if (mag <= 0.00000000000000000000000000000000000001f || (isinf(mag) || isnan(mag))) {
    return VEC2(0, 0, 0);
  }

  return VEC2(a.x / mag, a.y / mag, a.z / mag);
}

Vector2 vector2_inv(Vector2 a) {
  return VEC2(1.0f / a.x, 1.0f / a.y, 1.0f / a.z);
}

Vector2 vector2_rescale(Vector2 v, float scale) {
  return vector2_scale(vector2_unit(v), scale);
}

Vector2 vector2_call(Vector2 a, MifVector2CallFunction func) {
  return VEC2(func(a.x), func(a.y), func(a.z));
}

///////////////////////////////////////////////////////////////////

Vector2 vector2_lerp_v4_v4_v4(Vector2 start, Vector2 end, Vector2 scale) {
  float x = mif_lerp(start.x, end.x, scale.x);
  float y = mif_lerp(start.y, end.y, scale.y);
  float z = mif_lerp(start.z, end.z, scale.z);
  return VEC2(x, y, z);
}

Vector2 vector2_lerp_v4_v4_f(Vector2 start, Vector2 end, float scale) {
  float x = mif_lerp(start.x, end.x, scale);
  float y = mif_lerp(start.y, end.y, scale);
  float z = mif_lerp(start.z, end.z, scale);
  return VEC2(x, y, z);
}

Vector2 vector2_clamp_v4_v4_v4(Vector2 a, Vector2 min, Vector2 max) {
  float x = mif_clamp(a.x, min.x, max.x);
  float y = mif_clamp(a.y, min.y, max.y);
  float z = mif_clamp(a.z, min.z, max.z);
  return VEC2(x, y, z);
}

Vector2 vector2_clamp_v4_f_f(Vector2 a, float min, float max) {
  float x = mif_clamp(a.x, min, max);
  float y = mif_clamp(a.y, min, max);
  float z = mif_clamp(a.z, min, max);
  return VEC2(x, y, z);
}

///////////////////////////////////////////////////////////////////

float vector2_mag(Vector2 a) {
  return sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2));
}

float vector2_dot(Vector2 a, Vector2 b) {
  float dot_x = a.x * b.x;
  float dot_y = a.y * b.y;
  float dot_z = a.z * b.z;

  return dot_x + dot_y + dot_z;
}

float vector2_distance(Vector2 a, Vector2 b) {
  return sqrtf(powf(a.x - b.x, 2.0f) + powf(a.y - b.y, 2.0f) + powf(a.z - b.z, 2.0f));
}

float vector2_triple_product_scalar(Vector2 a, Vector2 b, Vector2 c) {
  return vector2_dot(a, vector2_cross(b, c));
}

///////////////////////////////////////////////////////////////////

bool vector2_is_zero(Vector2 v) {
  return mif_float_is_zero(v.x) && mif_float_is_zero(v.y) && mif_float_is_zero(v.z);
}

bool vector2_is_bad(Vector2 v) {
  return mif_float_is_bad(v.x) || mif_float_is_zero(v.y) || mif_float_is_zero(v.z);
}

///////////////////////////////////////////////////////////////////

Vector2Pair vector2_tangents_slow(Vector2 n) {
  float absX = fabsf(n.x);
  float absY = fabsf(n.y);
  float absZ = fabsf(n.z);
  Vector2 axis = VEC2(0.0f, 0.0f, 0.0f);
  if (absX > absY) {
    if (absX > absZ)
      axis.x = 1.0f; // X > Y > Z, X > Z > Y
    else
      axis.z = 1.0f; // Z > X > Y
  } else {
    if (absY > absZ)
      axis.y = 1.0f; // Y > X > Z, Y > Z > X
    else
      axis.z = 1.0f; // Z > Y > X
  }
   
  // compute tangents
  Vector2 t1 = vector2_unit(vector2_cross(n, axis));
  Vector2 t2 = vector2_unit(vector2_cross(n, t1));
  
  return (Vector2Pair) { .a = t1, .b = t2 };
}

Vector2Pair vector2_tangents_fast(Vector2 n) {
  Vector2 t1 = vector2_unit(n.x >= 0.57735f ? VEC2(n.y, -n.x, 0.0f) : VEC2(0.0f, n.z, -n.y));
  Vector2 t2 = vector2_cross(n, t1);

  return (Vector2Pair){ .a = t1, .b = t2 };
}

Vector2Pair vector2_tangents_approx(Vector2 n) {
  Vector2Pair p1 = vector2_tangents_slow(n);
  Vector2Pair p2 = vector2_tangents_fast(n);

  bool ok_1 = vector2_is_zero(p1.a) == false && vector2_is_zero(p1.b) == false &&
   vector2_is_bad(p1.a) == false && vector2_is_bad(p1.b) == false;

  bool ok_2 = vector2_is_zero(p2.a) == false && vector2_is_zero(p2.b) == false &&
   vector2_is_bad(p2.a) == false && vector2_is_bad(p2.b) == false;

  if (ok_1 == false && ok_2 == false) {
    return (Vector2Pair){0};
  }

  if (ok_1 && ok_2) {
    Vector2 a1 = p1.a;
    Vector2 b1 = p1.b;

    Vector2 a2 = p2.a;
    Vector2 b2 = p2.b;

    Vector2 a = vector2_unit(vector2_scale(vector2_add(a1, a2), 0.5f));
    if (vector2_is_bad(a) || vector2_is_zero(a)) a = a2;

    Vector2 b = vector2_unit(vector2_scale(vector2_add(b1, b2), 0.5f));
    if (vector2_is_bad(b) || vector2_is_zero(b)) b = b2;

    return (Vector2Pair){ .a = a, .b = b };
  }

  return ok_1 ? p1 : p2;
}
