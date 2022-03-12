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
    case SUB_B:
      PRINT_INS(SUB_B)
      sub8(&cp.B);
      RETURN_FROM_INS(SUB_B)
    case SUB_C:
      PRINT_INS(SUB_C)
      sub8(&cp.C);
      RETURN_FROM_INS(SUB_C)
    case SUB_D:
      PRINT_INS(SUB_D)
      sub8(&cp.D);
      RETURN_FROM_INS(SUB_D)
    case SUB_E:
      PRINT_INS(SUB_E)
      sub8(&cp.E);
      RETURN_FROM_INS(SUB_E)
    case SUB_H:
      PRINT_INS(SUB_H)
      sub8(&cp.H);
      RETURN_FROM_INS(SUB_H)
    case SUB_L:
      PRINT_INS(SUB_L)
      sub8(&cp.L);
      RETURN_FROM_INS(SUB_L)
    case SUB_star_HL:
      PRINT_INS(SUB_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        sub8(&data);
      }
      RETURN_FROM_INS(SUB_star_HL)
    case SUB_A:
      PRINT_INS(SUB_A)
      sub8(&cp.A);
      RETURN_FROM_INS(SUB_A)
    case SBC_B:
      PRINT_INS(SBC_B)
      sbc8(&cp.B);
      RETURN_FROM_INS(SBC_B)
    case SBC_C:
      PRINT_INS(SBC_C)
      sbc8(&cp.C);
      RETURN_FROM_INS(SBC_C)
    case SBC_D:
      PRINT_INS(SBC_D)
      sbc8(&cp.D);
      RETURN_FROM_INS(SBC_D)
    case SBC_E:
      PRINT_INS(SBC_E)
      sbc8(&cp.E);
      RETURN_FROM_INS(SBC_E)
    case SBC_H:
      PRINT_INS(SBC_H)
      sbc8(&cp.H);
      RETURN_FROM_INS(SBC_H)
    case SBC_L:
      PRINT_INS(SBC_L)
      sbc8(&cp.L);
      RETURN_FROM_INS(SBC_L)
    case SBC_star_HL:
      PRINT_INS(SBC_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        sbc8(&data);
      }
      RETURN_FROM_INS(SBC_star_HL)
    case SBC_A:
      PRINT_INS(SBC_A)
      sbc8(&cp.A);
      RETURN_FROM_INS(SBC_A)
    case AND_B:
      PRINT_INS(AND_B)
      and8(&cp.B);
      RETURN_FROM_INS(AND_B)
    case AND_C:
      PRINT_INS(AND_C)
      and8(&cp.C);
      RETURN_FROM_INS(AND_C)
    case AND_D:
      PRINT_INS(AND_D)
      and8(&cp.D);
      RETURN_FROM_INS(AND_D)
    case AND_E:
      PRINT_INS(AND_E)
      and8(&cp.E);
      RETURN_FROM_INS(AND_E)
    case AND_H:
      PRINT_INS(AND_H)
      and8(&cp.H);
      RETURN_FROM_INS(AND_H)
    case AND_L:
      PRINT_INS(AND_L)
      and8(&cp.L);
      RETURN_FROM_INS(AND_L)
    case AND_star_HL:
      PRINT_INS(SBC_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        and8(&data);
      }
      RETURN_FROM_INS(AND_star_HL)
    case AND_A:
      PRINT_INS(AND_A)
      and8(&cp.A);
      RETURN_FROM_INS(AND_A)
    case XOR_B:
      PRINT_INS(XOR_B)
      xor8(&cp.B);
      RETURN_FROM_INS(XOR_B)
    case XOR_C:
      PRINT_INS(XOR_C)
      xor8(&cp.C);
      RETURN_FROM_INS(XOR_C)
    case XOR_D:
      PRINT_INS(XOR_D)
      xor8(&cp.D);
      RETURN_FROM_INS(XOR_D)
    case XOR_E:
      PRINT_INS(XOR_E)
      xor8(&cp.E);
      RETURN_FROM_INS(XOR_E)
    case XOR_H:
      PRINT_INS(XOR_H)
      xor8(&cp.H);
      RETURN_FROM_INS(XOR_H)
    case XOR_L:
      PRINT_INS(XOR_L)
      xor8(&cp.L);
      RETURN_FROM_INS(XOR_L)
    case XOR_star_HL:
      PRINT_INS(SBC_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        xor8(&data);
      }
      RETURN_FROM_INS(XOR_star_HL)
    case XOR_A:
      PRINT_INS(XOR_A)
      xor8(&cp.A);
      RETURN_FROM_INS(XOR_A)
    case OR_B:
      PRINT_INS(OR_B)
      or8(&cp.B);
      RETURN_FROM_INS(OR_B)
    case OR_C:
      PRINT_INS(OR_C)
      or8(&cp.C);
      RETURN_FROM_INS(OR_C)
    case OR_D:
      PRINT_INS(OR_D)
      or8(&cp.D);
      RETURN_FROM_INS(OR_D)
    case OR_E:
      PRINT_INS(OR_E)
      or8(&cp.E);
      RETURN_FROM_INS(OR_E)
    case OR_H:
      PRINT_INS(OR_H)
      or8(&cp.H);
      RETURN_FROM_INS(OR_H)
    case OR_L:
      PRINT_INS(OR_L)
      or8(&cp.L);
      RETURN_FROM_INS(OR_L)
    case OR_star_HL:
      PRINT_INS(SBC_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        or8(&data);
      }
      RETURN_FROM_INS(OR_star_HL)
    case OR_A:
      PRINT_INS(OR_A)
      or8(&cp.A);
      RETURN_FROM_INS(OR_A)
    case CP_B:
      PRINT_INS(CP_B)
      cp8(&cp.B);
      RETURN_FROM_INS(CP_B)
    case CP_C:
      PRINT_INS(CP_C)
      cp8(&cp.C);
      RETURN_FROM_INS(CP_C)
    case CP_D:
      PRINT_INS(CP_D)
      cp8(&cp.D);
      RETURN_FROM_INS(CP_D)
    case CP_E:
      PRINT_INS(CP_E)
      cp8(&cp.E);
      RETURN_FROM_INS(CP_E)
    case CP_H:
      PRINT_INS(CP_H)
      cp8(&cp.H);
      RETURN_FROM_INS(CP_H)
    case CP_L:
      PRINT_INS(CP_L)
      cp8(&cp.L);
      RETURN_FROM_INS(CP_L)
    case CP_star_HL:
      PRINT_INS(SBC_star_HL)
      {
	uint8_t data;
	ldOp8FromMem(cp.HL, &data);
        cp8(&data);
      }
      RETURN_FROM_INS(CP_star_HL)
    case CP_A:
      PRINT_INS(CP_A)
      cp8(&cp.A);
      RETURN_FROM_INS(CP_A)
    case RET_NZ:
      PRINT_INS(RET_NZ)
      if(cp.zf == 0)
        pop16(&cp.PC);
      RETURN_FROM_INS(RET_NZ)
    case POP_BC:
      PRINT_INS(POP_BC)
      pop16(&cp.BC);
      RETURN_FROM_INS(POP_BC)
    case JP_NZ_IMM16:
      PRINT_INS(JP_NZ_IMM16)
      {
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        if(cp.zf == 0)
	{
          cp.PC =  helper;
	  break;
	}
      }
      RETURN_FROM_INS(JP_NZ_IMM16)
    case JP_IMM16:
      PRINT_INS(JP_IMM16)
      {
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        cp.PC =  helper;
	break;
      }
      RETURN_FROM_INS(JP_IMM16)
    case CALL_NZ_IMM16:
      PRINT_INS(CALL_NZ_IMM16)
      if(cp.zf == 0)
      {
        push16(cp.PC + instructions[CALL_NZ_IMM16].len -1);
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        cp.PC = helper;
	break;
      }
      RETURN_FROM_INS(CALL_NZ_IMM16)
    case PUSH_BC:
      PRINT_INS(PUSH_BC)
      push16(cp.BC);
      RETURN_FROM_INS(PUSH_BC)
    case ADD_A_IMM8:
      PRINT_INS(ADD_A_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        add8(&cp.A, &helper);
      }
      RETURN_FROM_INS(ADD_A_IMM8)
    case RST_0:
      PRINT_INS(RST_0)
      rst(RST_0);
      RETURN_FROM_INS(RST_0)
    case RET_Z:
      PRINT_INS(RET_Z)
      if(cp.zf == 1)
        pop16(&cp.PC);
      RETURN_FROM_INS(RET_Z)
    case RET:
      PRINT_INS(RET)
      pop16(&cp.PC);
      break;
      RETURN_FROM_INS(RET)
    case JP_Z_IMM16:
      PRINT_INS(JP_Z_IMM16)
      {
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        if(cp.zf == 1)
	{
          cp.PC =  helper;
	  break;
	}
      }
      RETURN_FROM_INS(JP_Z_IMM16)
    case CB_INST:
      return decodeCB();
    case CALL_Z_IMM16:
      PRINT_INS(CALL_Z_IMM16)
      if(cp.zf == 1)
      {
        push16(cp.PC + instructions[CALL_Z_IMM16].len -1);
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        cp.PC = helper;
	break;
      }
      RETURN_FROM_INS(CALL_Z_IMM16)
    case CALL_IMM16:
      PRINT_INS(CALL_IMM16)
      {
        push16(cp.PC + instructions[CALL_IMM16].len -1);
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        cp.PC = helper;
	break;
      }
      RETURN_FROM_INS(CALL_Z_IMM16)
    case ADC_A_IMM8:
      PRINT_INS(ADC_A_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        adc8(&cp.A, &helper);
      }
      RETURN_FROM_INS(ADC_A_IMM8)
    case RST_1:
      PRINT_INS(RST_1)
      rst(RST_1);
      RETURN_FROM_INS(RST_1)
    case RET_NC:
      PRINT_INS(RET_NC)
      if(cp.cf == 0)
        pop16(&cp.PC);
      RETURN_FROM_INS(RET_NC)
    case POP_DE:
      PRINT_INS(POP_DE)
      pop16(&cp.DE);
      RETURN_FROM_INS(POP_DE)
    case JP_NC_IMM16:
      PRINT_INS(JP_NC_IMM16)
      {
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        if(cp.cf == 0)
        {
          cp.PC =  helper;
          break;
	}
      }
      RETURN_FROM_INS(JP_NC_IMM16)
    case CALL_NC_IMM16:
      PRINT_INS(CALL_NC_IMM16)
      if(cp.cf == 0)
      {
        push16(cp.PC + instructions[CALL_NC_IMM16].len -1);
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        cp.PC = helper;
	break;
      }
      RETURN_FROM_INS(CALL_NC_IMM16)
    case PUSH_DE:
      PRINT_INS(PUSH_DE)
      push16(cp.DE);
      RETURN_FROM_INS(PUSH_DE)
    case SUB_IMM8:
      PRINT_INS(SUB_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        sub8(&helper);
      }
      RETURN_FROM_INS(SUB_IMM8)
    case RST_2:
      PRINT_INS(RST_2)
      rst(RST_2);
      RETURN_FROM_INS(RST_2)
    case RET_C:
      PRINT_INS(RET_C)
      if(cp.cf == 1)
        pop16(&cp.PC);
      RETURN_FROM_INS(RET_C)
    case RETI:
      PRINT_INS(RETI)
      pop16(&cp.PC);
      cp.interrupts_master_enabled=1;
      RETURN_FROM_INS(RETI);
    case JP_C_IMM16:
      PRINT_INS(JP_C_IMM16)
      {
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        if(cp.cf == 1)
	{
          cp.PC =  helper;
	  break;
	}
      }
      RETURN_FROM_INS(JP_C_IMM16)
    case CALL_C_IMM16:
      PRINT_INS(CALL_C_IMM16)
      if(cp.cf == 1)
      {
        push16(cp.PC + instructions[CALL_C_IMM16].len -1);
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        cp.PC = helper;
	break;
      }
      RETURN_FROM_INS(CALL_NC_IMM16)
    case SBC_A_IMM8:
      PRINT_INS(SBC_A_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        sbc8(&helper);
      }
      RETURN_FROM_INS(SBC_A_IMM8)
    case RST_3:
      PRINT_INS(RST_3)
      rst(RST_3);
      RETURN_FROM_INS(RST_3)
    case LD_star_IMM8_A:
      PRINT_INS(LD_star_IMM8_A)
      {
        uint8_t offset;
        ldOp8FromMemAtPC(&offset);
        ldOp8ToMem(cp.A, 0xFF00 | offset);
      }
      RETURN_FROM_INS(LD_star_IMM8_A)
    case POP_HL:
      PRINT_INS(POP_HL)
      pop16(&cp.HL);
      RETURN_FROM_INS(POP_HL)
    case LD_star_C_A:
      PRINT_INS(LD_C_A)
      ldOp8ToMem(cp.A, 0xFF00 | cp.C);
      RETURN_FROM_INS(LD_C_A)
    case PUSH_HL:
      PRINT_INS(PUSH_HL)
      push16(cp.HL);
      RETURN_FROM_INS(PUSH_HL)
    case AND_IMM8:
      PRINT_INS(AND_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        and8(&helper);
      }
      RETURN_FROM_INS(AND_IMM8)
    case RST_4:
      PRINT_INS(RST_4)
      rst(RST_4);
      RETURN_FROM_INS(RST_4)
    case LD_star_IMM16_A:
      PRINT_INS(LD_star_IMM16_A)
      {
        uint16_t addr;
        ldOp16FromMemAtPC(&addr);
        ldOp8ToMem(cp.A, addr);
      }
      RETURN_FROM_INS(LD_star_IMM16_A)
    case XOR_IMM8:
      PRINT_INS(XOR_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        xor8(&helper);
      }
      RETURN_FROM_INS(XOR_IMM8)
    case RST_5:
      PRINT_INS(RST_5)
      rst(RST_5);
      RETURN_FROM_INS(RST_5)
    case LD_A_star_IMM8:
      PRINT_INS(LD_A_star_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        ldOp8FromMem(0xFF00 | helper, &cp.A);
      }
      RETURN_FROM_INS(LD_A_star_IMM8)
    case POP_AF:
      PRINT_INS(POP_AF)
      pop16AF();
      RETURN_FROM_INS(POP_AF)
    case LD_A_star_C:
      PRINT_INS(LD_A_star_C)
      ldOp8FromMem(0xFF00 | cp.C, &cp.A);
      RETURN_FROM_INS(LD_A_star_C)
    case DI:
      PRINT_INS(DI)
      cp.interrupts_master_enabled = 0;
      RETURN_FROM_INS(DI)
    case PUSH_AF:
      PRINT_INS(PUSH_AF)
      push16(cp.AF);
      RETURN_FROM_INS(PUSH_AF)
    case OR_IMM8:
      PRINT_INS(OR_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        or8(&helper);
      }
      RETURN_FROM_INS(OR_IMM8)
    case RST_6:
      PRINT_INS(RST_6)
      rst(RST_6);
      RETURN_FROM_INS(RST_6)
    case ADD_SP_IMM8:
      PRINT_INS(ADD_SP_IMM8)
      {
        int8_t helper;
        ldOp8FromMemAtPC(&helper);
	cp.zf = cp.n = 0;
	cp.cf = ((cp.SP & 0xFF) + (helper & 0xFF)) > 0xFF;
	cp.h = ((cp.SP & 0xF) + (helper & 0xF)) > 0xF;
	cp.SP += helper;
      }
      RETURN_FROM_INS(ADD_SP_IMM8)
    case JP_HL:
      PRINT_INS(JP_HL)
      cp.PC = cp.HL;
      break;
    case LD_HL_SP_plus_IMM8:
      PRINT_INS(LD_HL_SP_plus_IMM8)
      {
        int8_t op;
	int16_t helper;
	cp.zf = cp.n = cp.h = cp.cf = 0;
	ldOp8FromMemAtPC(&op);
	helper = cp.SP + op;

	cp.cf = ((cp.SP & 0xFF) + (op & 0xFF)) > 0xFF;
        cp.h =  ((cp.SP & 0xF) + (op & 0xF)) > 0xF;
	cp.HL = cp.SP + op;
      }
      RETURN_FROM_INS(LD_HL_SP_plus_IMM8)
    case LD_SP_HL:
      PRINT_INS(LD_SP_HL)
      cp.SP = cp.HL;
      RETURN_FROM_INS(LD_SP_HL)
    case LD_A_star_IMM16:
      PRINT_INS(LD_A_star_IMM16)
      {
	uint16_t helper;
	ldOp16FromMemAtPC(&helper);
        ldOp8FromMem(helper, &cp.A);  
      }
      RETURN_FROM_INS(LD_A_star_IMM16)
    case EI:
      PRINT_INS(EI)
      cp.interrupts_master_enabled = 1;
      RETURN_FROM_INS(EI)
    case CP_IMM8:
      PRINT_INS(CP_IMM8)
      {
	uint8_t helper;
        ldOp8FromMemAtPC(&helper);
        cp8(&helper);
      }
      RETURN_FROM_INS(CP_IMM8)
    case RST_7:
      PRINT_INS(RST_7)
      rst(RST_7);
      RETURN_FROM_INS(RST_7)
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

static inline void move_pc_cb(uint8_t opcode)
{
  cp.PC += instructionsCB[opcode].len-1;
}

static inline void print_ins_cb(uint8_t opcode)
{
  printf("%s \n", instructionsCB[opcode].string);
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

void ldOp16FromMemAtSP(uint16_t *dest)
{
  ldOp16FromMem(cp.SP, dest);
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

void sub8(uint8_t *op)
{
  cp.h = 0;
  cp.cf = 0;
  cp.n = 1;

  if(*op > cp.A)
    cp.cf = 1;

  if((*op & 0xF) > (cp.A & 0xF))
    cp.h = 1;

  cp.A =  cp.A - *op;
  cp.zf = (cp.A == 0);
}

void sbc8(uint8_t *op)
{
  cp.n = 1;
  cp.h = 0;
  uint8_t carry = 0;
  if( (*op + cp.cf) > cp.A )
    carry = 1;

  int8_t halfcarry;
  halfcarry = (cp.A & 0xF) - (*op & 0xF) - cp.cf;
  if( halfcarry < 0 )
    cp.h = 1;

  cp.A =  cp.A - *op - cp.cf;

  cp.cf = carry;
  cp.zf = (cp.A == 0);
}

void and8(uint8_t *op)
{
  cp.n = 0;
  cp.h = 1; 
  cp.cf = 0;

  cp.A = cp.A & *op;
  cp.zf = cp.A == 0;
}
void xor8(uint8_t *op)
{
  cp.n = 0;
  cp.h = 0;
  cp.cf = 0;

  cp.A = cp.A ^ *op;
  cp.zf = cp.A == 0;
}
void or8(uint8_t *op)
{
  cp.n = 0;
  cp.h = 0;
  cp.cf = 0;

  cp.A = cp.A | *op;
  cp.zf = cp.A == 0;
}

void cp8(uint8_t *op)
{
  cp.n = 1;
  cp.h = 0;
  cp.cf = 0;

  if(cp.A < *op)
    cp.cf = 1;

  if( (cp.A & 0xF) < (*op & 0xF))
    cp.h = 1;

  cp.zf = cp.A == *op;
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

void pop16(uint16_t *out)
{
  ldOp16FromMemAtSP(out);
  cp.SP+=2;
}

void pop16AF()
{
  ldOp16FromMemAtSP(&cp.AF);
  //lets clear the not used bits here
  cp.F = cp.F & 0xF0;
  cp.SP+=2;
}

void push16(uint16_t in)
{
  ldOp8ToMem(in >> 8, cp.SP-1);
  ldOp8ToMem(in & 0xFF, cp.SP-2);
  cp.SP-=2;
}

uint8_t getOffset(uint8_t opcode)
{
  uint8_t t;
  //extract bit 5, 4, 3
  t=opcode >>3;
  t=t & 0x7;
  if(t == 0)
    return 0x0;
  if(t == 1)
    return 0x8;
  if(t == 2)
    return 0x10;
  if(t == 3)
    return 0x18;
  if(t == 4)
    return 0x20;
  if(t == 5)
    return 0x28;
  if(t == 6)
    return 0x30;
  if(t == 7)
    return 0x38;

  printf("You should not end up here\n");
}

void rst(uint8_t opcode)
{
  push16(cp.PC);
  cp.PC=0;
  cp.PC = cp.PC | (getOffset(opcode) & 0xFF);
}

uint8_t decodeCB()
{
  uint8_t opcode;
  ldOp8FromMemAtPC(&opcode);
  switch(opcode)
  {
    case RLC_B:
      PRINT_INS_CB(RLC_B)
      rlc(&cp.B);
      RETURN_FROM_INS_CB(RLC_B)
    case RLC_C:
      PRINT_INS_CB(RLC_C)
      rlc(&cp.C);
      RETURN_FROM_INS_CB(RLC_C)
    case RLC_D:
      PRINT_INS_CB(RLC_D)
      rlc(&cp.D);
      RETURN_FROM_INS_CB(RLC_D)
    case RLC_E:
      PRINT_INS_CB(RLC_E)
      rlc(&cp.E);
      RETURN_FROM_INS_CB(RLC_E)
    case RLC_H:
      PRINT_INS_CB(RLC_H)
      rlc(&cp.H);
      RETURN_FROM_INS_CB(RLC_H)
    case RLC_L:
      PRINT_INS_CB(RLC_L)
      rlc(&cp.L);
      RETURN_FROM_INS_CB(RLC_L)
    case RLC_star_HL:
      PRINT_INS_CB(RLC_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        rlc(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RLC_star_HL)
    case RLC_A:
      PRINT_INS_CB(RLC_A)
      rlc(&cp.A);
      RETURN_FROM_INS_CB(RLC_A)
    case RRC_B:
      PRINT_INS_CB(RRC_B)
      rrc(&cp.B);
      RETURN_FROM_INS_CB(RRC_B)
    case RRC_C:
      PRINT_INS_CB(RRC_C)
      rrc(&cp.C);
      RETURN_FROM_INS_CB(RRC_C)
    case RRC_D:
      PRINT_INS_CB(RRC_D)
      rrc(&cp.D);
      RETURN_FROM_INS_CB(RRC_D)
    case RRC_E:
      PRINT_INS_CB(RRC_E)
      rrc(&cp.E);
      RETURN_FROM_INS_CB(RRC_E)
    case RRC_H:
      PRINT_INS_CB(RRC_H)
      rrc(&cp.H);
      RETURN_FROM_INS_CB(RRC_H)
    case RRC_L:
      PRINT_INS_CB(RRC_L)
      rrc(&cp.L);
      RETURN_FROM_INS_CB(RRC_L)
    case RRC_star_HL:
      PRINT_INS_CB(RRC_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        rrc(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RRC_star_HL)
    case RRC_A:
      PRINT_INS_CB(RRC_A)
      rrc(&cp.A);
      RETURN_FROM_INS_CB(RRC_A)
    case RL_B:
      PRINT_INS_CB(RL_B)
      rl(&cp.B);
      RETURN_FROM_INS_CB(RL_B)
    case RL_C:
      PRINT_INS_CB(RL_C)
      rl(&cp.C);
      RETURN_FROM_INS_CB(RL_C)
    case RL_D:
      PRINT_INS_CB(RL_D)
      rl(&cp.D);
      RETURN_FROM_INS_CB(RL_D)
    case RL_E:
      PRINT_INS_CB(RL_E)
      rl(&cp.E);
      RETURN_FROM_INS_CB(RL_E)
    case RL_H:
      PRINT_INS_CB(RL_H)
      rl(&cp.H);
      RETURN_FROM_INS_CB(RL_H)
    case RL_L:
      PRINT_INS_CB(RL_L)
      rl(&cp.L);
      RETURN_FROM_INS_CB(RL_L)
    case RL_star_HL:
      PRINT_INS_CB(RL_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        rl(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RL_star_HL)
    case RL_A:
      PRINT_INS_CB(RL_A)
      rl(&cp.A);
      RETURN_FROM_INS_CB(RL_A)
    case RR_B:
      PRINT_INS_CB(RR_B)
      rr(&cp.B);
      RETURN_FROM_INS_CB(RR_B)
    case RR_C:
      PRINT_INS_CB(RR_C)
      rr(&cp.C);
      RETURN_FROM_INS_CB(RR_C)
    case RR_D:
      PRINT_INS_CB(RR_D)
      rr(&cp.D);
      RETURN_FROM_INS_CB(RR_D)
    case RR_E:
      PRINT_INS_CB(RR_E)
      rr(&cp.E);
      RETURN_FROM_INS_CB(RR_E)
    case RR_H:
      PRINT_INS_CB(RR_H)
      rr(&cp.H);
      RETURN_FROM_INS_CB(RR_H)
    case RR_L:
      PRINT_INS_CB(RR_L)
      rr(&cp.L);
      RETURN_FROM_INS_CB(RR_L)
    case RR_star_HL:
      PRINT_INS_CB(RR_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        rr(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RR_star_HL)
    case RR_A:
      PRINT_INS_CB(RR_A)
      rr(&cp.A);
      RETURN_FROM_INS_CB(RR_A)
  }
}

void rlc(uint8_t *op)
{
  cp.n = cp.h = 0;
  uint8_t save = *op;
  *op <<= 1;
  *op = *op | (save >> 7);
  cp.cf = save >> 7;
  cp.zf = *op == 0;
}

void rrc(uint8_t *op)
{
  cp.n = cp.h = 0;
  uint8_t save = *op;
  *op >>= 1;
  *op = *op | (save << 7);
  cp.cf =  (save & 0x1);
  cp.zf = *op == 0;
}

void rl(uint8_t *op)
{
  cp.n = cp.h = 0;
  uint8_t save = *op;
  *op <<= 1;
  *op = *op | cp.cf;
  cp.cf = (save >> 7) == 1;
  cp.zf = *op == 0;
}

void rr(uint8_t *op)
{
  cp.n = cp.h = 0;
  uint8_t save = *op;
  *op >>= 1;
  *op = *op | (cp.cf << 7);
  cp.cf = (save & 0x1) == 1;
  cp.zf = *op == 0;
}
