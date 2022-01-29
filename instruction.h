#include "stdint.h"

#define NOP 0
#define LD_BC_IMM16 1

struct instruction
{
  char * string;
  uint8_t len;
  uint8_t cycles;
};

static struct instruction instructions[] =
{ {"NOP",1,4},
  {"LD BC, imm16",3,12}
};
