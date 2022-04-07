#include "stdint.h"

uint8_t *tima;
uint8_t *tma;
uint8_t *tac;

void timerInit();
void timerProcess(uint32_t cycles);
uint8_t clkEnabled();
uint16_t getClkPrescaler();
