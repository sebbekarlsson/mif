#include <mif/macros.h>
#include <mif/matrix.h>
#include <mif/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mif_matrix_init(MifMatrix *dest, int64_t rows, int64_t cols) {
  if (!dest)
    return 0;
  if (dest->initialized)
    return 1;
  if (rows <= 0 || cols <= 0)
    MIF_WARNING_RETURN(0, stderr, "rows or columns <= 0.\n");
  dest->initialized = true;
  dest->rows = rows;
  dest->cols = cols;
  dest->data = (float *)calloc(rows * cols, sizeof(float));
  if (dest->data == 0) {
    dest->initialized = false;
    MIF_WARNING_RETURN(0, stderr, "Allocation failure.\n");
  }

  return 1;
}

int mif_matrix_fill(MifMatrix *dest, float x) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);

  MIF_MATRIX_FOR_EACH(*dest, { MIF_MATRIX_AT_((*dest), x, y) = x; });

  return 1;
}

int mif_matrix_add(MifMatrix *dest, MifMatrix a, MifMatrix b) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);

  MIF_ASSERT_RETURN(a.rows == b.rows, 0);
  MIF_ASSERT_RETURN(a.cols == b.cols, 0);
  MIF_ASSERT_RETURN(dest->rows == a.rows, 0);
  MIF_ASSERT_RETURN(dest->cols == a.cols, 0);

  MIF_MATRIX_FOR_EACH(*dest, {
    MIF_MATRIX_AT_((*dest), x, y) =
        MIF_MATRIX_AT_(a, x, y) + MIF_MATRIX_AT_(b, x, y);
  });

  return 1;
}

int mif_matrix_sub(MifMatrix *dest, MifMatrix a, MifMatrix b) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);

  MIF_ASSERT_RETURN(a.rows == b.rows, 0);
  MIF_ASSERT_RETURN(a.cols == b.cols, 0);
  MIF_ASSERT_RETURN(dest->rows == a.rows, 0);
  MIF_ASSERT_RETURN(dest->cols == a.cols, 0);

  MIF_MATRIX_FOR_EACH(*dest, {
    MIF_MATRIX_AT_((*dest), x, y) =
        MIF_MATRIX_AT_(a, x, y) - MIF_MATRIX_AT_(b, x, y);
  });

  return 1;
}

int mif_matrix_add_scalar(MifMatrix *dest, float v) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);

  MIF_MATRIX_FOR_EACH(*dest, { MIF_MATRIX_AT_((*dest), x, y) += v; });

  return 1;
}

int mif_matrix_sub_scalar(MifMatrix *dest, float v) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);

  MIF_MATRIX_FOR_EACH(*dest, { MIF_MATRIX_AT_((*dest), x, y) -= v; });

  return 1;
}

int mif_matrix_mul(MifMatrix *dest, MifMatrix a, MifMatrix b) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);
  MIF_ASSERT_RETURN(dest->rows > 0, 0);
  MIF_ASSERT_RETURN(dest->cols > 0, 0);

  MifMatrix tmp = {0};
  mif_matrix_init(&tmp, dest->rows, dest->cols);

  MIF_ASSERT_RETURN(a.cols == b.rows, 0);
  MIF_ASSERT_RETURN(dest->rows == a.rows, 0);
  MIF_ASSERT_RETURN(dest->cols == b.cols, 0);

  mif_matrix_mul_fast(&tmp, a, b);

  free(dest->data);
  dest->data = tmp.data;

  return 1;
}

#define MAT_AT(m, i, j) (m).data[(i) * (m).cols + (j)]

int mif_matrix_mul_fast(MifMatrix *dest, MifMatrix a, MifMatrix b) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);
  MIF_ASSERT_RETURN(dest->rows > 0, 0);
  MIF_ASSERT_RETURN(dest->cols > 0, 0);

  MIF_ASSERT_RETURN(a.cols == b.rows, 0);

  MIF_ASSERT_RETURN(dest->rows == a.rows, 0);
  MIF_ASSERT_RETURN(dest->cols == b.cols, 0);

  for (int64_t i = 0; i < dest->rows; i++) {
    for (int64_t j = 0; j < dest->cols; j++) {
      MIF_MATRIX_AT((*dest), i, j) = 0;
      for (int64_t k = 0; k < a.cols; ++k) {
        MIF_MATRIX_AT((*dest), i, j) +=
            MIF_MATRIX_AT(a, i, k) * MIF_MATRIX_AT(b, k, j);
      }
    }
  }

  return 1;
}

int mif_matrix_sigmoid(MifMatrix *dest) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);
  MIF_ASSERT_RETURN(dest->rows != 0, 0);
  MIF_ASSERT_RETURN(dest->cols != 0, 0);

  MIF_MATRIX_FOR_EACH((*dest), {
    MIF_MATRIX_AT_((*dest), x, y) = mif_sigmoid(MIF_MATRIX_AT_((*dest), x, y));
  });

  return 1;
}

int mif_matrix_identity(MifMatrix *dest) {
  if (!dest)
    return 0;

  MIF_ASSERT_RETURN(dest->initialized, 0);
  MIF_ASSERT_RETURN(dest->data != 0, 0);
  MIF_ASSERT_RETURN(dest->rows != 0, 0);
  MIF_ASSERT_RETURN(dest->cols != 0, 0);

  for (int64_t r = 0; r < dest->rows; r++) {
    MIF_MATRIX_AT_((*dest), r % dest->cols, r) = 1.0f;
  }

  return 1;
}

int mif_matrix_copy(MifMatrix *dest, MifMatrix m) {
  if (!dest)
    return 0;
  MIF_ASSERT_RETURN(dest->data == 0, 0);
  MIF_ASSERT_RETURN(m.initialized, 0);
  MIF_ASSERT_RETURN(m.data != 0, 0);
  MIF_ASSERT_RETURN(m.rows != 0, 0);
  MIF_ASSERT_RETURN(m.cols != 0, 0);
  if (!mif_matrix_init(dest, m.rows, m.cols))
    MIF_WARNING_RETURN_NOT_INITIALIZED(0);

  MIF_ASSERT_RETURN(dest->data != 0, 0);

  memcpy(&dest->data[0], &m.data[0], m.rows * m.cols * sizeof(float));
  return 1;
}

MifMatrix mif_matrix_row(MifMatrix src, int64_t i) {
  MifMatrix next = {0};
  MIF_ASSERT_RETURN(src.initialized, next);
  MIF_ASSERT_RETURN(src.data != 0, next);
  MIF_ASSERT_RETURN(src.rows != 0, next);
  MIF_ASSERT_RETURN(src.cols != 0, next);

  return (MifMatrix){
    .cols = src.cols,
    .rows = 1,
    .initialized = true,
    .data = &MIF_MATRIX_AT(src, i, 0)
  };
}

int mif_matrix_print(MifMatrix m, FILE *fp) {
  if (fp == 0)
    return 0;
  MIF_ASSERT_RETURN(m.initialized, 0);
  MIF_ASSERT_RETURN(m.data != 0, 0);

  fprintf(fp, "[\n");
  for (int64_t y = 0; y < (m).rows; y++) {
    for (int64_t x = 0; x < (m).cols; x++) {
      fprintf(fp, "  %f ", MIF_MATRIX_AT_(m, x, y));
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "]\n");

  return 1;
}

int mif_matrix_clear(MifMatrix *m) {
  if (!m)
    return 0;

  if (m->data != 0) {
    free(m->data);
  }

  m->data = 0;
  m->rows = 0;
  m->cols = 0;
  m->initialized = false;

  return 1;
}
