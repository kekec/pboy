#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"

#define PRINT_INS_FOO(arg) print_ins(arg);
#define PRINT_INS(arg) PRINT_INS_FOO(arg)
#define RETURN_FROM_INS(arg) move_pc(arg); return instructions[arg].cycles_min;
#define PRINT_INS_CB(arg)
#define RETURN_FROM_INS_CB(arg) move_pc_cb(arg); return instructionsCB[arg].cycles_min;

#define bit0(arg) bit(arg, 0)
#define bit1(arg) bit(arg, 1)
#define bit2(arg) bit(arg, 2)
#define bit3(arg) bit(arg, 3)
#define bit4(arg) bit(arg, 4)
#define bit5(arg) bit(arg, 5)
#define bit6(arg) bit(arg, 6)
#define bit7(arg) bit(arg, 7)

#define res0(arg) res(arg, 0)
#define res1(arg) res(arg, 1)
#define res2(arg) res(arg, 2)
#define res3(arg) res(arg, 3)
#define res4(arg) res(arg, 4)
#define res5(arg) res(arg, 5)
#define res6(arg) res(arg, 6)
#define res7(arg) res(arg, 7)

#define set0(arg) set(arg, 0)
#define set1(arg) set(arg, 1)
#define set2(arg) set(arg, 2)
#define set3(arg) set(arg, 3)
#define set4(arg) set(arg, 4)
#define set5(arg) set(arg, 5)
#define set6(arg) set(arg, 6)
#define set7(arg) set(arg, 7)

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
          uint8_t cf: 1;
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
uint8_t decodeCB();
uint8_t readMem(uint16_t addr);
void writeMem(uint16_t addr, uint8_t data);
void registerLogWriteMem(void (*func)(uint16_t, uint8_t));
void registerLogReadMem(uint8_t (*func)(uint16_t));

static inline void move_pc(uint8_t opcode);
static inline void print_ins(uint8_t opcode);

static inline void move_pc_cb(uint8_t opcode);
static inline void move_ins_cb(uint8_t opcode);

void ldOp8ToMem(uint8_t data, uint16_t dest);
void ldOp8FromMemAtPC(uint8_t *out);
void ldOp8FromMem(uint16_t src, uint8_t *dest);
void ldOp16FromMem(uint16_t src, uint16_t *dest);
void ldOp16FromMemAtPC(uint16_t *out);
void ldOp16FromMemAtSP(uint16_t *out);

void inc8(uint8_t *data);
void dec8(uint8_t *data);
void add8(uint8_t *op1, uint8_t *op2);
void adc8(uint8_t *op1, uint8_t *op2);
void sub8(uint8_t *op);
void sbc8(uint8_t *op);
void and8(uint8_t *op);
void xor8(uint8_t *op);
void or8(uint8_t *op);
void cp8(uint8_t *op);

void add16(uint16_t *op1, uint16_t *op2);
void incMem(uint16_t memAddr);
void decMem(uint16_t memAddr);

void rlcOp8(uint8_t *data);
void rlOp8(uint8_t *data);

void rrcOp8(uint8_t *data);
void rrOp8(uint8_t *data);

void daa();

void pop16(uint16_t *out);
void pop16AF();
void push16(uint16_t in);

void rst(uint8_t opcode);

void rlc(uint8_t *op);
void rrc(uint8_t *op);
void rl(uint8_t *op);
void rr(uint8_t *op);
void sla(uint8_t *op);
void sra(uint8_t *op);
void swap(uint8_t *op);
void srl(uint8_t *op);
void bit(uint8_t *op, uint8_t bit);
void res(uint8_t *op, uint8_t bit);
void set(uint8_t *op, uint8_t bit);
