#ifndef MYY_STRUCT_HELPERS
#define MYY_STRUCT_HELPERS 1

#define __PALIGN__ __attribute__((__packed__)) __attribute__((aligned(4)))
#define __ALIGN_AT(n) __attribute__((__packed__)) __attribute__((aligned(n)))

#endif
