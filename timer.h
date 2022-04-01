#include "stdint.h"

#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07

struct tmc_def
{
  uint8_t ics : 2; //input clock select
  uint8_t te : 1; //timer enable
  uint8_t reserved : 5;
};

uint8_t *tima;
uint8_t *tma;
struct tmc_def *tmc;

void timerInit(uint8_t *mem);
void timerProcess(uint32_t cycles);
