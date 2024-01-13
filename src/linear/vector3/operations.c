#include <mif/linear/vector3/vector3.h>
#include <mif/linear/vector3/operations.h>
#include <mif/linear/vector3/macros.h>
#include <mif/utils.h>
#include <mif/macros.h>
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

Vector3 vector3_rotate(Vector3 v, float radians, Vector3 axis) {
  vec3s v_ = { .x = v.x, .y = v.y, .z = v.z };
  vec3s a_ = { .x = axis.x, .y = axis.y, .z = axis.z };
  vec3s r = glms_vec3_rotate(v_, radians, a_);
  return VEC3(r.x, r.y, r.z);
}

Vector3 vector3_unit(Vector3 a) {
  float mag = vector3_mag(a);

  if (mag <= 0.00000000000000000000000000000000000001f || (isinf(mag) || isnan(mag))) {
    return VEC3(0, 0, 0);
  }

  return VEC3(a.x / mag, a.y / mag, a.z / mag);
}

Vector3 vector3_relax(Vector3 a, float relax) {
  return vector3_scale(a, 1.0f / (1.0f + fabsf(relax)));
}

Vector3 vector3_compute_normal(Vector3 v1, Vector3 v2, Vector3 v3) {
  Vector3 e1 = vector3_sub(v2, v1);
  Vector3 e2 = vector3_sub(v3, v1);

  return vector3_cross(e1, e2);
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

Vector3 vector3_saturate(Vector3 a) {
  return vector3_call(a, mif_saturate);
}

Vector3 vector3_set(Vector3 v, int i, float value) {
  switch (i) {
    case 0: v.x = value; break;
    case 1: v.y = value; break;
    case 2: v.z = value; break;
    default: return v; break;
  }
  return v;
}

Vector3 vector3_mul_mat3(Vector3 v, mat3s m) {
  vec3s r = glms_mat3_mulv(m, VEC3_GLM(v));
  return VEC3_FROM_GLM(r);
}

Vector3 vector3_mul_mat4(Vector3 v, float w, mat4s m) {
  vec3s r = glms_mat4_mulv3(m, VEC3_GLM(v), w);
  return VEC3_FROM_GLM(r);
}

Vector3 vector3_mul_mat4_raw(Vector3 v, float w, mat4 m) {
  vec4 dest = GLM_VEC4_ZERO_INIT;
  glm_mat4_mulv3(m, (vec3){v.x, v.y, v.z}, w, dest);
  Vector3 r = VEC3(dest[0], dest[1], dest[2]);
  r.w = dest[3];
  return r;
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

Vector3 vector3_clamp_mag(Vector3 a, float min, float max) {
  return vector3_scale(vector3_unit(a), mif_clamp(vector3_mag(a), min, max));
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

Vector3 vector3_random_f_v3_v3(float seed, Vector3 min, Vector3 max) {
  uint32_t useed = mif_permute_uint32(mif_float_bits_to_uint(seed));
  float x = mif_random_float_from_uint32(min.x, max.x, useed);
  useed = mif_permute_uint32(mif_float_bits_to_uint(x * 3.0f + seed));
  float y = mif_random_float_from_uint32(min.y, max.y, useed);
  useed = mif_permute_uint32(mif_float_bits_to_uint(y * 3.0f + seed));
  float z = mif_random_float_from_uint32(min.z, max.z, useed);
  return VEC3(x, y, z);
}

Vector3 vector3_random_f_f_f(float seed, float min, float max) {
  uint32_t useed = mif_permute_uint32(mif_float_bits_to_uint(seed));
  float x = mif_random_float_from_uint32(min, max, useed);
  useed = mif_permute_uint32(mif_float_bits_to_uint(x * 3.0f + seed));
  float y = mif_random_float_from_uint32(min, max, useed);
  useed = mif_permute_uint32(mif_float_bits_to_uint(y * 3.0f + seed));
  float z = mif_random_float_from_uint32(min, max, useed);
  return VEC3(x, y, z);
}

Vector3 vector3_random_v3_f_f(Vector3 seed, float min, float max) {
  Vector3U32 s = (Vector3U32){
    .x = mif_float_bits_to_uint(seed.x),
    .y = mif_float_bits_to_uint(seed.y),
    .z = mif_float_bits_to_uint(seed.z) };
  s = vector3U32_permute(s);
  float x = mif_random_float_from_uint32(min, max, s.x);
  float y = mif_random_float_from_uint32(min, max, s.y);
  float z = mif_random_float_from_uint32(min, max, s.z);
  return VEC3(x, y, z);
}

Vector3 vector3_random_v3_v3_v3(Vector3 seed, Vector3 min, Vector3 max) {
  Vector3U32 s = (Vector3U32){
    .x = mif_float_bits_to_uint(seed.x),
    .y = mif_float_bits_to_uint(seed.y),
    .z = mif_float_bits_to_uint(seed.z) };
  s = vector3U32_permute(s);
  float x = mif_random_float_from_uint32(min.x, max.x, s.x);
  float y = mif_random_float_from_uint32(min.y, max.y, s.y);
  float z = mif_random_float_from_uint32(min.z, max.z, s.z);
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

float vector3_get(Vector3 v, int i) {
  switch (i) {
    case 0: return v.x; break;
    case 1: return v.y; break;
    case 2: return v.z; break;
    default: return 0; break;
  }
  return 0;
}

float vector3_triple_product_scalar(Vector3 a, Vector3 b, Vector3 c) {
  return vector3_dot(a, vector3_cross(b, c));
}

float vector3_get_component(Vector3 a, uint8_t idx) {
  float* data = (float*)&a;
  idx = MAX(idx, 0);
  return data[idx % 3];
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

static inline uint32_t pm1(uint32_t x) {
  uint32_t ix = ~x;
  x ^= x << 17U;
  x ^= x >> 13U;
  x ^= x << 5U;
  x = x + x * (402U + ix * 77U);
  return x;
}

Vector3U32 vector3U32_permute(Vector3U32 v) {
  return (Vector3U32){ .x = pm1(v.x), .y = pm1(v.y), .z = pm1(v.z) };
}
