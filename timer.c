#include "timer.h"
#include "mmu.h"

uint16_t input_clock_select[4] = {1024, 16, 64, 256};

void timerInit(uint8_t *mem)
{
  divider = &mem[DIV];
  tima = &mem[TIMA];
  tma = &mem[TMA];
  tac = &mem[TAC];
  timaInterval = 1024;
  divInterval = 256;
}

void timerProcess(uint32_t cycles_passed)
{
  if(!cycles_passed)
    return;

  //increment div reg
  updateDiv(cycles_passed);

  //check if clk is enabled
  if(!clkEnabled())
    return;

  //check enough cycles have passed and increment tima value
  timaInterval -= cycles_passed;
  if(timaInterval > 0)
    return;

  setClk();
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

void updateDiv(uint32_t cycles_passed)
{
  //encrement with 16382Hz which is CPU_CLK/16382 = 256
  divInterval -= cycles_passed;
  if(divInterval <= 0)
  {
    (*divider)++;
    divInterval = 256;
  }
}

void setClk()
{
  uint8_t timerBits;
  timerBits = (*tac & 0x3);
  timaInterval =  input_clock_select[timerBits];
}
