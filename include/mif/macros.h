#ifndef MIF_MACROS_H
#define MIF_MACROS_H

#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif

#ifndef MAX
#define MAX(a, b) (a > b ? a : b)
#endif

#define MIF_FREE(v) free(v)

#define MIF_REALLOC(v, s) realloc(v, s)
#define MIF_CALLOC(n, s) calloc(v, s)

#define MIF_WARNING(...)                                                       \
  {                                                                            \
    printf("(MIF)(Warning)(%s): \n", __func__);                                \
    fprintf(__VA_ARGS__);                                                      \
  }

#define MIF_WARNING_RETURN(ret, ...)                                           \
  {                                                                            \
    printf("(MIF)(Warning)(%s): \n", __func__);                                \
    fprintf(__VA_ARGS__);                                                      \
    return ret;                                                                \
  }

#define MIF_ASSERT_RETURN(expr, ret)                                           \
  {                                                                            \
    if (!(expr)) {                                                             \
      MIF_WARNING_RETURN(ret, stderr, "Assertion for `%s` failed.\n", #expr);  \
    }                                                                          \
  }

#define MIF_WARNING_RETURN_NOT_INITIALIZED(ret)                            \
  {                                                                            \
    fprintf(stderr, "(MIF)(Warning, Not initialized.)(%s): \n", __func__);     \
    return ret;                                                                \
  }

#endif
