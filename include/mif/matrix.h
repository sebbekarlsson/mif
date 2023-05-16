#ifndef MIF_MATRIX_H
#define MIF_MATRIX_H
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  float* data;
  int64_t rows;
  int64_t cols;
  bool initialized;
} MifMatrix;

#define MIF_MATRIX_AT_(m, x, y) m.data[(y) * (m).cols + (x)]
#define MIF_MATRIX_AT(m, x, y) m.data[(x) * (m).cols + (y)]

#define MIF_MATRIX_FOR_EACH(m, body)                                           \
  {                                                                            \
    for (int64_t y = 0; y < (m).rows; y++) {                                   \
      for (int64_t x = 0; x < (m).cols; x++) {                                 \
        body                                                                   \
      }                                                                        \
    }                                                                          \
  }

#define MIF_MATRIX_FILL(m, expr) MIF_MATRIX_FOR_EACH(m, { MIF_MATRIX_AT(m, x, y) = (expr); });

int mif_matrix_init(MifMatrix *dest, int64_t rows, int64_t cols);

int mif_matrix_clear(MifMatrix* m);

int mif_matrix_fill(MifMatrix *dest, float x);

int mif_matrix_add(MifMatrix *dest, MifMatrix a, MifMatrix b);

int mif_matrix_sub(MifMatrix *dest, MifMatrix a, MifMatrix b);

int mif_matrix_add_scalar(MifMatrix *dest, float x);

int mif_matrix_sub_scalar(MifMatrix *dest, float x);

int mif_matrix_mul(MifMatrix *dest, MifMatrix a, MifMatrix b);

int mif_matrix_mul_fast(MifMatrix *dest, MifMatrix a, MifMatrix b);

int mif_matrix_sigmoid(MifMatrix* dest);

int mif_matrix_identity(MifMatrix* dest);

int mif_matrix_copy(MifMatrix *dest, MifMatrix m);

MifMatrix mif_matrix_row(MifMatrix src, int64_t i);

int mif_matrix_print(MifMatrix m, FILE *fp);


#endif
