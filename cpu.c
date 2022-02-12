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
    case RLCA:
      PRINT_INS(RLCA)
      rlcOp8(&cp.A);
      RETURN_FROM_INS(RLCA)
    case LD_A16_SP:
      PRINT_INS(LD_A16_SP)
      {
        uint16_t addr;
	uint16_t SP = cp.SP;
	ldOp16FromMemAtPC(&addr);
	ldOp8ToMem(SP & 0xFF, addr);
	SP = SP >> 8;
	ldOp8ToMem(SP, addr+1);
      }
      RETURN_FROM_INS(LD_A16_SP)
    case ADD_HL_BC:
      PRINT_INS(ADD_HL_BC)
      add16(&cp.HL, &cp.BC);
      RETURN_FROM_INS(ADD_HL_BC);
    case LD_A_star_BC:
      PRINT_INS(LD_A_star_BC)
      ldOp8FromMem(cp.BC, &cp.A);
      RETURN_FROM_INS(LD_A_star_BC);
    case DEC_BC:
      PRINT_INS(DEC_BC)
      cp.BC--;
      RETURN_FROM_INS(DEC_BC)
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
    case RRCA:
      PRINT_INS(RRCA)
      rrcOp8(&cp.A);
      RETURN_FROM_INS(RRCA)
    case STOP:
      PRINT_INS(STOP)
      //RETURN_FROM_INS(STOP)
      cp.halted = 1;
      break;
    case LD_DE_IMM16:
      PRINT_INS(LD_DE_IMM16)
      ldOp16FromMem(cp.PC, &cp.DE);
      RETURN_FROM_INS(LD_DE_IMM16)
    case LD_star_DE_A:
      PRINT_INS(LD_star_DE_A)
      ldOp8ToMem(cp.A,cp.DE);
      RETURN_FROM_INS(LD_star_DE_A)
    case INC_DE:
      PRINT_INS(INC_DE)
      cp.DE++;
      RETURN_FROM_INS(INC_DE)
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
    case RLA:
      PRINT_INS(RLA)
      rlOp8(&cp.A);
      RETURN_FROM_INS(RLA)
    case JR_IMM8:
      PRINT_INS(JR_IMM8)
      {
        int8_t data;
        ldOp8FromMemAtPC(&data);
	cp.PC += data;
      }
      RETURN_FROM_INS(JR_IMM8)
    case ADD_HL_DE:
      PRINT_INS(ADD_HL_DE)
      add16(&cp.HL, &cp.DE);
      RETURN_FROM_INS(ADD_HL_DE)
    case LD_A_star_DE:
      PRINT_INS(LD_A_star_DE)
      ldOp8FromMem(cp.DE, &cp.A);
      RETURN_FROM_INS(LD_A_star_DE)
    case DEC_DE:
      PRINT_INS(DEC_DE);
      cp.DE--;
      RETURN_FROM_INS(DEC_DE);
    case INC_E:
      PRINT_INS(INC_E)
      inc8(&cp.E);
      RETURN_FROM_INS(INC_E)
    case DEC_E:
      PRINT_INS(DEC_E)
      dec8(&cp.E);
      RETURN_FROM_INS(DEC_E)
    case LD_E_IMM8:
      PRINT_INS(LD_E_IMM8)
      ldOp8FromMemAtPC(&cp.E);
      RETURN_FROM_INS(LD_E_IMM8)
    case RRA:
      PRINT_INS(RRA)
      rrOp8(&cp.A);
      RETURN_FROM_INS(RRA)
    case JR_NZ_imm8:
      PRINT_INS(JR_NZ_imm8)
      if(cp.zf == 0)
      {
        int8_t data;
	ldOp8FromMemAtPC(&data);
        cp.PC += data;
	//TODO: cycles += 4;
      }
      RETURN_FROM_INS(JR_NZ_imm8)
    case LD_HL_IMM16:
      PRINT_INS(LD_HL_IMM16)
      ldOp16FromMem(cp.PC, &cp.HL);
      RETURN_FROM_INS(LD_HL_IMM16)
    case LD_star_HL_plus_A:
      PRINT_INS(LD_star_HL_plus_A)
      ldOp8ToMem(cp.A,cp.HL++);
      RETURN_FROM_INS(LD_star_HL_plus_A)
    case INC_HL:
      PRINT_INS(INC_HL)
      cp.HL++;
      RETURN_FROM_INS(INC_HL)
    case INC_H:
      PRINT_INS(INC_H)
      inc8(&cp.H);
      RETURN_FROM_INS(INC_H)
    case DEC_H:
      PRINT_INS(DEC_H)
      dec8(&cp.H);
      RETURN_FROM_INS(DEC_H)
    case LD_H_IMM8:
      PRINT_INS(LD_H_IMM8)
      ldOp8FromMemAtPC(&cp.H);
      RETURN_FROM_INS(LD_H_IMM8)
    case DAA:
      PRINT_INS(DAA)
      //no idea how du adjust acc reg
      RETURN_FROM_INS(DAA)
    case JR_Z_IMM8:
      PRINT_INS(JR_Z_IMM8)
      if(cp.zf == 1)
      {
         int8_t data;
	 ldOp8FromMemAtPC(&data);
	 cp.PC += data;
      }
      RETURN_FROM_INS(JR_Z_IMM8)
    case ADD_HL_HL:
      PRINT_INS(ADD_HL_HL)
      add16(&cp.HL,&cp.HL);
      RETURN_FROM_INS(ADD_HL_HL)
    case 0x2A:
      cp.A = readMem(cp.HL++);
      return 8;
    case DEC_HL:
      PRINT_INS(DEC_HL)
      cp.HL--;
      RETURN_FROM_INS(DEC_HL)
    case INC_L:
      PRINT_INS(INC_L)
      inc8(&cp.L);
      RETURN_FROM_INS(INC_L)
    case DEC_L:
      PRINT_INS(DEC_L)
      dec8(&cp.L);
      RETURN_FROM_INS(DEC_L)
    case LD_L_IMM8:
      PRINT_INS(LD_L_IMM8)
      ldOp8FromMemAtPC(&cp.L);
      RETURN_FROM_INS(LD_L_IMM8)
    case CPL:
      PRINT_INS(CPL)
      cp.A = ~cp.A;
      cp.h = cp.n = 1;
      RETURN_FROM_INS(CPL)
    case JR_NC_IMM8:
      PRINT_INS(JR_NC_IMM8)
      if(cp.cf == 0)
      {
        int8_t data;
	ldOp8FromMemAtPC(&data);
	cp.PC += data;
      }
      RETURN_FROM_INS(JR_NC_IMM8)
    case LD_SP_IMM16:
      PRINT_INS(LD_SP_IMM16)
      ldOp16FromMem(cp.PC, &cp.SP);
      RETURN_FROM_INS(LD_SP_IMM16)
    case LD_star_HL_minus_A:
      PRINT_INS(LD_star_HL_minus_A)
      ldOp8ToMem(cp.A,cp.HL--);
      RETURN_FROM_INS(LD_star_HL_minus_A)
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
    case LD_star_HL_IMM8:
      PRINT_INS(LD_star_HL_IMM8)
      {
	uint8_t data;
        ldOp8FromMemAtPC(&data);
	ldOp8ToMem(data, cp.HL);
      }
      RETURN_FROM_INS(LD_star_HL_IMM8)
    case SCF:
      PRINT_INS(SCF)
      cp.n = cp.h = 0;
      cp.cf = 1;
      RETURN_FROM_INS(SCF)
    case JR_C_IMM8:
      PRINT_INS(JR_C_IMM8)
      if(cp.cf)
      {
        int8_t data;
	ldOp8FromMemAtPC(&data);
	cp.PC += data;
      }
      RETURN_FROM_INS(JR_C_IMM8)
    case ADD_HL_SP:
      PRINT_INS(ADD_HL_SP)
      add16(&cp.HL, &cp.SP);
      RETURN_FROM_INS(ADD_HL_SP)
    case LD_A_star_HL_minus:
      PRINT_INS(LD_A_star_HL_minus)
      ldOp8FromMem(cp.HL--, &cp.A);
      RETURN_FROM_INS(LD_A_star_HL_minus)
   case DEC_SP:
      PRINT_INS(DEC_SP)
      cp.SP--;
      RETURN_FROM_INS(DEC_SP)
    case INC_A:
      PRINT_INS(INC_A)
      inc8(&cp.A);
      RETURN_FROM_INS(INC_A)
    case DEC_A:
      PRINT_INS(DEC_A)
      dec8(&cp.A);
      RETURN_FROM_INS(DEC_A)
    case LD_A_IMM8:
      PRINT_INS(LD_A_IMM8)
      ldOp8FromMemAtPC(&cp.A);
      RETURN_FROM_INS(LD_A_IMM8)
    case CCF:
      PRINT_INS(CCF)
      cp.n = cp.h = 0;
      cp.cf = ~cp.cf;
      RETURN_FROM_INS(CCF)
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

void ldOp16FromMemAtPC(uint16_t *dest)
{
  ldOp16FromMem(cp.PC, dest);
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

void add16(uint16_t *op1, uint16_t *op2)
{
  uint32_t overflow16 = ((*op1 + *op2) >> 16);
  uint16_t overflow11 = ((*op1 & 0x7FF) + (*op2 & 0x7FF)) >> 11;
  cp.n = cp.h = cp.cf = 0;
  if(overflow16)
    cp.cf = 1;
  if(overflow11)
    cp.h = 1;
  *op1 += *op2;
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

void rlcOp8(uint8_t *data)
{
  uint8_t temp = *data;
  cp.zf = cp.n = cp.h = cp.cf = 0;
  *data = *data << 1;
  //if there is a carry from the shift set flag and put the carry to lsb
  if(temp & 0x80)
  {
    cp.cf = 1;
    *data  = *data | 0x1;
  }

}
void rlOp8(uint8_t *data)
{
  uint8_t temp = *data;
  uint8_t old_carry = cp.cf;

  cp.zf = cp.n = cp.h = cp.cf = 0;
  *data = *data << 1;
  *data = *data | old_carry;

  if(temp & 0x80)
    cp.cf = 1;

}
void rrcOp8(uint8_t *data)
{
  uint8_t temp = *data;
  cp.zf = cp.n = cp.h = cp.cf = 0;
  *data = *data >> 1;
  //if there is a carry from the shift set flag and put the carry to msb
  if(temp & 0x01)
  {
    cp.cf = 1;
    *data  = *data | 0x80;
  }


}
void rrOp8(uint8_t *data)
{
  uint8_t temp = *data;
  uint8_t old_carry = cp.cf;

  cp.zf = cp.n = cp.h = cp.cf = 0;
  *data = *data >> 1;
  *data = *data | (old_carry << 7);

  if(temp & 0x01)
    cp.cf = 1;
}
