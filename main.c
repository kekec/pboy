#include <stdio.h>
#include "cpu.h"
#include "tester.h"

void test_regs()
{
  struct cpu rf;
  rf.A = 0xAA;
  rf.B = 0xBB;
  rf.C = 0xCC;
  rf.DE = 0x1234;
  rf.H = 0x50;
  rf.L = 0x11;
  rf.F = 0xFF;
 
  printf("size of regs %ld\n", sizeof(rf));
  printf("B : %x C : %x BC : %x\n", rf.B, rf.C, rf.BC);
  printf("D : %x E : %x DE : %x\n", rf.D, rf.E, rf.DE);
  printf("H : %x L :  %x HL : %x\n", rf.H, rf.L, rf.HL);
  printf("A : %x AF : %x F: %x\n", rf.A, rf.AF, rf.F);

  rf.F = 0xFF;
  printf("flag is %x\n", rf.F);
  rf.F = 0x00;
  printf("flag is %x\n", rf.F);
  rf.zf = 1;
  printf("flag is %x\n", rf.F);
}

void main()
{
  test_regs();
  init();

  for(int i=0; i<10; i++)
    step();
}
