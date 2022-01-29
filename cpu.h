#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"

#define PRINT_INS(arg) print_ins(arg)
#define RETURN_FROM_INS(arg) do {move_pc(arg);break;} while(0)

struct cpu
{
  union 
  {
    struct
    {
      union //begin f
      {
        struct
        {
          uint8_t reserved : 4;
          uint8_t cy : 1;
          uint8_t h : 1;
          uint8_t n : 1;
          uint8_t zf : 1;
        };
        uint8_t F;
      }; //end f
      uint8_t A;
    };
    uint16_t AF;
  };

  union
  {
    struct
    {
       uint8_t C;
       uint8_t B;
    };
    uint16_t BC;
  };

  union
  {
    struct
    {
       uint8_t E;
       uint8_t D;
    };
    uint16_t DE;
  };

  union
  {
    struct
    {
       uint8_t L;
       uint8_t H;
    };
    uint16_t HL;
  };

  uint16_t SP;
  uint16_t PC;

  bool halted;
  bool interrupts_master_enabled;
};

uint8_t *mem;
struct cpu cp;
uint8_t (*logReadMem)(uint16_t);
void (*logWriteMem)(uint16_t, uint8_t);

void init(uint8_t *address);
unsigned int step();
uint8_t readMem(uint16_t addr);
void writeMem(uint16_t addr, uint8_t data);
void registerLogWriteMem(void (*func)(uint16_t, uint8_t));
void registerLogReadMem(uint8_t (*func)(uint16_t));
void ldToMem8(uint8_t data, uint16_t dest);
void ldFromMem8(uint16_t src, uint8_t *data);
void ldOp16FromMem(uint16_t src, uint16_t *dest);
static inline void move_pc(uint8_t opcode);
static inline void print_ins(uint8_t opcode);


