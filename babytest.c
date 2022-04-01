#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include "cpu.h"

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

void main(uint8_t argc, char *argv[])
{
  FILE *fd;
  struct stat sb;
  uint8_t * buffer;
  uint32_t cycles;
  char c = 0;

  if (argc !=2 )
  {
    printf("Usage: %s romfile\n", argv[0]);
    exit(-1);
  }
  
  fd = fopen(argv[1], "rb");
  if (fd == NULL )
  {
    printf("Cannot open file %s\n", argv[1]);
    exit(-1);
  }

  //get file size
  stat(argv[1], &sb);
  buffer = (uint8_t*)malloc(65536);

  if(buffer == NULL)
  {
    printf("Memory could not be allocated\n");
    free(buffer);
    exit(-1);
  }

  fread(buffer, sb.st_size, 1, fd);

  cpuInit(buffer, 0x100);
  while(1)
  {
    cpuStep();
  }

  pclose(fd);
  free(buffer);
}
