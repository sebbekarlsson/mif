#ifndef MIF_MACROS_H
#define MIF_MACROS_H

#define MIF_WARNING(...)                                                      \
  {                                                                            \
    printf("(MIF)(Warning)(%s): \n", __func__);   \
    fprintf(__VA_ARGS__);                                                      \
  }

#endif
