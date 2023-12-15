#ifndef MIF_LINEAR_VECTOR3_MACROS_H
#define MIF_LINEAR_VECTOR3_MACROS_H

#define VEC3(X, Y, Z) (Vector3){ .x = (X), .y = (Y), .z = (Z) }
#define VEC31(V)(VEC3(V, V, V))

#define VEC3_OP(a, op, b) ((Vector3){.x = (a).x op (b).x, .y = (a).y op (b).y, .z = (a).z op (b).z})
#define VEC3_OP_SR(a, op, b) ((Vector3){.x = (a).x op (b), .y = (a).y op (b), .z = (a).z op (b)})

#define VEC3_SPREAD(v) (v).x, (v).y, (v).z

#define VEC3_PRINT(v, P) printf("VEC3(%"#P", %"#P", %"#P")\n", VEC3_SPREAD(v))

#define VEC3_PRINT_PRECISE(v) printf("VEC3(%12.6f, %12.6f, %12.6f)\n", VEC3_SPREAD(v))

#endif
