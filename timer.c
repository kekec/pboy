#include "timer.h"

void timerInit(uint8_t *mem)
{
  return;
  tima = &mem[TIMA];
  tma = &mem[TMA];
  tmc = (struct tmc_def *)&mem[TAC];
}

void timerProcess(uint32_t cycles)
{
  return;
  //check if we need to increment the timer
  if( 0 )
    return;

  if(*tima == 0xFF)
  {  

    //reload timer with tma value
    *tima = *tma;
  }
  *tima++;
}
