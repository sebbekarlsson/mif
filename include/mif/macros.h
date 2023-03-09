#ifndef MIF_MACROS_H
#define MIF_MACROS_H

#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif

#ifndef MAX
#define MAX(a, b) (a > b ? a : b)
#endif

#define MIF_WARNING(...)                                                      \
  {                                                                            \
    printf("(MIF)(Warning)(%s): \n", __func__);   \
    fprintf(__VA_ARGS__);                                                      \
  }

#endif
