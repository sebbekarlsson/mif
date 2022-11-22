#ifndef MIF_UTILS_H
#define MIF_UTILS_H
#include <stdbool.h>

#define MIF_SIGN(v) (v < 0.0f ? -1.0f : 1.0f)

float mif_clamp(float v, float min, float max);

float mif_lerp(float from, float to, float scale);

float mif_smoothstep(float edge0, float edge1, float value);

float mif_fract(float v);

float mif_cos_n(float v);

float mif_sin_n(float v);

float mif_inv(float v);

float mif_gold_ratio(float x, float y);

int mif_cantor(int x, int y);

void mif_decant(int c, int* x, int* y);

bool mif_isodd(int v);

int mif_collatz(int v);

#endif
