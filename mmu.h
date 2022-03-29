#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define SB 0xFF01
#define SC 0xFF02
#define IF 0xFF0F
#define IE 0xFFFF

static uint8_t *mem = NULL;
static uint8_t highmem[256];
static uint8_t iram[2*256];

uint8_t (*logReadMem)(uint16_t);
void (*logWriteMem)(uint16_t, uint8_t);

void mmuInit(uint8_t *address);
uint8_t mmuReadMem(uint16_t address);
void mmuWriteMem(uint16_t address, uint8_t data);

void mmuRegisterLogWriteMem(void (*func)(uint16_t, uint8_t));
void mmuRegisterLogReadMem(uint8_t (*func)(uint16_t));
