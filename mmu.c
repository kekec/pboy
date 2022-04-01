#include "mmu.h"
#include "cpu.h"
#include "stdlib.h"

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

  if( logReadMem != NULL )
    return (*logReadMem)(addr);

//  if((addr & 0xFF00) == 0xFF00)
//  {
//    if(addr == SC)
//      printf("Read SC %X\n", highmem[addr & 0xFF]);
//    return highmem[addr & 0xFF];
//  }
//
//  if((addr >= 0xC000) && (addr <= 0xDFFF))
//    return iram[addr & 0x1FF];
//
//  printf("Read SC %X\n", highmem[addr & 0xFF]);
  return mem[addr];

}

void mmuWriteMem(uint16_t addr, uint8_t data)
{
  if(mem == NULL)
    printf("Ouch\n");

  if( logWriteMem != NULL )
  {
    (*logWriteMem)(addr, data);
    return;
  }

  mem[addr] = data;
  if((addr == SC) && (data == 0x81))
  {
    char c = mem[SB];
    printf("%c", c);
    mem[SC] = 0;
  }

}

void mmuRegisterLogWriteMem(void (*func)(uint16_t, uint8_t))
{
  logWriteMem = func;
}

void mmuRegisterLogReadMem(uint8_t (*func)(uint16_t))
{
  logReadMem = func;
}

