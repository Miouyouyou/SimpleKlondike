/* I do not know how to inline this... It will stay as a macro until
   I figure out how the "inline" magic work */
#ifndef MYY_HELPERS_STRING_H
#define MYY_HELPERS_STRING_H 1
#define sh_pointToNextString(contiguous_strings) while (*contiguous_strings++)
#include <stdint.h>

unsigned int myy_string_size(const uint8_t * const string) {
  unsigned int c = 0;
  for(; string[c] != 0; c++);
  return c;
}

#endif
