#include "string.h"
#include "stdio.h"
#include "cpu.h"

void init(uint8_t * address)
{
  mem = address;
  memset(&cp, sizeof(cp), 0);
  cp.PC = 0;
}

unsigned int step()
{
  uint8_t instr = mem[cp.SP];

  switch(instr)
  {
    case 0x00:
      break;
    default: 
      printf("unknown instruction %x at addr %x\n", instr, cp.SP);
      break;
  }
  cp.PC++;
  return 4;
}
