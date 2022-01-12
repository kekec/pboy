#include "string.h"
#include "stdio.h"
#include "cpu.h"

void init()
{
  memset(&cp, sizeof(cp), 0);
  memset(&mem, sizeof(mem), 0);
  cp.SP = 0;
}

void step()
{
  uint8_t instr = mem[cp.SP];

  switch(instr)
  {
    default: 
      printf("unknown instruction %x at addr %x\n", instr, cp.SP);
      break;
  }
  cp.SP++;
}
