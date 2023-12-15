#include <mif/linear/vector3/vector3.h>
#include <mif/linear/vector3/operations.h>
#include <mif/linear/vector3/macros.h>
#include <mif/utils.h>
#include <math.h>

Vector3 vector3_add(Vector3 a, Vector3 b) {
  return VEC3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 vector3_sub(Vector3 a, Vector3 b) {
  return VEC3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 vector3_div(Vector3 a, Vector3 b) {
  return (Vector3){
    .x = a.x / b.x,
    .y = a.y / b.y,
    .z = a.z / b.z
  };
}

Vector3 vector3_mul(Vector3 a, Vector3 b) {
  return VEC3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 vector3_scale(Vector3 a, float s) {
  return VEC3(a.x * s, a.y * s, a.z * s);
}

///////////////////////////////////////////////////////////////////

Vector3 vector3_cross(Vector3 a, Vector3 b) {
  return VEC3(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

Vector3 vector3_reflect(Vector3 I, Vector3 N) {
  return vector3_sub(I, vector3_mul(vector3_scale(N, 2.0f), vector3_mul(I, N)));
}

Vector3 vector3_refract(Vector3 I, Vector3 N, float eta) {
  float cosi = vector3_dot(I, N);
  float k = 1.0f - eta * eta * (1.0f - cosi * cosi);
  return k < 0.0f ? VEC31(0) : vector3_sub(vector3_scale(I, eta), vector3_scale(N, eta * cosi + sqrtf(k)));
}

Vector3 vector3_triple_product(Vector3 a, Vector3 b, Vector3 c) {
  return vector3_cross(a, vector3_cross(b, c));
}

Vector3 vector3_unit(Vector3 a) {
  float mag = vector3_mag(a);

  if (mag <= 0.00000000000000000000000000000000000001f || (isinf(mag) || isnan(mag))) {
    return VEC3(0, 0, 0);
  }

  return VEC3(a.x / mag, a.y / mag, a.z / mag);
}

Vector3 vector3_inv(Vector3 a) {
  return VEC3(1.0f / a.x, 1.0f / a.y, 1.0f / a.z);
}

Vector3 vector3_rescale(Vector3 v, float scale) {
  return vector3_scale(vector3_unit(v), scale);
}

Vector3 vector3_call(Vector3 a, MifVector3CallFunction func) {
  return VEC3(func(a.x), func(a.y), func(a.z));
}

Vector3 vector3_mul_mat3(Vector3 v, mat3s m) {
  vec3s r = glms_mat3_mulv(m, VEC3_GLM(v));
  return VEC3_FROM_GLM(r);
}

Vector3 vector3_mul_mat4(Vector3 v, float w, mat4s m) {
  vec3s r = glms_mat4_mulv3(m, VEC3_GLM(v), w);
  return VEC3_FROM_GLM(r);
}

///////////////////////////////////////////////////////////////////

Vector3 vector3_lerp_v3_v3_v3(Vector3 start, Vector3 end, Vector3 scale) {
  float x = mif_lerp(start.x, end.x, scale.x);
  float y = mif_lerp(start.y, end.y, scale.y);
  float z = mif_lerp(start.z, end.z, scale.z);
  return VEC3(x, y, z);
}

Vector3 vector3_lerp_v3_v3_f(Vector3 start, Vector3 end, float scale) {
  float x = mif_lerp(start.x, end.x, scale);
  float y = mif_lerp(start.y, end.y, scale);
  float z = mif_lerp(start.z, end.z, scale);
  return VEC3(x, y, z);
}

Vector3 vector3_clamp_v3_v3_v3(Vector3 a, Vector3 min, Vector3 max) {
  float x = mif_clamp(a.x, min.x, max.x);
  float y = mif_clamp(a.y, min.y, max.y);
  float z = mif_clamp(a.z, min.z, max.z);
  return VEC3(x, y, z);
}

Vector3 vector3_clamp_v3_f_f(Vector3 a, float min, float max) {
  float x = mif_clamp(a.x, min, max);
  float y = mif_clamp(a.y, min, max);
  float z = mif_clamp(a.z, min, max);
  return VEC3(x, y, z);
}

///////////////////////////////////////////////////////////////////

float vector3_mag(Vector3 a) {
  return sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2));
}

float vector3_dot(Vector3 a, Vector3 b) {
  float dot_x = a.x * b.x;
  float dot_y = a.y * b.y;
  float dot_z = a.z * b.z;

  return dot_x + dot_y + dot_z;
}

float vector3_distance(Vector3 a, Vector3 b) {
  return sqrtf(powf(a.x - b.x, 2.0f) + powf(a.y - b.y, 2.0f) + powf(a.z - b.z, 2.0f));
}

float vector3_triple_product_scalar(Vector3 a, Vector3 b, Vector3 c) {
  return vector3_dot(a, vector3_cross(b, c));
}

///////////////////////////////////////////////////////////////////

bool vector3_is_zero(Vector3 v) {
  return mif_float_is_zero(v.x) && mif_float_is_zero(v.y) && mif_float_is_zero(v.z);
}

bool vector3_is_bad(Vector3 v) {
  return mif_float_is_bad(v.x) || mif_float_is_bad(v.y) || mif_float_is_bad(v.z);
}

///////////////////////////////////////////////////////////////////

Vector3Pair vector3_tangents_slow(Vector3 n) {
  float absX = fabsf(n.x);
  float absY = fabsf(n.y);
  float absZ = fabsf(n.z);
  Vector3 axis = VEC3(0.0f, 0.0f, 0.0f);
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
  Vector3 t1 = vector3_unit(vector3_cross(n, axis));
  Vector3 t2 = vector3_unit(vector3_cross(n, t1));
  
  return (Vector3Pair) { .a = t1, .b = t2 };
}

Vector3Pair vector3_tangents_fast(Vector3 n) {
  Vector3 t1 = vector3_unit(n.x >= 0.57735f ? VEC3(n.y, -n.x, 0.0f) : VEC3(0.0f, n.z, -n.y));
  Vector3 t2 = vector3_cross(n, t1);

  return (Vector3Pair){ .a = t1, .b = t2 };
}

Vector3Pair vector3_tangents_approx(Vector3 n) {
  Vector3Pair p1 = vector3_tangents_slow(n);
  Vector3Pair p2 = vector3_tangents_fast(n);

  bool ok_1 = vector3_is_zero(p1.a) == false && vector3_is_zero(p1.b) == false &&
   vector3_is_bad(p1.a) == false && vector3_is_bad(p1.b) == false;

  bool ok_2 = vector3_is_zero(p2.a) == false && vector3_is_zero(p2.b) == false &&
   vector3_is_bad(p2.a) == false && vector3_is_bad(p2.b) == false;

  if (ok_1 == false && ok_2 == false) {
    return (Vector3Pair){0};
  }

  if (ok_1 && ok_2) {
    Vector3 a1 = p1.a;
    Vector3 b1 = p1.b;

    Vector3 a2 = p2.a;
    Vector3 b2 = p2.b;

    Vector3 a = vector3_unit(vector3_scale(vector3_add(a1, a2), 0.5f));
    if (vector3_is_bad(a) || vector3_is_zero(a)) a = a2;

    Vector3 b = vector3_unit(vector3_scale(vector3_add(b1, b2), 0.5f));
    if (vector3_is_bad(b) || vector3_is_zero(b)) b = b2;

    return (Vector3Pair){ .a = a, .b = b };
  }

  return ok_1 ? p1 : p2;
}
