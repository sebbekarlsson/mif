#ifndef MIF_LINEAR_VECTOR3_OPERATIONS_H
#define MIF_LINEAR_VECTOR3_OPERATIONS_H
#include <mif/linear/vector3/vector3.h>
#include <cglm/struct/mat4.h>
#include <cglm/struct/mat3.h>
#include <stdbool.h>

typedef float (*MifVector3CallFunction)(float x);

Vector3 vector3_add(Vector3 a, Vector3 b);
Vector3 vector3_sub(Vector3 a, Vector3 b);
Vector3 vector3_div(Vector3 a, Vector3 b);
Vector3 vector3_mul(Vector3 a, Vector3 b);
Vector3 vector3_scale(Vector3 a, float s);

Vector3 vector3_cross(Vector3 a, Vector3 b);
Vector3 vector3_reflect(Vector3 I, Vector3 N);
Vector3 vector3_refract(Vector3 I, Vector3 N, float eta);
Vector3 vector3_triple_product(Vector3 a, Vector3 b, Vector3 c);

Vector3 vector3_unit(Vector3 a);
Vector3 vector3_inv(Vector3 a);
Vector3 vector3_rescale(Vector3 v, float scale);
Vector3 vector3_call(Vector3 a, MifVector3CallFunction func);

Vector3 vector3_mul_mat3(Vector3 v, mat3s m);
Vector3 vector3_mul_mat4(Vector3 v, float w, mat4s m);
Vector3 vector3_mul_mat4_raw(Vector3 v, float w, mat4 m);

Vector3 vector3_lerp_v3_v3_v3(Vector3 start, Vector3 end, Vector3 scale);
Vector3 vector3_lerp_v3_v3_f(Vector3 start, Vector3 end, float scale);

#define vector3_lerp(start, end, scale) _Generic((scale), \
    float: vector3_lerp_v3_v3_f, \
    Vector3: vector3_lerp_v3_v3_v3 \
)(start, end, scale)

Vector3 vector3_clamp_v3_v3_v3(Vector3 a, Vector3 min, Vector3 max);
Vector3 vector3_clamp_v3_f_f(Vector3 a, float min, float max);

#define vector3_clamp(a, min, max) _Generic((max), \
    float: vector3_clamp_v3_f_f, \
    Vector3: vector3_clamp_v3_v3_v3 \
)(a, min, max)

float vector3_mag(Vector3 a);
float vector3_dot(Vector3 a, Vector3 b);
float vector3_distance(Vector3 a, Vector3 b);
float vector3_triple_product_scalar(Vector3 a, Vector3 b, Vector3 c);

bool vector3_is_zero(Vector3 v);
bool vector3_is_bad(Vector3 v);

Vector3Pair vector3_tangents_slow(Vector3 n);
Vector3Pair vector3_tangents_fast(Vector3 n);
Vector3Pair vector3_tangents_approx(Vector3 n);

#endif
