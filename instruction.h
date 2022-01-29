#include "stdint.h"
#define NOP 0

struct instruction
{
  char * diss;
  uint8_t len;
  uint8_t cycles;
};

struct instruction instructions[] =
{ {"NOP",1,4}
};
