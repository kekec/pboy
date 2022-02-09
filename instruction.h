#include "stdint.h"

#define NOP 0x00
#define LD_BC_IMM16 0x01
#define LD_star_BC_A 0x02
#define INC_BC 0x03
#define INC_B 0x04
#define DEC_B 0x05
#define LD_B_IMM8 0x06
#define INC_C 0x0C
#define DEC_C 0x0D
#define LD_C_IMM8 0x0E
#define INC_D 0x14
#define DEC_D 0x15
#define LD_D_IMM8 0x16
#define INC_E 0x1C
#define DEC_E 0x1D
#define INC_L 0x24
#define DEC_L 0x25
#define INC_H 0x2C
#define DEC_H 0x2D
#define INC_star_HL 0x34
#define DEC_star_HL 0x35
#define INC_A 0x3C
#define DEC_A 0x3D

struct instruction
{
  char * string;
  uint8_t len;
  uint8_t cycles;
};

static struct instruction instructions[] =
{ {"NOP",1,4},           // 0
  {"LD BC, imm16",3,12}, // 1
  {"LD (BC), A",1,8},    // 2
  {"INC BC",1,8},        // 3
  {"INC B",1,4},         // 4
  {"DEC B",1,4},         // 5
  {"LD B, imm8",2,8},    // 6
  {"dummy B",1,4},       // 7
  {"dummy B",1,4},       // 8
  {"dummy B",1,4},       // 9
  {"dummy B",1,4},       // A
  {"dummy B",1,4},       // B
  {"INC C",1,4},         // C
  {"DEC C",1,4},         // D
  {"LD C, imm8",2,8},    // E
  {"dummy B",1,4},       // F
  {"dummy B",1,4},       //10
  {"dummy B",1,4},       //11
  {"dummy B",1,4},       //12
  {"dummy B",1,4},       //13
  {"INC D",1,4},         //14
  {"DEC D",1,4},         //15
  {"LD D, imm8",2,8},    //16
  {"dummy B",1,4},       //17
  {"dummy B",1,4},       //18
  {"dummy B",1,4},       //19
  {"dummy B",1,4},       //1A
  {"dummy B",1,4},       //1B
  {"INC E",1,4},         //1C
  {"DEC E",1,4},         //1D
  {"dummy B",1,4},       //1E
  {"dummy B",1,4},       //1F
  {"dummy B",1,4},       //20
  {"dummy B",1,4},       //21
  {"dummy B",1,4},       //22
  {"dummy B",1,4},       //23
  {"INC H",1,4},         //24
  {"DEC H",1,4},         //25
  {"dummy B",1,4},       //26
  {"dummy B",1,4},       //27
  {"dummy B",1,4},       //28
  {"dummy B",1,4},       //29
  {"dummy B",1,4},       //2A
  {"dummy B",1,4},       //2B
  {"INC L",1,4},         //2C
  {"DEC L",1,4},         //2D
  {"dummy B",1,4},       //2E
  {"dummy B",1,4},       //2F
  {"dummy B",1,4},       //30
  {"dummy B",1,4},       //31
  {"dummy B",1,4},       //32
  {"dummy B",1,4},       //33
  {"INC (HL)",1,4},      //34
  {"DEC (HL)",1,4},      //35
  {"dummy B",1,4},       //36
  {"dummy B",1,4},       //37
  {"dummy B",1,4},       //38
  {"dummy B",1,4},       //39
  {"dummy B",1,4},       //3A
  {"dummy B",1,4},       //3B
  {"INC A",1,4},         //3C
  {"DEC A",1,4},         //3D
};
