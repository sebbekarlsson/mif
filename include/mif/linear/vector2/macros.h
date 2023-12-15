#ifndef MIF_LINEAR_VECTOR2_MACROS_H
#define MIF_LINEAR_VECTOR2_MACROS_H

#define VEC2(X, Y) (Vector2){ .x = (X), .y = (Y) }
#define VEC21(V)(VEC2(V, V, V))

#define VEC2_OP(a, op, b) ((Vector2){.x = (a).x op (b).x, .y = (a).y op (b).y})
#define VEC2_OP_SR(a, op, b) ((Vector2){.x = (a).x op (b), .y = (a).y op (b)})

#define VEC2_SPREAD(v) (v).x, (v).y

#define VEC2_PRINT(v, P) printf("VEC2(%"#P", %"#P")\n", VEC2_SPREAD(v))

#define VEC2_PRINT_PRECISE(v) printf("VEC2(%12.6f, %12.6f)\n", VEC2_SPREAD(v))

#endif
