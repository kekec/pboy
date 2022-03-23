#include <stdint.h>
#include <string.h>
#include <stdio.h>

static uint8_t *mem = NULL;

void mmuInit(uint8_t *address);
uint8_t mmuReadMem(uint16_t address);
void mmuWriteMem(uint8_t data, uint16_t address);
