#include "mmu.h"

void mmuInit(uint8_t *address)
{
  if(address == NULL)
    printf("Ouch\n");
  mem=address;
  logReadMem = NULL;
  logWriteMem = NULL;
}

uint8_t mmuReadMem(uint16_t addr)
{
  if(mem == NULL)
    printf("Ouch\n");

  if(addr == 0xFF01 || addr == 0xFF02)
    printf("serial link read\n");
 
  if( logReadMem != NULL )
    return (*logReadMem)(addr);

  return mem[addr];
}

void mmuWriteMem(uint16_t addr, uint8_t data)
{
  if(mem == NULL)
    printf("Ouch\n");

  if(addr == 0xFF01 || addr == 0xFF02)
    printf("serial link write\n");

  if( logWriteMem != NULL )
  {
    (*logWriteMem)(addr, data);
    return;
  }

  mem[addr] = data;
}

void mmuRegisterLogWriteMem(void (*func)(uint16_t, uint8_t))
{
  logWriteMem = func;
}

void mmuRegisterLogReadMem(uint8_t (*func)(uint16_t))
{
  logReadMem = func;
}

