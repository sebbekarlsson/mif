#include <mif/linear/vector.h>
#include <mif/linear/vector4/macros.h>

Vector4 vector4_from_vec3(Vector3 v, float w) {
  return VEC4(v.x, v.y, v.z, w); 
}
