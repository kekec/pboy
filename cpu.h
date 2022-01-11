#include <stdint.h>

union flags
{
  struct
  {
    uint8_t np;
  };
  uint8_t F;
};

struct cpu
{
  union 
  {
    struct
    {
      uint8_t A;
      union flags F;
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
};

//struct cpu{
//  struct regs;
//};

//union
//{
//  struct
//  {
//    uint8_t A : 1;
//    uint8_t B : 1;
//    uint8_t C : 1;
//    uint8_t D : 1;
//    uint8_t E : 1;
//    uint8_t F : 1;
//  } f;
//  uint8_t flags;
//} flags;
