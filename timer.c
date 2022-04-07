#include "timer.h"
#include "mmu.h"

uint16_t input_clock_select[4] = {1024, 16, 64, 256};

void timerInit()
{
  tima = &mem[TIMA];
  tma = &mem[TMA];
  tac = &mem[TAC];
  //*tima = 0;
  //*tma = 0;
  //*tac = 0;
}

void timerProcess(uint32_t cycles)
{

  //increment div reg

  //check if clk is enabled
  if(!clkEnabled())
    return;

  if(!cycles)
    return;

  //get current clk prescaler
  //depending on the number of cycles increment timer value
  uint16_t div = getClkPrescaler();
  if( ((cycles & 0xF) == 0xF))
    return;

  if(*tima == 0xFF)
  {
    //trigger timer interrupt
    setInterruptFlag(INT_TMR);
    //reload timer with tma value
    *tima = *tma;
    return;
  }
  (*tima)++;
}

uint8_t clkEnabled()
{
  return ((*tac & TIMER_ENABLE_BIT) == TIMER_ENABLE_BIT);
}

uint16_t getClkPrescaler()
{
  uint8_t timerBits;
  timerBits = (*tac & 0x3);
  return input_clock_select[timerBits];
}
