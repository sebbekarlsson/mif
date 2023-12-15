#ifndef MIF_LINEAR_VECTOR3_MACROS_H
#define MIF_LINEAR_VECTOR3_MACROS_H

#define VEC4(X, Y, Z, W) (Vector4){ .x = (X), .y = (Y), .z = (Z), .w = (W) }
#define VEC41(V)(VEC4(V, V, V, V))

#define VEC4_OP(a, op, b) ((Vector4){.x = (a).x op (b).x, .y = (a).y op (b).y, .z = (a).z op (b).z, .w = (a).w op (b).w})
#define VEC4_OP_SR(a, op, b) ((Vector4){.x = (a).x op (b), .y = (a).y op (b), .z = (a).z op (b), .w = (a).w op (b)})

#define VEC4_SPREAD(v) (v).x, (v).y, (v).z, (v).w

#define VEC4_PRINT(v, P) printf("VEC4(%"#P", %"#P", %"#P", %"#P")\n", VEC4_SPREAD(v))

#define VEC4_PRINT_PRECISE(v) printf("VEC4(%12.6f, %12.6f, %12.6f, %12.6f)\n", VEC4_SPREAD(v))

#endif
