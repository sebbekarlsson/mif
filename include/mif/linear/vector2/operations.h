#ifndef MIF_LINEAR_VECTOR3_OPERATIONS_H
#define MIF_LINEAR_VECTOR3_OPERATIONS_H
#include <mif/linear/vector2/vector2.h>
#include <stdbool.h>

typedef float (*MifVector2CallFunction)(float x);

Vector2 vector2_add(Vector2 a, Vector2 b);
Vector2 vector2_sub(Vector2 a, Vector2 b);
Vector2 vector2_div(Vector2 a, Vector2 b);
Vector2 vector2_mul(Vector2 a, Vector2 b);
Vector2 vector2_scale(Vector2 a, float s);

Vector2 vector2_cross(Vector2 a, Vector2 b);
Vector2 vector2_reflect(Vector2 I, Vector2 N);
Vector2 vector2_refract(Vector2 I, Vector2 N, float eta);
Vector2 vector2_triple_product(Vector2 a, Vector2 b, Vector2 c);

Vector2 vector2_unit(Vector2 a);
Vector2 vector2_inv(Vector2 a);
Vector2 vector2_rescale(Vector2 v, float scale);
Vector2 vector2_call(Vector2 a, MifVector2CallFunction func);

Vector2 vector2_lerp_v4_v4_v4(Vector2 start, Vector2 end, Vector2 scale);
Vector2 vector2_lerp_v4_v4_f(Vector2 start, Vector2 end, float scale);

#define vector2_lerp(start, end, scale) _Generic((scale), \
    float: vector2_lerp_v4_v4_f, \
    Vector2: vector2_lerp_v4_v4_v4 \
)(start, end, scale)

Vector2 vector2_clamp_v4_v4_v4(Vector2 a, Vector2 min, Vector2 max);
Vector2 vector2_clamp_v4_f_f(Vector2 a, float min, float max);

#define vector2_clamp(a, min, max) _Generic((max), \
    float: vector2_clamp_v4_f_f, \
    Vector2: vector2_clamp_v4_v4_v4 \
)(a, min, max)

float vector2_mag(Vector2 a);
float vector2_dot(Vector2 a, Vector2 b);
float vector2_distance(Vector2 a, Vector2 b);
float vector2_triple_product_scalar(Vector2 a, Vector2 b, Vector2 c);

bool vector2_is_zero(Vector2 v);
bool vector2_is_bad(Vector2 v);

Vector2Pair vector2_tangents_slow(Vector2 n);
Vector2Pair vector2_tangents_fast(Vector2 n);
Vector2Pair vector2_tangents_approx(Vector2 n);

#endif
