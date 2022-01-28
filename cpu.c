#include "string.h"
#include <stdio.h>
#include "stdio.h"
#include "cpu.h"

void init(uint8_t * address)
{
  mem = address;
  cp.PC = 0;
  logReadMem = NULL;
  logWriteMem = NULL;
}

unsigned int step()
{
  uint8_t instr = readMem(cp.PC);
  switch(instr)
  {

    case 0x00:
      printf("NOP");
      cp.PC++;
      break;
    case 0x01:
      printf("Load BC with 16 bit num\n");
      printf("16bit num is: %x and %x", readMem(cp.PC+1), readMem(cp.PC+2));
      cp.C = readMem(++(cp.PC));
      cp.B = readMem(++(cp.PC));
      cp.PC++;
      printf("PC is %x\n", cp.PC);
      return 12;
    case 0x02:
      printf("PC is %x\n", cp.PC);
      printf("Load address (BC) %x with A %x\n", cp.BC, cp.A);
      writeMem(cp.BC, cp.A);
      cp.PC++;
      printf("PC is %x\n", cp.PC);
      break;
    case 0x03:
      cp.BC++;
      cp.PC++;
      break;
    case 0x11:
      printf("Load ED with 16 bit num\n");
      cp.E = readMem(++cp.PC);
      cp.D = readMem(++cp.PC);
      cp.PC++;
      return 12;
    case 0x12:
      printf("LD (ED) into A");
      writeMem(cp.DE, cp.A);
      cp.PC++;
      return 8;
    case 0x13:
      cp.DE++;
      cp.PC++;
      break;
    case 0x21:
      printf("Load LH with 16 bit num\n");
      cp.L = readMem(++cp.PC);
      cp.H = readMem(++cp.PC);
      cp.PC++;
      return 12;
    case 0x22:
      printf("LD (HL++) with A\n");
      writeMem(cp.HL, cp.A);
      cp.HL++;
      cp.PC++;
      break;
    case 0x23:
      cp.HL++;
      cp.PC++;
      break;
    case 0x2A:
      cp.A = readMem(cp.HL);
      cp.HL++;
      cp.PC++;
      return 8;
    case 0x31:
      printf("Load SP with 16 bit num\n");
      cp.SP = readMem(cp.PC+1) | (readMem(cp.PC+2) << 8);
      cp.PC = cp.PC + 3;
      return 12;
    case 0x32:
      printf("Load (HL--) with A\n");
      writeMem(cp.HL, cp.A);
      cp.HL--;
      cp.PC++;
      return 4;
    case 0x33:
      cp.SP++;
      cp.PC++;
      break;
    default: 
      printf("unknown instruction %x at addr %x\n", instr, cp.PC);
      break;
  }
}

void writeMem(uint16_t addr, uint8_t data)
{
  if( logWriteMem != NULL )
    (*logWriteMem)(addr, data);
}

uint8_t readMem(uint16_t addr)
{
  if( logReadMem != NULL )
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
