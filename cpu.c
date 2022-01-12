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
  uint8_t instr = mem[cp.PC++];

  switch(instr)
  {
    case 0x00:
      return 4; 
    case 0x01:
      cp.C = mem[cp.PC++];
      cp.B = mem[cp.PC++];
      return 12;
    case 0x11:
      cp.E = mem[cp.PC++];
      cp.D = mem[cp.PC++];
      return 12;
    case 0x21:
      cp.L = mem[cp.PC++];
      cp.H = mem[cp.PC++];
      return 12;
    case 0x31:
      cp.SP = mem[cp.PC] | (mem[cp.PC+1] << 8);
      cp.PC = cp.PC + 2;
      return 12;
    default: 
      printf("unknown instruction %x at addr %x\n", instr, cp.SP);
      break;
  }
}
