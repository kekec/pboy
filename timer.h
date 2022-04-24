#include "stdint.h"

uint8_t *divider;
uint8_t *tima;
uint8_t *tma;
uint8_t *tac;

uint32_t currentTimerInterval;

void timerInit();
void timerProcess(uint32_t cycles);
uint8_t clkEnabled();
uint16_t getClkPrescaler();
void updateDiv(uint32_t cycles);
void updateClk();
