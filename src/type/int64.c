#include <mif/type/int64.h>
#include <mif/macros.h>
#include <stdio.h>
#include <stdlib.h>

MIF_IMPLEMENT_BUFFER(int64_t);

bool mif_int64_t_buffer_includes(int64_tBuffer buffer, int64_t value) {
  if (buffer.length <= 0 || buffer.items == 0) return false;

  for (int64_t i = 0; i < buffer.length; i++) {
    if (buffer.items[i] == value) return true;
  }

  return false;
}
