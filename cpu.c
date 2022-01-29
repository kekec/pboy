#include "string.h"
#include <stdio.h>
#include "stdio.h"
#include "cpu.h"
#include "instruction.h"

void init(uint8_t * address)
{
  mem = address;
  cp.PC = 0;
  logReadMem = NULL;
  logWriteMem = NULL;
}

unsigned int step()
{
  uint8_t instr = readMem(cp.PC++);
  switch(instr)
  {

    case NOP:
      cp.SP += (instructions[NOP].len - 1);
      return instructions[NOP].cycles;
    case 0x01:
      //printf("Load BC with 16 bit num\n");
      ldOp16FromMem(cp.PC, &cp.BC);
      cp.PC = cp.PC + 2;
      return 12;
    case 0x02:
      //printf("Load address (BC) %x with A %x\n", cp.BC, cp.A);
      ldToMem8(cp.A,cp.BC);
      break;
    case 0x03:
      cp.BC++;
      break;
    case 0x11:
      //printf("Load DE with 16 bit num\n");
      ldOp16FromMem(cp.PC, &cp.DE);
      cp.PC = cp.PC + 2;
      return 12;
    case 0x12:
      //printf("Load address (DE) %x with A %x\n", cp.DE, cp.A);
      ldToMem8(cp.A,cp.DE);
      return 8;
    case 0x13:
      cp.DE++;
      break;
    case 0x21:
      //printf("Load LH with 16 bit num\n");
      ldOp16FromMem(cp.PC, &cp.HL);
      cp.PC = cp.PC + 2;
      return 12;
    case 0x22:
      //printf("LD (HL++) with A\n");
      ldToMem8(cp.A,cp.HL++);
      break;
    case 0x23:
      cp.HL++;
      break;
    case 0x2A:
      cp.A = readMem(cp.HL++);
      return 8;
    case 0x31:
      //printf("Load SP with 16 bit num\n");
      ldOp16FromMem(cp.PC, &cp.SP);
      cp.PC = cp.PC + 2;
      return 12;
    case 0x32:
      printf("Load (HL--) with A\n");
      ldToMem8(cp.A,cp.HL--);
      return 4;
    case 0x33:
      cp.SP++;
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

void ldToMem8(uint8_t data, uint16_t dest)
{
  writeMem(dest, data);
}

void ldFromMem8(uint16_t src, uint8_t *data)
{
  *data = readMem(src);
}

void ldOp16FromMem(uint16_t src, uint16_t *dest)
{
  *dest = readMem(src) | (readMem(src+1) << 8);
}
