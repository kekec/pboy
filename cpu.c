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
      PRINT_INS(NOP)
      RETURN_FROM_INS(NOP)
    case LD_BC_IMM16:
      PRINT_INS(LD_BC_IMM16)
      ldOp16FromMem(cp.PC, &cp.BC);
      RETURN_FROM_INS(LD_BC_IMM16)
    case LD_star_BC_A:
      PRINT_INS(LD_star_BC_A)
      ldOp8ToMem(cp.A,cp.BC);
      RETURN_FROM_INS(LD_star_BC_A)
    case INC_BC:
      PRINT_INS(INC_BC)
      cp.BC++;
      RETURN_FROM_INS(INC_BC)
    case INC_B:
      PRINT_INS(INC_B)
      inc8(&cp.B);
      RETURN_FROM_INS(INC_B)
    case DEC_B:
      PRINT_INS(DEC_B)
      dec8(&cp.B);
      RETURN_FROM_INS(DEC_B)
    case LD_B_IMM8:
      PRINT_INS(LD_B_IMM8)
      ldOp8FromMemAtPC(&cp.B);
      RETURN_FROM_INS(LD_B_IMM8)
    case INC_C:
      PRINT_INS(INC_C)
      inc8(&cp.C);
      RETURN_FROM_INS(INC_C)
    case DEC_C:
      PRINT_INS(DEC_C)
      dec8(&cp.C);
      RETURN_FROM_INS(DEC_C)
    case LD_C_IMM8:
      PRINT_INS(LD_C_IMM8)
      ldOp8FromMemAtPC(&cp.C);
      RETURN_FROM_INS(LD_C_IMM8)
    case 0x11:
      //printf("Load DE with 16 bit num\n");
      ldOp16FromMem(cp.PC, &cp.DE);
      cp.PC = cp.PC + 2;
      return 12;
    case 0x12:
      //printf("Load address (DE) %x with A %x\n", cp.DE, cp.A);
      ldOp8ToMem(cp.A,cp.DE);
      return 8;
    case 0x13:
      cp.DE++;
      break;
    case INC_D:
      PRINT_INS(INC_D)
      inc8(&cp.D);
      RETURN_FROM_INS(INC_D)
    case DEC_D:
      PRINT_INS(DEC_D)
      dec8(&cp.D);
      RETURN_FROM_INS(DEC_D)
    case LD_D_IMM8:
      PRINT_INS(LD_D_IMM8)
      ldOp8FromMemAtPC(&cp.D);
      RETURN_FROM_INS(LD_D_IMM8)
    case INC_E:
      PRINT_INS(INC_E)
      inc8(&cp.E);
      RETURN_FROM_INS(INC_E)
    case DEC_E:
      PRINT_INS(DEC_E)
      dec8(&cp.E);
      RETURN_FROM_INS(DEC_E)
    case 0x21:
      //printf("Load LH with 16 bit num\n");
      ldOp16FromMem(cp.PC, &cp.HL);
      cp.PC = cp.PC + 2;
      return 12;
    case 0x22:
      //printf("LD (HL++) with A\n");
      ldOp8ToMem(cp.A,cp.HL++);
      break;
    case 0x23:
      cp.HL++;
      break;
    case INC_H:
      PRINT_INS(INC_H)
      inc8(&cp.H);
      RETURN_FROM_INS(INC_H)
    case DEC_H:
      PRINT_INS(DEC_H)
      dec8(&cp.H);
      RETURN_FROM_INS(DEC_H)
    case 0x2A:
      cp.A = readMem(cp.HL++);
      return 8;
    case INC_L:
      PRINT_INS(INC_L)
      inc8(&cp.L);
      RETURN_FROM_INS(INC_L)
    case DEC_L:
      PRINT_INS(DEC_L)
      dec8(&cp.L);
      RETURN_FROM_INS(DEC_L)
    case 0x31:
      //printf("Load SP with 16 bit num\n");
      ldOp16FromMem(cp.PC, &cp.SP);
      cp.PC = cp.PC + 2;
      return 12;
    case 0x32:
      printf("Load (HL--) with A\n");
      ldOp8ToMem(cp.A,cp.HL--);
      return 4;
    case 0x33:
      cp.SP++;
      break;
    case INC_star_HL:
      PRINT_INS(INC_star_HL)
      incMem(cp.HL);
      RETURN_FROM_INS(INC_star_HL)
    case DEC_star_HL:
      PRINT_INS(DEC_star_HL)
      decMem(cp.HL);
      RETURN_FROM_INS(DEC_star_HL)
    case INC_A:
      PRINT_INS(INC_A)
      inc8(&cp.A);
      RETURN_FROM_INS(INC_A)
    case DEC_A:
      PRINT_INS(DEC_A)
      dec8(&cp.A);
      RETURN_FROM_INS(DEC_A)
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
    return (*logReadMem)(addr);
}

void registerLogReadMem(uint8_t (*func) (uint16_t) )
{
  logReadMem =  func;
}

void registerLogWriteMem( void (*func) (uint16_t, uint8_t) )
{
  logWriteMem = func;
}

static inline void print_ins(uint8_t opcode)
{
  printf("%s \n", instructions[opcode].string);
}

static inline void move_pc(uint8_t opcode)
{
  cp.PC += instructions[opcode].len-1;
}

void ldOp8ToMem(uint8_t data, uint16_t dest)
{
  writeMem(dest, data);
}

void ldOp8FromMem(uint16_t src, uint8_t *data)
{
  *data = readMem(src);
}

void ldOp8FromMemAtPC(uint8_t *dest)
{
  ldOp8FromMem(cp.PC, dest);
}

void ldOp16FromMem(uint16_t src, uint16_t *dest)
{
  *dest = readMem(src) | (readMem(src+1) << 8);
}

void inc8(uint8_t *data)
{
  cp.zf = 0;
  cp.h = 0;
  cp.n = 0;
  if(*data == 0xFF)
    cp.zf = 1;

  if((*data & 0xF) == 0xF)
    cp.h = 1;

  (*data)++;
}

void dec8(uint8_t *data)
{
  cp.n = 1;
  if((*data & 0xF) == 0)
    cp.h = 1;
  else
    cp.h = 0;
  if(*data == 0x01)
    cp.zf = 1;
  else
    cp.zf = 0;

  (*data)--;
}

void incMem(uint16_t memAddr)
{
  uint8_t data;
  ldOp8FromMem(memAddr, &data);
  inc8(&data);
  ldOp8ToMem(data, memAddr);
} 

void decMem(uint16_t memAddr)
{
  uint8_t data;
  ldOp8FromMem(memAddr, &data);
  dec8(&data);
  ldOp8ToMem(data, memAddr);
}


