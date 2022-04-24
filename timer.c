#include "timer.h"
#include "mmu.h"

uint16_t input_clock_select[4] = {1024, 16, 64, 256};

void timerInit()
{
  divider = &mem[DIV];
  tima = &mem[TIMA];
  tma = &mem[TMA];
  tac = &mem[TAC];
}

void timerProcess(uint32_t cycles)
{
  if(!cycles)
    return;

  //increment div reg
  updateDiv(cycles);

  //check if clk is enabled
  if(!clkEnabled())
    return;

  //check enough cycles have passed and increment tima value
  //TODO: check if counterInterval is reached and timer needs to be clocked

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

void updateDiv(uint32_t cycles)
{
  //encrement with 16382Hz which is CPU_CLK/16382 = 256
  if((cycles % 256) == 0)
  {
    (*divider)++;
  }
}

void updateClk()
{
  uint8_t timerBits;
  timerBits = (*tac & 0x3);
  currentTimerInterval =  input_clock_select[timerBits];
}
