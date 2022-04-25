#include "stdint.h"

uint8_t *divider;
uint8_t *tima;
uint8_t *tma;
uint8_t *tac;

int32_t timaInterval;
int32_t divInterval;

void timerInit(uint8_t *mem);
void timerProcess(uint32_t cycles);
uint8_t clkEnabled();
uint16_t getClkPrescaler();
void updateDiv(uint32_t cycles);
void setClk();
