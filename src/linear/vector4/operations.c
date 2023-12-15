#include <mif/linear/vector4/operations.h>
#include <mif/linear/vector4/macros.h>
#include <mif/utils.h>
#include <math.h>

Vector4 vector4_add(Vector4 a, Vector4 b) {
  return VEC4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vector4 vector4_sub(Vector4 a, Vector4 b) {
  return VEC4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vector4 vector4_div(Vector4 a, Vector4 b) {
  return (Vector4){
    .x = a.x / b.x,
    .y = a.y / b.y,
    .z = a.z / b.z
  };
}

Vector4 vector4_mul(Vector4 a, Vector4 b) {
  return VEC4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vector4 vector4_scale(Vector4 a, float s) {
  return VEC4(a.x * s, a.y * s, a.z * s, a.w * s);
}

///////////////////////////////////////////////////////////////////

Vector4 vector4_cross(Vector4 a, Vector4 b) {
  return VEC4(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

Vector4 vector4_reflect(Vector4 I, Vector4 N) {
  return vector4_sub(I, vector4_mul(vector4_scale(N, 2.0f), vector4_mul(I, N)));
}

Vector4 vector4_refract(Vector4 I, Vector4 N, float eta) {
  float cosi = vector4_dot(I, N);
  float k = 1.0f - eta * eta * (1.0f - cosi * cosi);
  return k < 0.0f ? VEC41(0) : vector4_sub(vector4_scale(I, eta), vector4_scale(N, eta * cosi + sqrtf(k)));
}

Vector4 vector4_triple_product(Vector4 a, Vector4 b, Vector4 c) {
  return vector4_cross(a, vector4_cross(b, c));
}

Vector4 vector4_unit(Vector4 a) {
  float mag = vector4_mag(a);

  if (mag <= 0.00000000000000000000000000000000000001f || (isinf(mag) || isnan(mag))) {
    return VEC4(0, 0, 0);
  }

  return VEC4(a.x / mag, a.y / mag, a.z / mag, a.w / mag);
}

Vector4 vector4_inv(Vector4 a) {
  return VEC4(1.0f / a.x, 1.0f / a.y, 1.0f / a.z, 1.0f / a.w);
}

Vector4 vector4_rescale(Vector4 v, float scale) {
  return vector4_scale(vector4_unit(v), scale);
}

Vector4 vector4_call(Vector4 a, MifVector4CallFunction func) {
  return VEC4(func(a.x), func(a.y), func(a.z), func(a.w));
}

///////////////////////////////////////////////////////////////////

Vector4 vector4_lerp_v4_v4_v4(Vector4 start, Vector4 end, Vector4 scale) {
  float x = mif_lerp(start.x, end.x, scale.x);
  float y = mif_lerp(start.y, end.y, scale.y);
  float z = mif_lerp(start.z, end.z, scale.z);
  float w = mif_lerp(start.w, end.w, scale.w);
  return VEC4(x, y, z, w);
}

Vector4 vector4_lerp_v4_v4_f(Vector4 start, Vector4 end, float scale) {
  float x = mif_lerp(start.x, end.x, scale);
  float y = mif_lerp(start.y, end.y, scale);
  float z = mif_lerp(start.z, end.z, scale);
  float w = mif_lerp(start.w, end.w, scale);
  return VEC4(x, y, z, w);
}

Vector4 vector4_clamp_v4_v4_v4(Vector4 a, Vector4 min, Vector4 max) {
  float x = mif_clamp(a.x, min.x, max.x);
  float y = mif_clamp(a.y, min.y, max.y);
  float z = mif_clamp(a.z, min.z, max.z);
  float w = mif_clamp(a.w, min.w, max.w);
  return VEC4(x, y, z, w);
}

Vector4 vector4_clamp_v4_f_f(Vector4 a, float min, float max) {
  float x = mif_clamp(a.x, min, max);
  float y = mif_clamp(a.y, min, max);
  float z = mif_clamp(a.z, min, max);
  float w = mif_clamp(a.w, min, max);
  return VEC4(x, y, z, w);
}

///////////////////////////////////////////////////////////////////

float vector4_mag(Vector4 a) {
  return sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2));
}

float vector4_dot(Vector4 a, Vector4 b) {
  float dot_x = a.x * b.x;
  float dot_y = a.y * b.y;
  float dot_z = a.z * b.z;

  return dot_x + dot_y + dot_z;
}

float vector4_distance(Vector4 a, Vector4 b) {
  return sqrtf(powf(a.x - b.x, 2.0f) + powf(a.y - b.y, 2.0f) + powf(a.z - b.z, 2.0f));
}

float vector4_triple_product_scalar(Vector4 a, Vector4 b, Vector4 c) {
  return vector4_dot(a, vector4_cross(b, c));
}

///////////////////////////////////////////////////////////////////

bool vector4_is_zero(Vector4 v) {
  return mif_float_is_zero(v.x) && mif_float_is_zero(v.y) && mif_float_is_zero(v.z);
}

bool vector4_is_bad(Vector4 v) {
  return mif_float_is_bad(v.x) || mif_float_is_zero(v.y) || mif_float_is_zero(v.z);
}

///////////////////////////////////////////////////////////////////

Vector4Pair vector4_tangents_slow(Vector4 n) {
  float absX = fabsf(n.x);
  float absY = fabsf(n.y);
  float absZ = fabsf(n.z);
  Vector4 axis = VEC4(0.0f, 0.0f, 0.0f, 0.0f);
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
  Vector4 t1 = vector4_unit(vector4_cross(n, axis));
  Vector4 t2 = vector4_unit(vector4_cross(n, t1));
  
  return (Vector4Pair) { .a = t1, .b = t2 };
}

Vector4Pair vector4_tangents_fast(Vector4 n) {
  Vector4 t1 = vector4_unit(n.x >= 0.57735f ? VEC4(n.y, -n.x, 0.0f) : VEC4(0.0f, n.z, -n.y));
  Vector4 t2 = vector4_cross(n, t1);

  return (Vector4Pair){ .a = t1, .b = t2 };
}

Vector4Pair vector4_tangents_approx(Vector4 n) {
  Vector4Pair p1 = vector4_tangents_slow(n);
  Vector4Pair p2 = vector4_tangents_fast(n);

  bool ok_1 = vector4_is_zero(p1.a) == false && vector4_is_zero(p1.b) == false &&
   vector4_is_bad(p1.a) == false && vector4_is_bad(p1.b) == false;

  bool ok_2 = vector4_is_zero(p2.a) == false && vector4_is_zero(p2.b) == false &&
   vector4_is_bad(p2.a) == false && vector4_is_bad(p2.b) == false;

  if (ok_1 == false && ok_2 == false) {
    return (Vector4Pair){0};
  }

  if (ok_1 && ok_2) {
    Vector4 a1 = p1.a;
    Vector4 b1 = p1.b;

    Vector4 a2 = p2.a;
    Vector4 b2 = p2.b;

    Vector4 a = vector4_unit(vector4_scale(vector4_add(a1, a2), 0.5f));
    if (vector4_is_bad(a) || vector4_is_zero(a)) a = a2;

    Vector4 b = vector4_unit(vector4_scale(vector4_add(b1, b2), 0.5f));
    if (vector4_is_bad(b) || vector4_is_zero(b)) b = b2;

    return (Vector4Pair){ .a = a, .b = b };
  }

  return ok_1 ? p1 : p2;
}
