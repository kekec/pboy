#include <stdio.h>
#include "cpu.h"

void test()
{
  struct cpu rf;
  rf.A = 0x55;
  rf.B = 0xF0;
  rf.DE = 0x1234;
  rf.H = 0x50;
  rf.L = 0x11;
 
  printf("size of regs %ld\n", sizeof(rf));
  printf("B : %x C : %x, BC : %x\n", rf.B, rf.C, rf.BC);
  printf("D : %x E : %x, DE : %x\n", rf.D, rf.E, rf.DE);
  printf("H : %x L : %x, HL : %x\n", rf.H, rf.L, rf.HL);
  printf("Hello World\n");
}

void main()
{
  test();
}
