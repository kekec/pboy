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
    case DAA: //thanks to: https://forums.nesdev.org/viewtopic.php?t=15944
      PRINT_INS(DAA)
      daa();
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
    case LD_A_star_HL_plus:
      PRINT_INS(LD_A_star_HL_plus)
      cp.A = readMem(cp.HL++);
      RETURN_FROM_INS(LD_A_star_HL_plus)
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
    case INC_SP:
      PRINT_INS(INC_SP)
      cp.SP++;
      RETURN_FROM_INS(INC_SP)
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
    case LD_B_B:
      PRINT_INS(LD_B_B)
      RETURN_FROM_INS(LD_B_B)
    case LD_B_C:
      PRINT_INS(LD_B_C)
      cp.B = cp.C;
      RETURN_FROM_INS(LD_B_C)
    case LD_B_D:
      PRINT_INS(LD_B_D)
      cp.B = cp.D;
      RETURN_FROM_INS(LD_B_D)
    case LD_B_E:
      PRINT_INS(LD_B_E)
      cp.B = cp.E;
      RETURN_FROM_INS(LD_B_E)
    case LD_B_H:
      PRINT_INS(LD_B_H)
      cp.B = cp.H;
      RETURN_FROM_INS(LD_B_H)
    case LD_B_L:
      PRINT_INS(LD_B_L)
      cp.B = cp.L;
      RETURN_FROM_INS(LD_B_L)
    case LD_B_star_HL:
      PRINT_INS(LD_B_star_HL)
      ldOp8FromMem(cp.HL, &cp.B);
      RETURN_FROM_INS(LD_B_star_HL)
    case LD_B_A:
      PRINT_INS(LD_B_A)
      cp.B = cp.A;
      RETURN_FROM_INS(LD_B_A)
    case LD_C_B:
      PRINT_INS(LD_C_B)
      cp.C = cp.B;
      RETURN_FROM_INS(LD_C_B)
    case LD_C_C:
      PRINT_INS(LD_C_C)
      RETURN_FROM_INS(LD_C_C)
    case LD_C_D:
      PRINT_INS(LD_C_D)
      cp.C = cp.D;
      RETURN_FROM_INS(LD_C_D)
    case LD_C_E:
      PRINT_INS(LD_C_E)
      cp.C = cp.E;
      RETURN_FROM_INS(LD_C_E)
    case LD_C_H:
      PRINT_INS(LD_C_H)
      cp.C = cp.H;
      RETURN_FROM_INS(LD_C_H)
    case LD_C_L:
      PRINT_INS(LD_C_L)
      cp.C = cp.L;
      RETURN_FROM_INS(LD_C_L)
    case LD_C_star_HL:
      PRINT_INS(LD_C_star_HL)
      ldOp8FromMem(cp.HL, &cp.C);
      RETURN_FROM_INS(LD_C_star_HL)
    case LD_C_A:
      PRINT_INS(LD_C_A)
      cp.C = cp.A;
      RETURN_FROM_INS(LD_C_A)
    case LD_D_B:
      PRINT_INS(LD_D_B)
      cp.D = cp.B;
      RETURN_FROM_INS(LD_D_B)
    case LD_D_C:
      PRINT_INS(LD_D_C)
      cp.D = cp.C;
      RETURN_FROM_INS(LD_D_C)
    case LD_D_D:
      PRINT_INS(LD_D_D)
      RETURN_FROM_INS(LD_D_D)
    case LD_D_E:
      PRINT_INS(LD_D_E)
      cp.D = cp.E;
      RETURN_FROM_INS(LD_D_E)
    case LD_D_H:
      PRINT_INS(LD_D_H)
      cp.D = cp.H;
      RETURN_FROM_INS(LD_D_H)
    case LD_D_L:
      PRINT_INS(LD_D_L)
      cp.D = cp.L;
      RETURN_FROM_INS(LD_D_L)
    case LD_D_star_HL:
      PRINT_INS(LD_D_star_HL)
      ldOp8FromMem(cp.HL, &cp.D);
      RETURN_FROM_INS(LD_D_star_HL)
    case LD_D_A:
      PRINT_INS(LD_D_A)
      cp.D = cp.A;
      RETURN_FROM_INS(LD_D_A)
    case LD_E_B:
      PRINT_INS(LD_E_B)
      cp.E = cp.B;
      RETURN_FROM_INS(LD_E_B)
    case LD_E_C:
      PRINT_INS(LD_E_C)
      cp.E = cp.C;
      RETURN_FROM_INS(LD_E_C)
    case LD_E_D:
      PRINT_INS(LD_E_D)
      cp.E = cp.D;
      RETURN_FROM_INS(LD_E_D)
    case LD_E_E:
      PRINT_INS(LD_E_E)
      RETURN_FROM_INS(LD_E_E)
    case LD_E_H:
      PRINT_INS(LD_E_H)
      cp.E = cp.H;
      RETURN_FROM_INS(LD_E_H)
    case LD_E_L:
      PRINT_INS(LD_E_L)
      cp.E = cp.L;
      RETURN_FROM_INS(LD_E_L)
    case LD_E_star_HL:
      PRINT_INS(LD_E_star_HL)
      ldOp8FromMem(cp.HL, &cp.E);
      RETURN_FROM_INS(LD_E_star_HL)
    case LD_E_A:
      PRINT_INS(LD_E_A)
      cp.E = cp.A;
      RETURN_FROM_INS(LD_E_A)
    case LD_H_B:
      PRINT_INS(LD_H_B)
      cp.H = cp.B;
      RETURN_FROM_INS(LD_H_B)
    case LD_H_C:
      PRINT_INS(LD_H_C)
      cp.H = cp.C;
      RETURN_FROM_INS(LD_H_C)
    case LD_H_D:
      PRINT_INS(LD_H_D)
      cp.H = cp.D;
      RETURN_FROM_INS(LD_H_D)
    case LD_H_E:
      PRINT_INS(LD_H_E)
      cp.H = cp.E;
      RETURN_FROM_INS(LD_H_E)
    case LD_H_H:
      PRINT_INS(LD_H_H)
      RETURN_FROM_INS(LD_H_H)
    case LD_H_L:
      PRINT_INS(LD_H_L)
      cp.H = cp.L;
      RETURN_FROM_INS(LD_H_L)
    case LD_H_star_HL:
      PRINT_INS(LD_H_star_HL)
      ldOp8FromMem(cp.HL, &cp.H);
      RETURN_FROM_INS(LD_H_star_HL)
    case LD_H_A:
      PRINT_INS(LD_H_A)
      cp.H = cp.A;
      RETURN_FROM_INS(LD_H_A)
    case LD_L_B:
      PRINT_INS(LD_L_B)
      cp.L = cp.B;
      RETURN_FROM_INS(LD_L_B)
    case LD_L_C:
      PRINT_INS(LD_L_C)
      cp.L = cp.C;
      RETURN_FROM_INS(LD_L_C)
    case LD_L_D:
      PRINT_INS(LD_L_D)
      cp.L = cp.D;
      RETURN_FROM_INS(LD_L_D)
    case LD_L_E:
      PRINT_INS(LD_L_E)
      cp.L = cp.E;
      RETURN_FROM_INS(LD_L_E)
    case LD_L_H:
      PRINT_INS(LD_L_H)
      cp.L = cp.H;
      RETURN_FROM_INS(LD_L_H)
    case LD_L_L:
      PRINT_INS(LD_L_L)
      RETURN_FROM_INS(LD_L_L)
    case LD_L_star_HL:
      PRINT_INS(LD_L_star_HL)
      ldOp8FromMem(cp.HL, &cp.L);
      RETURN_FROM_INS(LD_L_star_HL)
    case LD_L_A:
      PRINT_INS(LD_L_A)
      cp.L = cp.A;
      RETURN_FROM_INS(LD_L_A)
    case LD_star_HL_B:
      PRINT_INS(LD_star_HL_B)
      ldOp8ToMem(cp.B, cp.HL);
      RETURN_FROM_INS(LD_star_HL_B)
    case LD_star_HL_C:
      PRINT_INS(LD_star_HL_C)
      ldOp8ToMem(cp.C, cp.HL);
      RETURN_FROM_INS(LD_star_HL_C)
    case LD_star_HL_D:
      PRINT_INS(LD_star_HL_D)
      ldOp8ToMem(cp.D, cp.HL);
      RETURN_FROM_INS(LD_star_HL_D)
    case LD_star_HL_E:
      PRINT_INS(LD_star_HL_E)
      ldOp8ToMem(cp.E, cp.HL);
      RETURN_FROM_INS(LD_star_HL_E)
    case LD_star_HL_H:
      PRINT_INS(LD_star_HL_H)
      ldOp8ToMem(cp.H, cp.HL);
      RETURN_FROM_INS(LD_star_HL_H)
    case LD_star_HL_L:
      PRINT_INS(LD_star_HL_L)
      ldOp8ToMem(cp.L, cp.HL);
      RETURN_FROM_INS(LD_star_HL_L)
    case LD_star_HL_star_HL:
      PRINT_INS(LD_star_HL_star_HL)
      cp.halted = true;
      break;
//      RETURN_FROM_INS(LD_star_HL_star_HL)
    case LD_star_HL_A:
      PRINT_INS(LD_star_HL_A)
      ldOp8ToMem(cp.A, cp.HL);
      RETURN_FROM_INS(LD_star_HL_A)
    case LD_A_B:
      PRINT_INS(LD_A_B)
      cp.A = cp.B;
      RETURN_FROM_INS(LD_A_B)
    case LD_A_C:
      PRINT_INS(LD_A_C)
      cp.A = cp.C;
      RETURN_FROM_INS(LD_A_C)
    case LD_A_D:
      PRINT_INS(LD_A_D)
      cp.A = cp.D;
      RETURN_FROM_INS(LD_A_D)
    case LD_A_E:
      PRINT_INS(LD_A_E)
      cp.A = cp.E;
      RETURN_FROM_INS(LD_A_E)
    case LD_A_H:
      PRINT_INS(LD_A_H)
      cp.A = cp.H;
      RETURN_FROM_INS(LD_A_H)
    case LD_A_L:
      PRINT_INS(LD_A_L)
      cp.A = cp.L;
      RETURN_FROM_INS(LD_A_L)
    case LD_A_star_HL:
      PRINT_INS(LD_A_star_HL)
      ldOp8FromMem(cp.HL, &cp.A);
      RETURN_FROM_INS(LD_A_star_HL)
    case LD_A_A:
      PRINT_INS(LD_A_A)
      RETURN_FROM_INS(LD_A_A)
    case ADD_A_B:
      PRINT_INS(ADD_A_B)
      add8(&cp.A, &cp.B);
      RETURN_FROM_INS(ADD_A_B)
    case ADD_A_C:
      PRINT_INS(ADD_A_C)
      add8(&cp.A, &cp.C);
      RETURN_FROM_INS(ADD_A_C)
    case ADD_A_D:
      PRINT_INS(ADD_A_D)
      add8(&cp.A, &cp.D);
      RETURN_FROM_INS(ADD_A_D)
    case ADD_A_E:
      PRINT_INS(ADD_A_E)
      add8(&cp.A, &cp.E);
      RETURN_FROM_INS(ADD_A_E)
    case ADD_A_H:
      PRINT_INS(ADD_A_H)
      add8(&cp.A, &cp.H);
      RETURN_FROM_INS(ADD_A_H)
    case ADD_A_L:
      PRINT_INS(ADD_A_L)
      add8(&cp.A, &cp.L);
      RETURN_FROM_INS(ADD_A_L)
    case ADD_A_star_HL:
      PRINT_INS(ADD_A_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        add8(&cp.A, &data);
      }
      RETURN_FROM_INS(ADD_A_star_HL)
    case ADD_A_A:
      PRINT_INS(ADD_A_A)
      add8(&cp.A, &cp.A);
      RETURN_FROM_INS(ADD_A_A)
    case ADC_A_B:
      PRINT_INS(ADC_A_B)
      adc8(&cp.A, &cp.B);
      RETURN_FROM_INS(ADC_A_B)
    case ADC_A_C:
      PRINT_INS(ADC_A_C)
      adc8(&cp.A, &cp.C);
      RETURN_FROM_INS(ADC_A_C)
    case ADC_A_D:
      PRINT_INS(ADC_A_D)
      adc8(&cp.A, &cp.D);
      RETURN_FROM_INS(ADC_A_D)
    case ADC_A_E:
      PRINT_INS(ADC_A_E)
      adc8(&cp.A, &cp.E);
      RETURN_FROM_INS(ADC_A_E)
    case ADC_A_H:
      PRINT_INS(ADC_A_H)
      adc8(&cp.A, &cp.H);
      RETURN_FROM_INS(ADC_A_H)
    case ADC_A_L:
      PRINT_INS(ADC_A_L)
      adc8(&cp.A, &cp.L);
      RETURN_FROM_INS(ADC_A_L)
    case ADC_A_star_HL:
      PRINT_INS(ADC_A_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        adc8(&cp.A, &data);
      }
      RETURN_FROM_INS(ADC_A_star_HL)
    case ADC_A_A:
      PRINT_INS(ADC_A_A)
      adc8(&cp.A, &cp.A);
      RETURN_FROM_INS(ADC_A_A)
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

void add8(uint8_t *op1, uint8_t *op2)
{
  uint16_t overflow8 = ((*op1 + *op2) >> 8);
  uint8_t overflow3 = ((*op1 & 0x7) + (*op2 & 0x7)) >> 3;
  cp.n = cp.h = cp.cf = cp.zf = 0;
  if(overflow8)
    cp.cf = 1;
  if(overflow3)
    cp.h = 1;
  *op1 += *op2;

  if(*op1 == 0)
    cp.zf = 1;
}

void adc8(uint8_t *op1, uint8_t *op2)
{
  cp.n = 0;
  uint16_t result;
  uint8_t halfcarry;
  halfcarry = (*op1 & 0xF) + (*op2 & 0xF) + cp.cf;
  result = *op1 + *op2 + cp.cf;

  if(halfcarry >> 4)
    cp.h = 1;
  else
    cp.h = 0;

  if(result >> 8)
    cp.cf = 1;
  else
    cp.cf = 0;

   *op1 = (result & 0xFF);
   cp.zf = (*op1 == 0);
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
void daa()
{
  if(cp.n == 0) //if called after addition
  {
    if(cp.cf || cp.A > 0x99) { cp.A += 0x60; cp.cf = 1; }
    if(cp.h || ((cp.A & 0xF) > 9)) { cp.A += 0x06; }
  }
  else //if called after subtraction
  {
    if(cp.cf) { cp.A -= 0x60; }
    if(cp.h) { cp.A -= 0x06; }
  }
  cp.zf = (cp.A == 0);
  cp.h = 0;
}
