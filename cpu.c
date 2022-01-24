#include "string.h"
#include "stdio.h"
#include "cpu.h"
#include "lib/tester.h"

void init(uint8_t * address)
{
  mem = address;
  memset(&cp, sizeof(cp), 0);
  cp.PC = 0;
  logReadMem = NULL;
  logWriteMem = NULL;
}

unsigned int step()
{
  uint8_t instr = readMem(cp.PC++);

  switch(instr)
  {
    case 0x00:
      return 4; 
    case 0x01:
      cp.C = readMem(cp.PC++);
      cp.B = readMem(cp.PC++);
      return 12;
    case 0x11:
      cp.E = readMem(cp.PC++);
      cp.D = readMem(cp.PC++);
      return 12;
    case 0x21:
      cp.L = readMem(cp.PC++);
      cp.H = readMem(cp.PC++);
      return 12;
    case 0x31:
      cp.SP = readMem(cp.PC) | (readMem(cp.PC+1) << 8);
      cp.PC = cp.PC + 2;
      return 12;
    default: 
      printf("unknown instruction %x at addr %x\n", instr, cp.SP);
      break;
  }
}

void writeMem(uint16_t addr, uint8_t data)
{
  if(logWriteMem != NULL)
    (*logWriteMem)(addr, data);
  mem[addr] = data;   
}

uint8_t readMem(uint16_t addr)
{
  if(logReadMem != NULL)
    (*logReadMem)(addr);
  return mem[addr];
}

void registerLogReadMem(uint8_t (*func) (uint16_t) )
{
  logReadMem =  func;
}
void registerLogWriteMem( void (*func) (uint16_t, uint8_t) )
{
  logWriteMem = func;
}
