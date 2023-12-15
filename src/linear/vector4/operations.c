#include <mif/linear/vector4/vector4.h>
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
    .z = a.z / b.z,
    .w = a.w / b.w
  };
}

Vector4 vector4_mul(Vector4 a, Vector4 b) {
  return VEC4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vector4 vector4_scale(Vector4 a, float s) {
  return VEC4(a.x * s, a.y * s, a.z * s, a.w * s);
}

///////////////////////////////////////////////////////////////////
Vector4 vector4_unit(Vector4 a) {
  float mag = vector4_mag(a);

  if (mag <= 0.00000000000000000000000000000000000001f || (isinf(mag) || isnan(mag))) {
    return VEC4(0, 0, 0, 0);
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
  return sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2) + powf(a.w, 2));
}

float vector4_dot(Vector4 a, Vector4 b) {
  float dot_x = a.x * b.x;
  float dot_y = a.y * b.y;
  float dot_z = a.z * b.z;
  float dot_w = a.w * b.w;

  return dot_x + dot_y + dot_z + dot_w;
}
float vector4_distance(Vector4 a, Vector4 b) {
  return sqrtf(powf(a.x - b.x, 2.0f) + powf(a.y - b.y, 2.0f) + powf(a.z - b.z, 2.0f) + powf(a.w - b.w, 2.0f));
}

///////////////////////////////////////////////////////////////////

bool vector4_is_zero(Vector4 v) {
  return mif_float_is_zero(v.x) && mif_float_is_zero(v.y) && mif_float_is_zero(v.z) && mif_float_is_zero(v.w);
}

bool vector4_is_bad(Vector4 v) {
  return mif_float_is_bad(v.x) || mif_float_is_bad(v.y) || mif_float_is_bad(v.z) || mif_float_is_bad(v.w);
}
