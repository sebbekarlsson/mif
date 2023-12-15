#ifndef MIF_LINEAR_VECTOR3_OPERATIONS_H
#define MIF_LINEAR_VECTOR3_OPERATIONS_H
#include <mif/linear/vector4/vector4.h>
#include <stdbool.h>

typedef float (*MifVector4CallFunction)(float x);

Vector4 vector4_add(Vector4 a, Vector4 b);
Vector4 vector4_sub(Vector4 a, Vector4 b);
Vector4 vector4_div(Vector4 a, Vector4 b);
Vector4 vector4_mul(Vector4 a, Vector4 b);
Vector4 vector4_scale(Vector4 a, float s);

Vector4 vector4_cross(Vector4 a, Vector4 b);
Vector4 vector4_reflect(Vector4 I, Vector4 N);
Vector4 vector4_refract(Vector4 I, Vector4 N, float eta);
Vector4 vector4_triple_product(Vector4 a, Vector4 b, Vector4 c);

Vector4 vector4_unit(Vector4 a);
Vector4 vector4_inv(Vector4 a);
Vector4 vector4_rescale(Vector4 v, float scale);
Vector4 vector4_call(Vector4 a, MifVector4CallFunction func);

Vector4 vector4_lerp_v4_v4_v4(Vector4 start, Vector4 end, Vector4 scale);
Vector4 vector4_lerp_v4_v4_f(Vector4 start, Vector4 end, float scale);

#define vector4_lerp(start, end, scale) _Generic((scale), \
    float: vector4_lerp_v4_v4_f, \
    Vector4: vector4_lerp_v4_v4_v4 \
)(start, end, scale)

Vector4 vector4_clamp_v4_v4_v4(Vector4 a, Vector4 min, Vector4 max);
Vector4 vector4_clamp_v4_f_f(Vector4 a, float min, float max);

#define vector4_clamp(a, min, max) _Generic((max), \
    float: vector4_clamp_v4_f_f, \
    Vector4: vector4_clamp_v4_v4_v4 \
)(a, min, max)

float vector4_mag(Vector4 a);
float vector4_dot(Vector4 a, Vector4 b);
float vector4_distance(Vector4 a, Vector4 b);
float vector4_triple_product_scalar(Vector4 a, Vector4 b, Vector4 c);

bool vector4_is_zero(Vector4 v);
bool vector4_is_bad(Vector4 v);

Vector4Pair vector4_tangents_slow(Vector4 n);
Vector4Pair vector4_tangents_fast(Vector4 n);
Vector4Pair vector4_tangents_approx(Vector4 n);

#endif
