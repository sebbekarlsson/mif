#ifndef MIF_LINEAR_VECTOR4_OPERATIONS_H
#define MIF_LINEAR_VECTOR4_OPERATIONS_H
#include <mif/linear/vector4/vector4.h>
#include <cglm/struct/mat4.h>
#include <stdbool.h>

typedef float (*MifVector4CallFunction)(float x);

Vector4 vector4_add(Vector4 a, Vector4 b);
Vector4 vector4_sub(Vector4 a, Vector4 b);
Vector4 vector4_div(Vector4 a, Vector4 b);
Vector4 vector4_mul(Vector4 a, Vector4 b);
Vector4 vector4_scale(Vector4 a, float s);

Vector4 vector4_unit(Vector4 a);
Vector4 vector4_inv(Vector4 a);
Vector4 vector4_rescale(Vector4 v, float scale);
Vector4 vector4_call(Vector4 a, MifVector4CallFunction func);
Vector4 vector4_saturate(Vector4 a);
Vector4 vector4_set(Vector4 v, int i, float value);

Vector4 vector4_mul_mat4(Vector4 v, mat4s m);
Vector4 vector4_mul_mat4_raw(Vector4 v, mat4 m);

Vector4 vector4_lerp_v4_v4_v4(Vector4 start, Vector4 end, Vector4 scale);
Vector4 vector4_lerp_v4_v4_f(Vector4 start, Vector4 end, float scale);

#define vector4_lerp(start, end, scale) _Generic((scale), \
    double: vector4_lerp_v4_v4_f, \
    float: vector4_lerp_v4_v4_f, \
    Vector4: vector4_lerp_v4_v4_v4 \
)(start, end, scale)

Vector4 vector4_clamp_v4_v4_v4(Vector4 a, Vector4 min, Vector4 max);
Vector4 vector4_clamp_v4_f_f(Vector4 a, float min, float max);

#define vector4_clamp(a, min, max) _Generic((max), \
    double: vector4_clamp_v4_f_f, \
    float: vector4_clamp_v4_f_f, \
    Vector4: vector4_clamp_v4_v4_v4 \
)(a, min, max)

float vector4_mag(Vector4 a);
float vector4_dot(Vector4 a, Vector4 b);
float vector4_distance(Vector4 a, Vector4 b);
float vector4_get(Vector4 v, int i);

bool vector4_is_zero(Vector4 v);
bool vector4_is_bad(Vector4 v);
#endif
