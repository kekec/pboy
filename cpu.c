#include "string.h"
#include <stdio.h>
#include "stdio.h"
#include "cpu.h"
#include "instruction.h"
#include "mmu.h"
#include "timer.h"

uint8_t *mem;

void cpuInit(uint8_t * address, uint16_t start)
{
  mmuInit(address);
  timerInit();
  cp.PC = start;
  logReadMem = NULL;
  logWriteMem = NULL;
}

void cpuEnableSim()
{
  simulated = 1;
}

//I assume that the cpuStep function will be called 60 times per second
void cpuStep()
{
  uint32_t cycles=0;
  const uint32_t MAX_CYCLES = CPU_CLK/60;
  
  while(cycles <= MAX_CYCLES) 
  {
    if(!cp.halted)
      cycles += executeInstruction();
    else
      cycles += 4;

    if(simulated)
      return;

    timerProcess(cycles);
    checkInterrupt();
  }
}

unsigned int executeInstruction()
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
	cp.PC++; //PC seems to be off by one if I don't increment
        RETURN_MAX_CYCLES(JR_NZ_imm8)
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
        RETURN_MAX_CYCLES(CALL_NZ_IMM16)
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
      {
        pop16(&cp.PC);
        RETURN_MAX_CYCLES(RET_Z)
      }
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
  mmuWriteMem(addr, data);
}

uint8_t readMem(uint16_t addr)
{
  return mmuReadMem(addr);
}

void registerLogReadMem(uint8_t (*func) (uint16_t) )
{
  mmuRegisterLogReadMem(func);
}

void registerLogWriteMem( void (*func) (uint16_t, uint8_t) )
{
  mmuRegisterLogWriteMem(func);
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
  uint8_t overflow3 = ((*op1 & 0xF) + (*op2 & 0xF)) >> 4;
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
    case SLA_B:
      PRINT_INS_CB(SLA_B)
      sla(&cp.B);
      RETURN_FROM_INS_CB(SLA_B)
    case SLA_C:
      PRINT_INS_CB(SLA_C)
      sla(&cp.C);
      RETURN_FROM_INS_CB(SLA_C)
    case SLA_D:
      PRINT_INS_CB(SLA_D)
      sla(&cp.D);
      RETURN_FROM_INS_CB(SLA_D)
    case SLA_E:
      PRINT_INS_CB(SLA_E)
      sla(&cp.E);
      RETURN_FROM_INS_CB(SLA_E)
    case SLA_H:
      PRINT_INS_CB(SLA_H)
      sla(&cp.H);
      RETURN_FROM_INS_CB(SLA_H)
    case SLA_L:
      PRINT_INS_CB(SLA_L)
      sla(&cp.L);
      RETURN_FROM_INS_CB(SLA_L)
    case SLA_star_HL:
      PRINT_INS_CB(SLA_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        sla(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SLA_star_HL)
    case SLA_A:
      PRINT_INS_CB(SLA_A)
      sla(&cp.A);
      RETURN_FROM_INS_CB(SLA_A)
    case SRA_B:
      PRINT_INS_CB(SRA_B)
      sra(&cp.B);
      RETURN_FROM_INS_CB(SRA_B)
    case SRA_C:
      PRINT_INS_CB(SRA_C)
      sra(&cp.C);
      RETURN_FROM_INS_CB(SRA_C)
    case SRA_D:
      PRINT_INS_CB(SRA_D)
      sra(&cp.D);
      RETURN_FROM_INS_CB(SRA_D)
    case SRA_E:
      PRINT_INS_CB(SRA_E)
      sra(&cp.E);
      RETURN_FROM_INS_CB(SRA_E)
    case SRA_H:
      PRINT_INS_CB(SRA_H)
      sra(&cp.H);
      RETURN_FROM_INS_CB(SRA_H)
    case SRA_L:
      PRINT_INS_CB(SRA_L)
      sra(&cp.L);
      RETURN_FROM_INS_CB(SRA_L)
    case SRA_star_HL:
      PRINT_INS_CB(SRA_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        sra(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SRA_star_HL)
    case SRA_A:
      PRINT_INS_CB(SRA_A)
      sra(&cp.A);
      RETURN_FROM_INS_CB(SRA_A)
    case SWAP_B:
      PRINT_INS_CB(SWAP_B)
      swap(&cp.B);
      RETURN_FROM_INS_CB(SWAP_B)
    case SWAP_C:
      PRINT_INS_CB(SWAP_C)
      swap(&cp.C);
      RETURN_FROM_INS_CB(SWAP_C)
    case SWAP_D:
      PRINT_INS_CB(SWAP_D)
      swap(&cp.D);
      RETURN_FROM_INS_CB(SWAP_D)
    case SWAP_E:
      PRINT_INS_CB(SWAP_E)
      swap(&cp.E);
      RETURN_FROM_INS_CB(SWAP_E)
    case SWAP_H:
      PRINT_INS_CB(SWAP_H)
      swap(&cp.H);
      RETURN_FROM_INS_CB(SWAP_H)
    case SWAP_L:
      PRINT_INS_CB(SWAP_L)
      swap(&cp.L);
      RETURN_FROM_INS_CB(SWAP_L)
    case SWAP_star_HL:
      PRINT_INS_CB(SWAP_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        swap(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SWAP_star_HL)
    case SWAP_A:
      PRINT_INS_CB(SWAP_A)
      swap(&cp.A);
      RETURN_FROM_INS_CB(SWAP_A)
    case SRL_B:
      PRINT_INS_CB(SRL_B)
      srl(&cp.B);
      RETURN_FROM_INS_CB(SRL_B)
    case SRL_C:
      PRINT_INS_CB(SRL_C)
      srl(&cp.C);
      RETURN_FROM_INS_CB(SRL_C)
    case SRL_D:
      PRINT_INS_CB(SRL_D)
      srl(&cp.D);
      RETURN_FROM_INS_CB(SRL_D)
    case SRL_E:
      PRINT_INS_CB(SRL_E)
      srl(&cp.E);
      RETURN_FROM_INS_CB(SRL_E)
    case SRL_H:
      PRINT_INS_CB(SRL_H)
      srl(&cp.H);
      RETURN_FROM_INS_CB(SRL_H)
    case SRL_L:
      PRINT_INS_CB(SRL_L)
      srl(&cp.L);
      RETURN_FROM_INS_CB(SRL_L)
    case SRL_star_HL:
      PRINT_INS_CB(SRL_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        srl(&dummy);
        ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SRL_star_HL)
    case SRL_A:
      PRINT_INS_CB(SRL_A)
      srl(&cp.A);
      RETURN_FROM_INS_CB(SRL_A)
    case BIT_0_B:
      PRINT_INS_CB(BIT_0_B)
      bit0(&cp.B);
      RETURN_FROM_INS_CB(BIT_0_B)
    case BIT_0_C:
      PRINT_INS_CB(BIT_0_C)
      bit0(&cp.C);
      RETURN_FROM_INS_CB(BIT_0_C)
    case BIT_0_D:
      PRINT_INS_CB(BIT_0_D)
      bit0(&cp.D);
      RETURN_FROM_INS_CB(BIT_0_D)
    case BIT_0_E:
      PRINT_INS_CB(BIT_0_E)
      bit0(&cp.E);
      RETURN_FROM_INS_CB(BIT_0_E)
    case BIT_0_H:
      PRINT_INS_CB(BIT_0_H)
      bit0(&cp.H);
      RETURN_FROM_INS_CB(BIT_0_H)
    case BIT_0_L:
      PRINT_INS_CB(BIT_0_L)
      bit0(&cp.L);
      RETURN_FROM_INS_CB(BIT_0_L)
    case BIT_0_star_HL:
      PRINT_INS_CB(BIT_0_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit0(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_0_star_HL)
    case BIT_0_A:
      PRINT_INS_CB(BIT_0_A)
      bit0(&cp.A);
      RETURN_FROM_INS_CB(BIT_0_A)
    case BIT_1_B:
      PRINT_INS_CB(BIT_1_B)
      bit1(&cp.B);
      RETURN_FROM_INS_CB(BIT_1_B)
    case BIT_1_C:
      PRINT_INS_CB(BIT_1_C)
      bit1(&cp.C);
      RETURN_FROM_INS_CB(BIT_1_C)
    case BIT_1_D:
      PRINT_INS_CB(BIT_1_D)
      bit1(&cp.D);
      RETURN_FROM_INS_CB(BIT_1_D)
    case BIT_1_E:
      PRINT_INS_CB(BIT_1_E)
      bit1(&cp.E);
      RETURN_FROM_INS_CB(BIT_1_E)
    case BIT_1_H:
      PRINT_INS_CB(BIT_1_H)
      bit1(&cp.H);
      RETURN_FROM_INS_CB(BIT_1_H)
    case BIT_1_L:
      PRINT_INS_CB(BIT_1_L)
      bit1(&cp.L);
      RETURN_FROM_INS_CB(BIT_1_L)
    case BIT_1_star_HL:
      PRINT_INS_CB(BIT_1_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit1(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_1_star_HL)
    case BIT_1_A:
      PRINT_INS_CB(BIT_1_A)
      bit1(&cp.A);
      RETURN_FROM_INS_CB(BIT_1_A)
    case BIT_2_B:
      PRINT_INS_CB(BIT_2_B)
      bit2(&cp.B);
      RETURN_FROM_INS_CB(BIT_2_B)
    case BIT_2_C:
      PRINT_INS_CB(BIT_2_C)
      bit2(&cp.C);
      RETURN_FROM_INS_CB(BIT_2_C)
    case BIT_2_D:
      PRINT_INS_CB(BIT_2_D)
      bit2(&cp.D);
      RETURN_FROM_INS_CB(BIT_2_D)
    case BIT_2_E:
      PRINT_INS_CB(BIT_2_E)
      bit2(&cp.E);
      RETURN_FROM_INS_CB(BIT_2_E)
    case BIT_2_H:
      PRINT_INS_CB(BIT_2_H)
      bit2(&cp.H);
      RETURN_FROM_INS_CB(BIT_2_H)
    case BIT_2_L:
      PRINT_INS_CB(BIT_2_L)
      bit2(&cp.L);
      RETURN_FROM_INS_CB(BIT_2_L)
    case BIT_2_star_HL:
      PRINT_INS_CB(BIT_2_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit2(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_2_star_HL)
    case BIT_2_A:
      PRINT_INS_CB(BIT_2_A)
      bit2(&cp.A);
      RETURN_FROM_INS_CB(BIT_2_A)
    case BIT_3_B:
      PRINT_INS_CB(BIT_3_B)
      bit3(&cp.B);
      RETURN_FROM_INS_CB(BIT_3_B)
    case BIT_3_C:
      PRINT_INS_CB(BIT_3_C)
      bit3(&cp.C);
      RETURN_FROM_INS_CB(BIT_3_C)
    case BIT_3_D:
      PRINT_INS_CB(BIT_3_D)
      bit3(&cp.D);
      RETURN_FROM_INS_CB(BIT_3_D)
    case BIT_3_E:
      PRINT_INS_CB(BIT_3_E)
      bit3(&cp.E);
      RETURN_FROM_INS_CB(BIT_3_E)
    case BIT_3_H:
      PRINT_INS_CB(BIT_3_H)
      bit3(&cp.H);
      RETURN_FROM_INS_CB(BIT_3_H)
    case BIT_3_L:
      PRINT_INS_CB(BIT_3_L)
      bit3(&cp.L);
      RETURN_FROM_INS_CB(BIT_3_L)
    case BIT_3_star_HL:
      PRINT_INS_CB(BIT_3_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit3(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_3_star_HL)
    case BIT_3_A:
      PRINT_INS_CB(BIT_3_A)
      bit3(&cp.A);
      RETURN_FROM_INS_CB(BIT_3_A)
    case BIT_4_B:
      PRINT_INS_CB(BIT_4_B)
      bit4(&cp.B);
      RETURN_FROM_INS_CB(BIT_4_B)
    case BIT_4_C:
      PRINT_INS_CB(BIT_4_C)
      bit4(&cp.C);
      RETURN_FROM_INS_CB(BIT_4_C)
    case BIT_4_D:
      PRINT_INS_CB(BIT_4_D)
      bit4(&cp.D);
      RETURN_FROM_INS_CB(BIT_4_D)
    case BIT_4_E:
      PRINT_INS_CB(BIT_4_E)
      bit4(&cp.E);
      RETURN_FROM_INS_CB(BIT_4_E)
    case BIT_4_H:
      PRINT_INS_CB(BIT_4_H)
      bit4(&cp.H);
      RETURN_FROM_INS_CB(BIT_4_H)
    case BIT_4_L:
      PRINT_INS_CB(BIT_4_L)
      bit4(&cp.L);
      RETURN_FROM_INS_CB(BIT_4_L)
    case BIT_4_star_HL:
      PRINT_INS_CB(BIT_4_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit4(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_4_star_HL)
    case BIT_4_A:
      PRINT_INS_CB(BIT_4_A)
      bit4(&cp.A);
      RETURN_FROM_INS_CB(BIT_4_A)
    case BIT_5_B:
      PRINT_INS_CB(BIT_5_B)
      bit5(&cp.B);
      RETURN_FROM_INS_CB(BIT_5_B)
    case BIT_5_C:
      PRINT_INS_CB(BIT_5_C)
      bit5(&cp.C);
      RETURN_FROM_INS_CB(BIT_5_C)
    case BIT_5_D:
      PRINT_INS_CB(BIT_5_D)
      bit5(&cp.D);
      RETURN_FROM_INS_CB(BIT_5_D)
    case BIT_5_E:
      PRINT_INS_CB(BIT_5_E)
      bit5(&cp.E);
      RETURN_FROM_INS_CB(BIT_5_E)
    case BIT_5_H:
      PRINT_INS_CB(BIT_5_H)
      bit5(&cp.H);
      RETURN_FROM_INS_CB(BIT_5_H)
    case BIT_5_L:
      PRINT_INS_CB(BIT_5_L)
      bit5(&cp.L);
      RETURN_FROM_INS_CB(BIT_5_L)
    case BIT_5_star_HL:
      PRINT_INS_CB(BIT_5_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit5(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_5_star_HL)
    case BIT_5_A:
      PRINT_INS_CB(BIT_5_A)
      bit5(&cp.A);
      RETURN_FROM_INS_CB(BIT_5_A)
    case BIT_6_B:
      PRINT_INS_CB(BIT_6_B)
      bit6(&cp.B);
      RETURN_FROM_INS_CB(BIT_6_B)
    case BIT_6_C:
      PRINT_INS_CB(BIT_6_C)
      bit6(&cp.C);
      RETURN_FROM_INS_CB(BIT_6_C)
    case BIT_6_D:
      PRINT_INS_CB(BIT_6_D)
      bit6(&cp.D);
      RETURN_FROM_INS_CB(BIT_6_D)
    case BIT_6_E:
      PRINT_INS_CB(BIT_6_E)
      bit6(&cp.E);
      RETURN_FROM_INS_CB(BIT_6_E)
    case BIT_6_H:
      PRINT_INS_CB(BIT_6_H)
      bit6(&cp.H);
      RETURN_FROM_INS_CB(BIT_6_H)
    case BIT_6_L:
      PRINT_INS_CB(BIT_6_L)
      bit6(&cp.L);
      RETURN_FROM_INS_CB(BIT_6_L)
    case BIT_6_star_HL:
      PRINT_INS_CB(BIT_6_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit6(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_6_star_HL)
    case BIT_6_A:
      PRINT_INS_CB(BIT_6_A)
      bit6(&cp.A);
      RETURN_FROM_INS_CB(BIT_6_A)
    case BIT_7_B:
      PRINT_INS_CB(BIT_7_B)
      bit7(&cp.B);
      RETURN_FROM_INS_CB(BIT_7_B)
    case BIT_7_C:
      PRINT_INS_CB(BIT_7_C)
      bit7(&cp.C);
      RETURN_FROM_INS_CB(BIT_7_C)
    case BIT_7_D:
      PRINT_INS_CB(BIT_7_D)
      bit7(&cp.D);
      RETURN_FROM_INS_CB(BIT_7_D)
    case BIT_7_E:
      PRINT_INS_CB(BIT_7_E)
      bit7(&cp.E);
      RETURN_FROM_INS_CB(BIT_7_E)
    case BIT_7_H:
      PRINT_INS_CB(BIT_7_H)
      bit7(&cp.H);
      RETURN_FROM_INS_CB(BIT_7_H)
    case BIT_7_L:
      PRINT_INS_CB(BIT_7_L)
      bit7(&cp.L);
      RETURN_FROM_INS_CB(BIT_7_L)
    case BIT_7_star_HL:
      PRINT_INS_CB(BIT_7_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        bit7(&dummy);
      }
      RETURN_FROM_INS_CB(BIT_7_star_HL)
    case BIT_7_A:
      PRINT_INS_CB(BIT_7_A)
      bit7(&cp.A);
      RETURN_FROM_INS_CB(BIT_7_A)
    case RES_0_B:
      PRINT_INS_CB(RES_0_B)
      res0(&cp.B);
      RETURN_FROM_INS_CB(RES_0_B)
    case RES_0_C:
      PRINT_INS_CB(RES_0_C)
      res0(&cp.C);
      RETURN_FROM_INS_CB(RES_0_C)
    case RES_0_D:
      PRINT_INS_CB(RES_0_D)
      res0(&cp.D);
      RETURN_FROM_INS_CB(RES_0_D)
    case RES_0_E:
      PRINT_INS_CB(RES_0_E)
      res0(&cp.E);
      RETURN_FROM_INS_CB(RES_0_E)
    case RES_0_H:
      PRINT_INS_CB(RES_0_H)
      res0(&cp.H);
      RETURN_FROM_INS_CB(RES_0_H)
    case RES_0_L:
      PRINT_INS_CB(RES_0_L)
      res0(&cp.L);
      RETURN_FROM_INS_CB(RES_0_L)
    case RES_0_star_HL:
      PRINT_INS_CB(RES_0_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res0(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_0_star_HL)
    case RES_0_A:
      PRINT_INS_CB(RES_0_A)
      res0(&cp.A);
      RETURN_FROM_INS_CB(RES_0_A)
    case RES_1_B:
      PRINT_INS_CB(RES_1_B)
      res1(&cp.B);
      RETURN_FROM_INS_CB(RES_1_B)
    case RES_1_C:
      PRINT_INS_CB(RES_1_C)
      res1(&cp.C);
      RETURN_FROM_INS_CB(RES_1_C)
    case RES_1_D:
      PRINT_INS_CB(RES_1_D)
      res1(&cp.D);
      RETURN_FROM_INS_CB(RES_1_D)
    case RES_1_E:
      PRINT_INS_CB(RES_1_E)
      res1(&cp.E);
      RETURN_FROM_INS_CB(RES_1_E)
    case RES_1_H:
      PRINT_INS_CB(RES_1_H)
      res1(&cp.H);
      RETURN_FROM_INS_CB(RES_1_H)
    case RES_1_L:
      PRINT_INS_CB(RES_1_L)
      res1(&cp.L);
      RETURN_FROM_INS_CB(RES_1_L)
    case RES_1_star_HL:
      PRINT_INS_CB(RES_1_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res1(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_1_star_HL)
    case RES_1_A:
      PRINT_INS_CB(RES_1_A)
      res1(&cp.A);
      RETURN_FROM_INS_CB(RES_1_A)
    case RES_2_B:
      PRINT_INS_CB(RES_2_B)
      res2(&cp.B);
      RETURN_FROM_INS_CB(RES_2_B)
    case RES_2_C:
      PRINT_INS_CB(RES_2_C)
      res2(&cp.C);
      RETURN_FROM_INS_CB(RES_2_C)
    case RES_2_D:
      PRINT_INS_CB(RES_2_D)
      res2(&cp.D);
      RETURN_FROM_INS_CB(RES_2_D)
    case RES_2_E:
      PRINT_INS_CB(RES_2_E)
      res2(&cp.E);
      RETURN_FROM_INS_CB(RES_2_E)
    case RES_2_H:
      PRINT_INS_CB(RES_2_H)
      res2(&cp.H);
      RETURN_FROM_INS_CB(RES_2_H)
    case RES_2_L:
      PRINT_INS_CB(RES_2_L)
      res2(&cp.L);
      RETURN_FROM_INS_CB(RES_2_L)
    case RES_2_star_HL:
      PRINT_INS_CB(RES_2_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res2(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_2_star_HL)
    case RES_2_A:
      PRINT_INS_CB(RES_2_A)
      res2(&cp.A);
      RETURN_FROM_INS_CB(RES_2_A)
    case RES_3_B:
      PRINT_INS_CB(RES_3_B)
      res3(&cp.B);
      RETURN_FROM_INS_CB(RES_3_B)
    case RES_3_C:
      PRINT_INS_CB(RES_3_C)
      res3(&cp.C);
      RETURN_FROM_INS_CB(RES_3_C)
    case RES_3_D:
      PRINT_INS_CB(RES_3_D)
      res3(&cp.D);
      RETURN_FROM_INS_CB(RES_3_D)
    case RES_3_E:
      PRINT_INS_CB(RES_3_E)
      res3(&cp.E);
      RETURN_FROM_INS_CB(RES_3_E)
    case RES_3_H:
      PRINT_INS_CB(RES_3_H)
      res3(&cp.H);
      RETURN_FROM_INS_CB(RES_3_H)
    case RES_3_L:
      PRINT_INS_CB(RES_3_L)
      res3(&cp.L);
      RETURN_FROM_INS_CB(RES_3_L)
    case RES_3_star_HL:
      PRINT_INS_CB(RES_3_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res3(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_3_star_HL)
    case RES_3_A:
      PRINT_INS_CB(RES_3_A)
      res3(&cp.A);
      RETURN_FROM_INS_CB(RES_3_A)
    case RES_4_B:
      PRINT_INS_CB(RES_4_B)
      res4(&cp.B);
      RETURN_FROM_INS_CB(RES_4_B)
    case RES_4_C:
      PRINT_INS_CB(RES_4_C)
      res4(&cp.C);
      RETURN_FROM_INS_CB(RES_4_C)
    case RES_4_D:
      PRINT_INS_CB(RES_4_D)
      res4(&cp.D);
      RETURN_FROM_INS_CB(RES_4_D)
    case RES_4_E:
      PRINT_INS_CB(RES_4_E)
      res4(&cp.E);
      RETURN_FROM_INS_CB(RES_4_E)
    case RES_4_H:
      PRINT_INS_CB(RES_4_H)
      res4(&cp.H);
      RETURN_FROM_INS_CB(RES_4_H)
    case RES_4_L:
      PRINT_INS_CB(RES_4_L)
      res4(&cp.L);
      RETURN_FROM_INS_CB(RES_4_L)
    case RES_4_star_HL:
      PRINT_INS_CB(RES_4_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res4(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_4_star_HL)
    case RES_4_A:
      PRINT_INS_CB(RES_4_A)
      res4(&cp.A);
      RETURN_FROM_INS_CB(RES_4_A)
    case RES_5_B:
      PRINT_INS_CB(RES_5_B)
      res5(&cp.B);
      RETURN_FROM_INS_CB(RES_5_B)
    case RES_5_C:
      PRINT_INS_CB(RES_5_C)
      res5(&cp.C);
      RETURN_FROM_INS_CB(RES_5_C)
    case RES_5_D:
      PRINT_INS_CB(RES_5_D)
      res5(&cp.D);
      RETURN_FROM_INS_CB(RES_5_D)
    case RES_5_E:
      PRINT_INS_CB(RES_5_E)
      res5(&cp.E);
      RETURN_FROM_INS_CB(RES_5_E)
    case RES_5_H:
      PRINT_INS_CB(RES_5_H)
      res5(&cp.H);
      RETURN_FROM_INS_CB(RES_5_H)
    case RES_5_L:
      PRINT_INS_CB(RES_5_L)
      res5(&cp.L);
      RETURN_FROM_INS_CB(RES_5_L)
    case RES_5_star_HL:
      PRINT_INS_CB(RES_5_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res5(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_5_star_HL)
    case RES_5_A:
      PRINT_INS_CB(RES_5_A)
      res5(&cp.A);
      RETURN_FROM_INS_CB(RES_5_A)
    case RES_6_B:
      PRINT_INS_CB(RES_6_B)
      res6(&cp.B);
      RETURN_FROM_INS_CB(RES_6_B)
    case RES_6_C:
      PRINT_INS_CB(RES_6_C)
      res6(&cp.C);
      RETURN_FROM_INS_CB(RES_6_C)
    case RES_6_D:
      PRINT_INS_CB(RES_6_D)
      res6(&cp.D);
      RETURN_FROM_INS_CB(RES_6_D)
    case RES_6_E:
      PRINT_INS_CB(RES_6_E)
      res6(&cp.E);
      RETURN_FROM_INS_CB(RES_6_E)
    case RES_6_H:
      PRINT_INS_CB(RES_6_H)
      res6(&cp.H);
      RETURN_FROM_INS_CB(RES_6_H)
    case RES_6_L:
      PRINT_INS_CB(RES_6_L)
      res6(&cp.L);
      RETURN_FROM_INS_CB(RES_6_L)
    case RES_6_star_HL:
      PRINT_INS_CB(RES_6_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res6(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_6_star_HL)
    case RES_6_A:
      PRINT_INS_CB(RES_6_A)
      res6(&cp.A);
      RETURN_FROM_INS_CB(RES_6_A)
    case RES_7_B:
      PRINT_INS_CB(RES_7_B)
      res7(&cp.B);
      RETURN_FROM_INS_CB(RES_7_B)
    case RES_7_C:
      PRINT_INS_CB(RES_7_C)
      res7(&cp.C);
      RETURN_FROM_INS_CB(RES_7_C)
    case RES_7_D:
      PRINT_INS_CB(RES_7_D)
      res7(&cp.D);
      RETURN_FROM_INS_CB(RES_7_D)
    case RES_7_E:
      PRINT_INS_CB(RES_7_E)
      res7(&cp.E);
      RETURN_FROM_INS_CB(RES_7_E)
    case RES_7_H:
      PRINT_INS_CB(RES_7_H)
      res7(&cp.H);
      RETURN_FROM_INS_CB(RES_7_H)
    case RES_7_L:
      PRINT_INS_CB(RES_7_L)
      res7(&cp.L);
      RETURN_FROM_INS_CB(RES_7_L)
    case RES_7_star_HL:
      PRINT_INS_CB(RES_7_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        res7(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(RES_7_star_HL)
    case RES_7_A:
      PRINT_INS_CB(RES_7_A)
      res7(&cp.A);
      RETURN_FROM_INS_CB(RES_7_A)
    case SET_0_B:
      PRINT_INS_CB(SET_0_B)
      set0(&cp.B);
      RETURN_FROM_INS_CB(SET_0_B)
    case SET_0_C:
      PRINT_INS_CB(SET_0_C)
      set0(&cp.C);
      RETURN_FROM_INS_CB(SET_0_C)
    case SET_0_D:
      PRINT_INS_CB(SET_0_D)
      set0(&cp.D);
      RETURN_FROM_INS_CB(SET_0_D)
    case SET_0_E:
      PRINT_INS_CB(SET_0_E)
      set0(&cp.E);
      RETURN_FROM_INS_CB(SET_0_E)
    case SET_0_H:
      PRINT_INS_CB(SET_0_H)
      set0(&cp.H);
      RETURN_FROM_INS_CB(SET_0_H)
    case SET_0_L:
      PRINT_INS_CB(SET_0_L)
      set0(&cp.L);
      RETURN_FROM_INS_CB(SET_0_L)
    case SET_0_star_HL:
      PRINT_INS_CB(SET_0_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set0(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_0_star_HL)
    case SET_0_A:
      PRINT_INS_CB(SET_0_A)
      set0(&cp.A);
      RETURN_FROM_INS_CB(SET_0_A)
    case SET_1_B:
      PRINT_INS_CB(SET_1_B)
      set1(&cp.B);
      RETURN_FROM_INS_CB(SET_1_B)
    case SET_1_C:
      PRINT_INS_CB(SET_1_C)
      set1(&cp.C);
      RETURN_FROM_INS_CB(SET_1_C)
    case SET_1_D:
      PRINT_INS_CB(SET_1_D)
      set1(&cp.D);
      RETURN_FROM_INS_CB(SET_1_D)
    case SET_1_E:
      PRINT_INS_CB(SET_1_E)
      set1(&cp.E);
      RETURN_FROM_INS_CB(SET_1_E)
    case SET_1_H:
      PRINT_INS_CB(SET_1_H)
      set1(&cp.H);
      RETURN_FROM_INS_CB(SET_1_H)
    case SET_1_L:
      PRINT_INS_CB(SET_1_L)
      set1(&cp.L);
      RETURN_FROM_INS_CB(SET_1_L)
    case SET_1_star_HL:
      PRINT_INS_CB(SET_1_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set1(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_1_star_HL)
    case SET_1_A:
      PRINT_INS_CB(SET_1_A)
      set1(&cp.A);
      RETURN_FROM_INS_CB(SET_1_A)
    case SET_2_B:
      PRINT_INS_CB(SET_2_B)
      set2(&cp.B);
      RETURN_FROM_INS_CB(SET_2_B)
    case SET_2_C:
      PRINT_INS_CB(SET_2_C)
      set2(&cp.C);
      RETURN_FROM_INS_CB(SET_2_C)
    case SET_2_D:
      PRINT_INS_CB(SET_2_D)
      set2(&cp.D);
      RETURN_FROM_INS_CB(SET_2_D)
    case SET_2_E:
      PRINT_INS_CB(SET_2_E)
      set2(&cp.E);
      RETURN_FROM_INS_CB(SET_2_E)
    case SET_2_H:
      PRINT_INS_CB(SET_2_H)
      set2(&cp.H);
      RETURN_FROM_INS_CB(SET_2_H)
    case SET_2_L:
      PRINT_INS_CB(SET_2_L)
      set2(&cp.L);
      RETURN_FROM_INS_CB(SET_2_L)
    case SET_2_star_HL:
      PRINT_INS_CB(SET_2_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set2(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_2_star_HL)
    case SET_2_A:
      PRINT_INS_CB(SET_2_A)
      set2(&cp.A);
      RETURN_FROM_INS_CB(SET_2_A)
    case SET_3_B:
      PRINT_INS_CB(SET_3_B)
      set3(&cp.B);
      RETURN_FROM_INS_CB(SET_3_B)
    case SET_3_C:
      PRINT_INS_CB(SET_3_C)
      set3(&cp.C);
      RETURN_FROM_INS_CB(SET_3_C)
    case SET_3_D:
      PRINT_INS_CB(SET_3_D)
      set3(&cp.D);
      RETURN_FROM_INS_CB(SET_3_D)
    case SET_3_E:
      PRINT_INS_CB(SET_3_E)
      set3(&cp.E);
      RETURN_FROM_INS_CB(SET_3_E)
    case SET_3_H:
      PRINT_INS_CB(SET_3_H)
      set3(&cp.H);
      RETURN_FROM_INS_CB(SET_3_H)
    case SET_3_L:
      PRINT_INS_CB(SET_3_L)
      set3(&cp.L);
      RETURN_FROM_INS_CB(SET_3_L)
    case SET_3_star_HL:
      PRINT_INS_CB(SET_3_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set3(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_3_star_HL)
    case SET_3_A:
      PRINT_INS_CB(SET_3_A)
      set3(&cp.A);
      RETURN_FROM_INS_CB(SET_3_A)
    case SET_4_B:
      PRINT_INS_CB(SET_4_B)
      set4(&cp.B);
      RETURN_FROM_INS_CB(SET_4_B)
    case SET_4_C:
      PRINT_INS_CB(SET_4_C)
      set4(&cp.C);
      RETURN_FROM_INS_CB(SET_4_C)
    case SET_4_D:
      PRINT_INS_CB(SET_4_D)
      set4(&cp.D);
      RETURN_FROM_INS_CB(SET_4_D)
    case SET_4_E:
      PRINT_INS_CB(SET_4_E)
      set4(&cp.E);
      RETURN_FROM_INS_CB(SET_4_E)
    case SET_4_H:
      PRINT_INS_CB(SET_4_H)
      set4(&cp.H);
      RETURN_FROM_INS_CB(SET_4_H)
    case SET_4_L:
      PRINT_INS_CB(SET_4_L)
      set4(&cp.L);
      RETURN_FROM_INS_CB(SET_4_L)
    case SET_4_star_HL:
      PRINT_INS_CB(SET_4_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set4(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_4_star_HL)
    case SET_4_A:
      PRINT_INS_CB(SET_4_A)
      set4(&cp.A);
      RETURN_FROM_INS_CB(SET_4_A)
    case SET_5_B:
      PRINT_INS_CB(SET_5_B)
      set5(&cp.B);
      RETURN_FROM_INS_CB(SET_5_B)
    case SET_5_C:
      PRINT_INS_CB(SET_5_C)
      set5(&cp.C);
      RETURN_FROM_INS_CB(SET_5_C)
    case SET_5_D:
      PRINT_INS_CB(SET_5_D)
      set5(&cp.D);
      RETURN_FROM_INS_CB(SET_5_D)
    case SET_5_E:
      PRINT_INS_CB(SET_5_E)
      set5(&cp.E);
      RETURN_FROM_INS_CB(SET_5_E)
    case SET_5_H:
      PRINT_INS_CB(SET_5_H)
      set5(&cp.H);
      RETURN_FROM_INS_CB(SET_5_H)
    case SET_5_L:
      PRINT_INS_CB(SET_5_L)
      set5(&cp.L);
      RETURN_FROM_INS_CB(SET_5_L)
    case SET_5_star_HL:
      PRINT_INS_CB(SET_5_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set5(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_5_star_HL)
    case SET_5_A:
      PRINT_INS_CB(SET_5_A)
      set5(&cp.A);
      RETURN_FROM_INS_CB(SET_5_A)
    case SET_6_B:
      PRINT_INS_CB(SET_6_B)
      set6(&cp.B);
      RETURN_FROM_INS_CB(SET_6_B)
    case SET_6_C:
      PRINT_INS_CB(SET_6_C)
      set6(&cp.C);
      RETURN_FROM_INS_CB(SET_6_C)
    case SET_6_D:
      PRINT_INS_CB(SET_6_D)
      set6(&cp.D);
      RETURN_FROM_INS_CB(SET_6_D)
    case SET_6_E:
      PRINT_INS_CB(SET_6_E)
      set6(&cp.E);
      RETURN_FROM_INS_CB(SET_6_E)
    case SET_6_H:
      PRINT_INS_CB(SET_6_H)
      set6(&cp.H);
      RETURN_FROM_INS_CB(SET_6_H)
    case SET_6_L:
      PRINT_INS_CB(SET_6_L)
      set6(&cp.L);
      RETURN_FROM_INS_CB(SET_6_L)
    case SET_6_star_HL:
      PRINT_INS_CB(SET_6_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set6(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_6_star_HL)
    case SET_6_A:
      PRINT_INS_CB(SET_6_A)
      set6(&cp.A);
      RETURN_FROM_INS_CB(SET_6_A)
    case SET_7_B:
      PRINT_INS_CB(SET_7_B)
      set7(&cp.B);
      RETURN_FROM_INS_CB(SET_7_B)
    case SET_7_C:
      PRINT_INS_CB(SET_7_C)
      set7(&cp.C);
      RETURN_FROM_INS_CB(SET_7_C)
    case SET_7_D:
      PRINT_INS_CB(SET_7_D)
      set7(&cp.D);
      RETURN_FROM_INS_CB(SET_7_D)
    case SET_7_E:
      PRINT_INS_CB(SET_7_E)
      set7(&cp.E);
      RETURN_FROM_INS_CB(SET_7_E)
    case SET_7_H:
      PRINT_INS_CB(SET_7_H)
      set7(&cp.H);
      RETURN_FROM_INS_CB(SET_7_H)
    case SET_7_L:
      PRINT_INS_CB(SET_7_L)
      set7(&cp.L);
      RETURN_FROM_INS_CB(SET_7_L)
    case SET_7_star_HL:
      PRINT_INS_CB(SET_7_star_HL)
      {
        uint8_t dummy;
        ldOp8FromMem(cp.HL, &dummy);
        set7(&dummy);
	ldOp8ToMem(dummy, cp.HL);
      }
      RETURN_FROM_INS_CB(SET_7_star_HL)
    case SET_7_A:
      PRINT_INS_CB(SET_7_A)
      set7(&cp.A);
      RETURN_FROM_INS_CB(SET_7_A)

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

void sla(uint8_t *op)
{
  cp.n = cp.h = 0;
  uint8_t save = *op;
  *op <<= 1;
  cp.cf = (save & 0x80) == 0x80;
  *op = *op & 0xFE; 
  cp.zf = *op == 0;
}

void sra(uint8_t *op)
{
  cp.n = cp.h = 0;
  uint8_t save = *op;
  *op >>= 1;
  *op = *op | (save & 0x80);
  cp.cf = ((save & 0x01) == 1);
  cp.zf = *op == 0;
}

void swap(uint8_t *op)
{
  cp.n = cp.h = cp.cf = 0;
  uint8_t temp;
  temp = ((*op & 0xF0) >> 4) | ((*op & 0x0F) << 4);
  *op = temp;
  cp.zf = *op == 0;
}

void srl(uint8_t *op)
{
  cp.n = cp.h = 0;
  uint8_t save = *op;
  *op >>= 1;
  cp.cf = ((save & 0x01) == 1);
  *op = (*op & 0x7F);
  cp.zf = *op == 0;
}

void bit(uint8_t *op, uint8_t bit)
{
  cp.n = 0;
  cp.h = 1;
  uint8_t flag;
  flag = (*op & (1<<bit)) >> bit;
  cp.zf = ~flag;
}

void res(uint8_t *op, uint8_t bit)
{
  uint8_t mask;
  mask = ~(1<<bit);
  *op &= mask;
}

void set(uint8_t *op, uint8_t bit)
{
  uint8_t mask;
  mask = 1<<bit;
  *op |= mask;
}

void checkInterrupt()
{
  //do not trigger int if IME is disabled or cpu not halted
  if(!cp.interrupts_master_enabled && !cp.halted)
    return;
  
  //read Interrupt enable register
  uint8_t ie_reg;
  ldOp8FromMem(IE, &ie_reg);

  //read Interrupt flag register
  uint8_t if_reg;
  ldOp8FromMem(IF, &if_reg);

  //check if interrupt is enabled and triggered
  for(uint8_t num = 1; num*=2; num <= 8)
  {
    if(!(num & ie_reg & if_reg))
      continue;

    if(cp.halted)
    {
      cp.halted = 0;
      return;
    }

    cp.interrupts_master_enabled = 0;
    push16(cp.PC);

    //clear int flag
    if_reg = if_reg & ~num;
    ldOp8ToMem(if_reg, IF);

    if(num & INT_VBLANK)
      cp.PC = 0x40;

    if(num & INT_LCD)
      cp.PC = 0x48;

    if(num & INT_TMR)
      cp.PC = 0x50;

    if(num & INT_JOYPAD)
      cp.PC = 0x60;
  }
}
