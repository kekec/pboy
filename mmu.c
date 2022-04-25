#include "mmu.h"
#include "cpu.h"
#include "timer.h"
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

  uint8_t old_mem = mem[addr];
  mem[addr] = data;
  if((addr == SC) && (data == 0x81))
  {
    char c = mem[SB];
    printf("%c", c);
    mem[SC] = 0;
  }

  if(addr == DIV)
    mem[addr] = 0;

  if(addr != TAC)
    return;

  if(old_mem == data)
    return;

  //let the timer know that the clock changed
  //maybe shall use callback here?
  if((old_mem & 0x3) != (data & 0x03))
    setClk();
}

void mmuRegisterLogWriteMem(void (*func)(uint16_t, uint8_t))
{
  logWriteMem = func;
}

void mmuRegisterLogReadMem(uint8_t (*func)(uint16_t))
{
  logReadMem = func;
}

uint8_t getInterruptFlag(uint8_t num)
{
  return (mem[IF] & num) == num;
}
void setInterruptFlag(uint8_t num)
{

  mem[IF] |= num;
}
