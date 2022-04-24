#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define SB 0xFF01
#define SC 0xFF02

#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07
#define TIMER_ENABLE_BIT 4

#define IF 0xFF0F
#define IE 0xFFFF

#define INT_VBLANK 1
#define INT_LCD 2
#define INT_TMR 4
#define INT_JOYPAD 8

#define CPU_CLK 4194304

extern uint8_t *mem;

uint8_t (*logReadMem)(uint16_t);
void (*logWriteMem)(uint16_t, uint8_t);

void mmuInit(uint8_t *address);
uint8_t mmuReadMem(uint16_t address);
void mmuWriteMem(uint16_t address, uint8_t data);

void mmuRegisterLogWriteMem(void (*func)(uint16_t, uint8_t));
void mmuRegisterLogReadMem(uint8_t (*func)(uint16_t));

void setInterruptFlag(uint8_t num);
uint8_t getInterruptFlag(uint8_t num);

