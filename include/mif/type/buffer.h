#ifndef MIF_TYPE_BUFFER_H
#define MIF_TYPE_BUFFER_H
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MIF_BUFFER_DEFAULT_CAPACITY 64

typedef struct {
  int64_t capacity;
} MifBufferConfig;

#define MIF_GENERATE_BUFFER_STRUCT_FIELD(FIELD_TYPE, FIELD) FIELD_TYPE FIELD;

#define MIF_DEFINE_BUFFER__HEAD(T, CUSTOM_FIELD)                               \
  typedef struct MIF_##T##_BUFFER_STRUCT {                                     \
    T *items;                                                                  \
    volatile int64_t length;                                                   \
    volatile int64_t n_allocated;                                              \
    MifBufferConfig config;                                                    \
    volatile bool initialized;                                                 \
    CUSTOM_FIELD                                                               \
  } T##Buffer;                                                                 \
  int mif_##T##_buffer_init(T##Buffer *buffer, MifBufferConfig cfg);           \
  T##Buffer mif_##T##_buffer_init_inline(MifBufferConfig cfg);                 \
  int mif_##T##_buffer_push(T##Buffer *buffer, T item);                         \
  int mif_##T##_buffer_reset(T##Buffer *buffer);                               \
  int mif_##T##_buffer_destroy(T##Buffer *buffer);                             \
  int mif_##T##_buffer_reverse(T##Buffer *buffer);                             \
  int mif_##T##_buffer_fill(T##Buffer *buffer, T item, int64_t count);         \
  int mif_##T##_buffer_copy(T##Buffer src, T##Buffer *dest);                   \
  int mif_##T##_buffer_concat(T##Buffer *src, T##Buffer other);                \
  int mif_##T##_buffer_concat_raw(T##Buffer *src, T *items, int64_t count);    \
  int mif_##T##_buffer_popi(T##Buffer *buffer, int64_t index, T *out);         \
  int mif_##T##_buffer_remove(T##Buffer *buffer, int64_t index);               \
  int mif_##T##_buffer_splice_remove(T##Buffer *buffer, int64_t start,         \
                                     int64_t end);                             \
  bool mif_##T##_buffer_is_empty(T##Buffer buffer);                            \
  bool mif_##T##_buffer_has_data(T##Buffer buffer);                            \
  int mif_##T##_buffer_back(T##Buffer buffer, T *out);                         \
  int mif_##T##_buffer_pop(T##Buffer *buffer);

#define MIF_DEFINE_BUFFER(T) MIF_DEFINE_BUFFER__HEAD(T, )

#define MIF_IMPLEMENT_BUFFER(T)                                                \
  int mif_##T##_buffer_init(T##Buffer *buffer, MifBufferConfig cfg) {          \
    if (!buffer)                                                               \
      return 0;                                                                \
    if (buffer->initialized)                                                   \
      return 1;                                                                \
    cfg.capacity =                                                             \
        cfg.capacity > 0 ? cfg.capacity : MIF_BUFFER_DEFAULT_CAPACITY;         \
    buffer->initialized = true;                                                \
    buffer->items = 0;                                                         \
    buffer->n_allocated = 0;                                                   \
    buffer->config = cfg;                                                      \
    buffer->length = 0;                                                        \
    return 1;                                                                  \
  }                                                                            \
  T##Buffer mif_##T##_buffer_init_inline(MifBufferConfig cfg) {                \
    T##Buffer buffer = {0};                                                    \
    mif_##T##_buffer_init(&buffer, cfg);                                       \
    return buffer;                                                             \
  }                                                                            \
  static int mif_##T##_buffer_maybe_grow(T##Buffer *buffer, int64_t needs) {   \
    MIF_ASSERT_RETURN(buffer->initialized == true, 0);                         \
    MIF_ASSERT_RETURN(buffer->config.capacity > 0, 0);                         \
    MIF_ASSERT_RETURN(needs > 0, 0);                                           \
    if (buffer->n_allocated > buffer->length &&                                \
        buffer->n_allocated >= needs && buffer->items != 0)                    \
      return 1;                                                                \
                                                                               \
    int64_t added_length = MAX(needs, buffer->config.capacity);                \
    MIF_ASSERT_RETURN(added_length > 0, 0);                                    \
    MIF_ASSERT_RETURN(buffer->n_allocated >= 0, 0);                            \
    buffer->items = (T *)realloc(                                              \
        buffer->items, (buffer->n_allocated + added_length + 1) * sizeof(T));  \
    MIF_ASSERT_RETURN(buffer->items != 0, 0);                                  \
    buffer->n_allocated += added_length;                                       \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_concat(T##Buffer *src, T##Buffer other) {               \
    if (!src)                                                                  \
      return 0;                                                                \
    if (!src->initialized)                                                     \
      MIF_WARNING_RETURN_NOT_INITIALIZED(0);                                   \
    if (other.length <= 0 || other.items == 0)                                 \
      MIF_WARNING_RETURN(0, stderr, "other is empty.\n");                      \
    if (!other.initialized)                                                    \
      MIF_WARNING_RETURN(0, stderr, "other not initialized.\n");               \
                                                                               \
    int64_t start_index = src->length;                                         \
                                                                               \
    MIF_ASSERT_RETURN(mif_##T##_buffer_maybe_grow(src, src->length + other.length) == 1, 0); \
    src->length += other.length;                                               \
                                                                               \
    if (src->items == 0)                                                       \
      MIF_WARNING_RETURN(0, stderr, "Failed to allocate memory.\n");           \
                                                                               \
    memcpy(&src->items[start_index], &other.items[0],                          \
           other.length * sizeof(T));                                          \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_concat_raw(T##Buffer *src, T *items, int64_t count) {   \
    if (!src) {                                                                \
      return 0;                                                                \
    }                                                                          \
    if (!src->initialized) {                                                   \
      MIF_WARNING_RETURN_NOT_INITIALIZED(0);                                   \
    }                                                                          \
    MIF_ASSERT_RETURN(items != 0, 0);                                          \
    MIF_ASSERT_RETURN(count > 0, 0);                                           \
    int64_t start_index = src->length;                                         \
                                                                               \
    MIF_ASSERT_RETURN(mif_##T##_buffer_maybe_grow(src, src->length + count) == 1, 0);        \
    src->length += count;                                                      \
                                                                               \
    if (src->items == 0)                                                       \
      MIF_WARNING_RETURN(0, stderr, "Failed to allocate memory.\n");           \
                                                                               \
    memcpy(&src->items[start_index], &items[0], count * sizeof(T));            \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_push(T##Buffer *buffer, T item) {                       \
    if (!buffer)                                                               \
      return 0;                                                                \
    if (!buffer->initialized)                                                  \
      MIF_WARNING_RETURN(0, stderr, "Buffer not initialized\n");               \
    MIF_ASSERT_RETURN(mif_##T##_buffer_maybe_grow(buffer, 1) == 1, 0);         \
    if (!buffer->items)                                                        \
      MIF_WARNING_RETURN(0, stderr, "Could not realloc buffer.\n");            \
    buffer->items[buffer->length++] = item;                                    \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_copy(T##Buffer src, T##Buffer *dest) {                  \
    if (!dest)                                                                 \
      return 0;                                                                \
                                                                               \
    if (src.length <= 0 || src.items == 0)                                     \
      return 0;                                                                \
    if (!dest->initialized)                                                    \
      MIF_WARNING_RETURN(0, stderr, "destination not initialized\n");          \
                                                                               \
    if (!src.initialized)                                                      \
      MIF_WARNING_RETURN(0, stderr, "source not initialized\n");               \
                                                                               \
    if (dest->length > 0 || dest->items != 0)                                  \
      MIF_WARNING_RETURN(0, stderr, "Destination is not empty!\n");            \
                                                                               \
    return mif_##T##_buffer_concat(dest, src);                                 \
  }                                                                            \
  int mif_##T##_buffer_reset(T##Buffer *buffer) {                              \
    if (!buffer)                                                               \
      return 0;                                                                \
    if (!buffer->initialized)                                                  \
      return 0;                                                                \
    buffer->length = 0;                                                        \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_destroy(T##Buffer *buffer) {                            \
    if (!buffer)                                                               \
      return 0;                                                                \
    if (!buffer->initialized)                                                  \
      return 0;                                                                \
    if (buffer->items != 0) {                                                  \
      MIF_ASSERT_RETURN(buffer->n_allocated > 0, 0);                           \
      MIF_FREE(buffer->items);                                                 \
    }                                                                          \
    buffer->items = 0;                                                         \
    buffer->n_allocated = 0;                                                   \
    buffer->config.capacity = 0;                                               \
    buffer->initialized = false;                                               \
    buffer->length = 0;                                                        \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_fill(T##Buffer *buffer, T item, int64_t count) {        \
    if (!buffer)                                                               \
      return 0;                                                                \
    if (count <= 0)                                                            \
      return 0;                                                                \
    if (!buffer->initialized)                                                  \
      MIF_WARNING_RETURN(0, stderr, "Buffer not initialized\n");               \
    if (buffer->length > 0) {                                                  \
      mif_##T##_buffer_reset(buffer);                                          \
    }                                                                          \
    MIF_ASSERT_RETURN(mif_##T##_buffer_maybe_grow(buffer, count) == 1, 0);     \
    if (buffer->items == 0)                                                    \
      MIF_WARNING_RETURN(0, stderr, "Failed to allocate memory.\n");           \
    MIF_ASSERT_RETURN(buffer->n_allocated >= count, 0);                        \
    for (int64_t i = 0; i < count; i++) {                                      \
      mif_##T##_buffer_push(buffer, item);                                     \
    }                                                                          \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_popi(T##Buffer *buffer, int64_t index, T *out) {        \
    if (!buffer)                                                               \
      return 0;                                                                \
    if (!buffer->initialized)                                                  \
      MIF_WARNING_RETURN(0, stderr, "Buffer not initialized\n");               \
                                                                               \
    if (mif_##T##_buffer_is_empty(*buffer) || index < 0 ||                     \
        index >= buffer->length)                                               \
      return 0;                                                                \
                                                                               \
    if (out != 0) { *out = buffer->items[index]; }                             \
                                                                               \
    if (buffer->length - 1 <= 0) {                                             \
      mif_##T##_buffer_reset(buffer);                                          \
      return 1;                                                                \
    }                                                                          \
                                                                               \
    for (int64_t i = index; i < buffer->length - 1; i++) {                     \
      buffer->items[i] = buffer->items[i + 1];                                 \
    }                                                                          \
                                                                               \
    buffer->length -= 1;                                                       \
    buffer->length = MAX(0, buffer->length);                                   \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_remove(T##Buffer *buffer, int64_t index) {              \
    if (!buffer)                                                               \
      return 0;                                                                \
    if (!buffer->initialized)                                                  \
      MIF_WARNING_RETURN(0, stderr, "Buffer not initialized\n");               \
                                                                               \
    if (mif_##T##_buffer_is_empty(*buffer) || index < 0 ||                     \
        index >= buffer->length)                                               \
      return 0;                                                                \
                                                                               \
    if (buffer->length - 1 <= 0) {                                             \
      mif_##T##_buffer_reset(buffer);                                          \
      return 0;                                                                \
    }                                                                          \
                                                                               \
    for (int64_t i = index; i < buffer->length - 1; i++) {                     \
      buffer->items[i] = buffer->items[i + 1];                                 \
    }                                                                          \
                                                                               \
    buffer->length -= 1;                                                       \
    buffer->length = MAX(0, buffer->length);                                   \
                                                                               \
    return 1;                                                                  \
  }                                                                            \
  bool mif_##T##_buffer_is_empty(T##Buffer buffer) {                           \
    return (buffer.items == 0 || buffer.length <= 0);                          \
  }                                                                            \
  bool mif_##T##_buffer_has_data(T##Buffer buffer) {                           \
    return mif_##T##_buffer_is_empty(buffer) == false;                         \
  }                                                                            \
  int mif_##T##_buffer_splice_remove(T##Buffer *buffer, int64_t start,         \
                                     int64_t end) {                            \
    if (buffer->length <= 0 || buffer->items == 0)                             \
      return 0;                                                                \
                                                                               \
    T##Buffer next_buffer = {0};                                               \
    mif_##T##_buffer_init(&next_buffer, buffer->config);                       \
                                                                               \
    for (int64_t i = start; i < MIN(start + end, buffer->length - 1); i++) {   \
      T v = buffer->items[i % buffer->length];                                 \
      mif_##T##_buffer_push(&next_buffer, v);                                  \
    }                                                                          \
                                                                               \
    mif_##T##_buffer_reset(buffer);                                            \
    *buffer = next_buffer;                                                     \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_back(T##Buffer buffer, T *out) {                        \
    if (buffer.length <= 0 || buffer.items == 0)                               \
      return 0;                                                                \
    *out = buffer.items[buffer.length - 1];                                    \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_pop(T##Buffer *buffer) {                                \
    if (buffer->length <= 0 || buffer->items == 0)                             \
      return 0;                                                                \
                                                                               \
    if (buffer->length - 1 <= 0) {                                             \
      mif_##T##_buffer_reset(buffer);                                          \
      return 1;                                                                \
    }                                                                          \
    buffer->length -= 1;                                                       \
    MIF_ASSERT_RETURN(buffer->length >= 0, 0);                                 \
    return 1;                                                                  \
  }                                                                            \
  int mif_##T##_buffer_reverse(T##Buffer *buff) {                              \
    MIF_ASSERT_RETURN(buff != 0, 0);                                           \
    MIF_ASSERT_RETURN(buff->length > 0, 0);                                    \
    MIF_ASSERT_RETURN(buff->items != 0, 0);                                    \
    int64_t start = 0;                                                         \
    int64_t end = buff->length - 1;                                            \
    while (start < end) {                                                      \
      T temp = buff->items[start];                                             \
      buff->items[start] = buff->items[end];                                   \
      buff->items[end] = temp;                                                 \
      start++;                                                                 \
      end--;                                                                   \
    }                                                                          \
    return 1;                                                                  \
  }

#endif
