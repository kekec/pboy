#include "mmu.h"

void mmuInit(uint8_t *address)
{
  if(address == NULL)
    printf("Ouch\n");
  mem=address;
}

uint8_t mmuReadMem(uint16_t address)
{
  if(mem == NULL)
    printf("Ouch\n");

  return mem[address];
}

void mmuWriteMem(uint8_t data, uint16_t address)
{
  if(mem == NULL)
    printf("Ouch\n");

  mem[address] = data;
}
