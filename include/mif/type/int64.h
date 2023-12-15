#ifndef MIF_TYPE_INT64_H
#define MIF_TYPE_INT64_H
#include <mif/type/buffer.h>
#include <stdint.h>
#include <stdbool.h>
MIF_DEFINE_BUFFER(int64_t);


bool mif_int64_t_buffer_includes(int64_tBuffer buffer, int64_t value);
#endif
