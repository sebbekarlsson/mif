#include <mif/linear/vector2/vector2.h>
#include <mif/linear/vector2/operations.h>
#include <mif/linear/vector2/macros.h>
#include <mif/utils.h>
#include <math.h>

Vector2 vector2_add(Vector2 a, Vector2 b) {
  return VEC2(a.x + b.x, a.y + b.y);
}

Vector2 vector2_sub(Vector2 a, Vector2 b) {
  return VEC2(a.x - b.x, a.y - b.y);
}

Vector2 vector2_div(Vector2 a, Vector2 b) {
  return (Vector2){
    .x = a.x / b.x,
    .y = a.y / b.y
  };
}

Vector2 vector2_mul(Vector2 a, Vector2 b) {
  return VEC2(a.x * b.x, a.y * b.y);
}

Vector2 vector2_scale(Vector2 a, float s) {
  return VEC2(a.x * s, a.y * s);
}

///////////////////////////////////////////////////////////////////

Vector2 vector2_unit(Vector2 a) {
  float mag = vector2_mag(a);

  if (mag <= 0.00000000000000000000000000000000000001f || (isinf(mag) || isnan(mag))) {
    return VEC2(0, 0);
  }

  return VEC2(a.x / mag, a.y / mag);
}

Vector2 vector2_inv(Vector2 a) {
  return VEC2(1.0f / a.x, 1.0f / a.y);
}

Vector2 vector2_rescale(Vector2 v, float scale) {
  return vector2_scale(vector2_unit(v), scale);
}

Vector2 vector2_call(Vector2 a, MifVector2CallFunction func) {
  return VEC2(func(a.x), func(a.y));
}

Vector2 vector2_saturate(Vector2 a) {
  return vector2_call(a, mif_saturate);
}

///////////////////////////////////////////////////////////////////

Vector2 vector2_lerp_v2_v2_v2(Vector2 start, Vector2 end, Vector2 scale) {
  float x = mif_lerp(start.x, end.x, scale.x);
  float y = mif_lerp(start.y, end.y, scale.y);
  return VEC2(x, y);
}

Vector2 vector2_lerp_v2_v2_f(Vector2 start, Vector2 end, float scale) {
  float x = mif_lerp(start.x, end.x, scale);
  float y = mif_lerp(start.y, end.y, scale);
  return VEC2(x, y);
}

Vector2 vector2_clamp_v2_v2_v2(Vector2 a, Vector2 min, Vector2 max) {
  float x = mif_clamp(a.x, min.x, max.x);
  float y = mif_clamp(a.y, min.y, max.y);
  return VEC2(x, y);
}

Vector2 vector2_clamp_v2_f_f(Vector2 a, float min, float max) {
  float x = mif_clamp(a.x, min, max);
  float y = mif_clamp(a.y, min, max);
  return VEC2(x, y);
}

///////////////////////////////////////////////////////////////////

float vector2_mag(Vector2 a) {
  return sqrtf(powf(a.x, 2) + powf(a.y, 2));
}

float vector2_dot(Vector2 a, Vector2 b) {
  float dot_x = a.x * b.x;
  float dot_y = a.y * b.y;

  return dot_x + dot_y;
}

float vector2_distance(Vector2 a, Vector2 b) {
  return (hypotf(b.x - a.x, b.y - a.y));
}

///////////////////////////////////////////////////////////////////

bool vector2_is_zero(Vector2 v) {
  return mif_float_is_zero(v.x) && mif_float_is_zero(v.y);
}

bool vector2_is_bad(Vector2 v) {
  return mif_float_is_bad(v.x) || mif_float_is_bad(v.y);
}
