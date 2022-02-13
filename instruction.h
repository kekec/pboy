#include "stdint.h"

#define NOP 0x00
#define LD_BC_IMM16 0x01
#define LD_star_BC_A 0x02
#define INC_BC 0x03
#define INC_B 0x04
#define DEC_B 0x05
#define LD_B_IMM8 0x06
#define RLCA 0x07
#define LD_A16_SP 0x08
#define ADD_HL_BC 0x09
#define LD_A_star_BC 0x0A
#define DEC_BC 0x0B
#define INC_C 0x0C
#define DEC_C 0x0D
#define LD_C_IMM8 0x0E
#define RRCA 0x0F
#define STOP 0x10
#define LD_DE_IMM16 0x11
#define LD_star_DE_A 0x12
#define INC_DE 0x13
#define INC_D 0x14
#define DEC_D 0x15
#define LD_D_IMM8 0x16
#define RLA 0x17
#define JR_IMM8 0x18
#define ADD_HL_DE 0x19
#define LD_A_star_DE 0x1A
#define DEC_DE 0x1B
#define INC_E 0x1C
#define DEC_E 0x1D
#define LD_E_IMM8 0x1E
#define RRA 0x1F
#define JR_NZ_imm8 0x20
#define LD_HL_IMM16 0x21
#define LD_star_HL_plus_A 0x22
#define INC_HL 0x23
#define INC_H 0x24
#define DEC_H 0x25
#define LD_H_IMM8 0x26
#define DAA 0x27
#define JR_Z_IMM8 0x28
#define ADD_HL_HL 0x29
#define LD_A_star_HL_plus 0x2A
#define DEC_HL 0x2B
#define INC_L 0x2C
#define DEC_L 0x2D
#define LD_L_IMM8 0x2E
#define CPL 0x2F
#define JR_NC_IMM8 0x30
#define LD_SP_IMM16 0x31
#define LD_star_HL_minus_A 0x32
#define INC_SP 0x33
#define INC_star_HL 0x34
#define DEC_star_HL 0x35
#define LD_star_HL_IMM8 0x36
#define SCF 0x37
#define JR_C_IMM8 0x38
#define ADD_HL_SP 0x39
#define LD_A_star_HL_minus 0x3A
#define DEC_SP 0x3B
#define INC_A 0x3C
#define DEC_A 0x3D
#define LD_A_IMM8 0x3E
#define CCF 0x3F

#define LD_B_B 0x40
#define LD_B_C 0x41
#define LD_B_D 0x42
#define LD_B_E 0x43
#define LD_B_H 0x44
#define LD_B_L 0x45
#define LD_B_star_HL 0x46
#define LD_B_A 0x47

#define LD_C_B 0x48
#define LD_C_C 0x49
#define LD_C_D 0x4A
#define LD_C_E 0x4B 
#define LD_C_H 0x4C
#define LD_C_L 0x4D
#define LD_C_star_HL 0x4E
#define LD_C_A 0x4F

#define LD_D_B 0x50
#define LD_D_C 0x51
#define LD_D_D 0x52
#define LD_D_E 0x53
#define LD_D_H 0x54
#define LD_D_L 0x55
#define LD_D_star_HL 0x56
#define LD_D_A 0x57

#define LD_E_B 0x58
#define LD_E_C 0x59
#define LD_E_D 0x5A
#define LD_E_E 0x5B 
#define LD_E_H 0x5C
#define LD_E_L 0x5D
#define LD_E_star_HL 0x5E
#define LD_E_A 0x5F

#define LD_H_B 0x60
#define LD_H_C 0x61
#define LD_H_D 0x62
#define LD_H_E 0x63
#define LD_H_H 0x64
#define LD_H_L 0x65
#define LD_H_star_HL 0x66
#define LD_H_A 0x67

#define LD_L_B 0x68
#define LD_L_C 0x69
#define LD_L_D 0x6A
#define LD_L_E 0x6B 
#define LD_L_H 0x6C
#define LD_L_L 0x6D
#define LD_L_star_HL 0x6E
#define LD_L_A 0x6F

#define LD_star_HL_B 0x70
#define LD_star_HL_C 0x71
#define LD_star_HL_D 0x72
#define LD_star_HL_E 0x73
#define LD_star_HL_H 0x74
#define LD_star_HL_L 0x75
#define LD_star_HL_star_HL 0x76
#define LD_star_HL_A 0x77

#define LD_A_B 0x78
#define LD_A_C 0x79
#define LD_A_D 0x7A
#define LD_A_E 0x7B 
#define LD_A_H 0x7C
#define LD_A_L 0x7D
#define LD_A_star_HL 0x7E
#define LD_A_A 0x7F

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
  {"RLCA",1,4},          // 7
  {"LD (a16), SP",3,20}, // 8
  {"ADD HL,BC",1,8},     // 9
  {"LD A, (BC)",1,8},    // A
  {"DEC BC",1,8},        // B
  {"INC C",1,4},         // C
  {"DEC C",1,4},         // D
  {"LD C, imm8",2,8},    // E
  {"RRCA",1,4},          // F
  {"STOP",2,4},          //10
  {"LD DE, imm16",3,12}, //11
  {"LD (DE), A",1,8},    //12
  {"INC DE",1,8},        //13
  {"INC D",1,4},         //14
  {"DEC D",1,4},         //15
  {"LD D, imm8",2,8},    //16
  {"RLA",1,4},           //17
  {"JR imm8",2,12},      //18
  {"ADD HL,DE",1,8},     //19
  {"LD A, (DE)",1,8},    //1A
  {"DEC DE",1,8},        //1B
  {"INC E",1,4},         //1C
  {"DEC E",1,4},         //1D
  {"LD E, imm8",2,8},    //1E
  {"RRA",1,4},           //1F
  {"JR NZ, imm8",2,4},   //20 //4 or 8 cycles
  {"LD HL, imm16",3,12}, //21
  {"LD (HL+), A",1,8},   //22
  {"INC HL",1,8},        //23
  {"INC H",1,4},         //24
  {"DEC H",1,4},         //25
  {"LD H, imm8",2,8},    //26
  {"DAA",1,4},           //27
  {"JR Z, imm8",2,4},    //28 //4 or 8 cycles
  {"ADD HL,HL",1,8},     //29
  {"LD_A_star_DE",1,4},  //2A
  {"DEC HL",1,8},        //2B
  {"INC L",1,4},         //2C
  {"DEC L",1,4},         //2D
  {"LD L",2,8},          //2E
  {"CPL",1,4},           //2F
  {"JR NZ, imm8",2,4},   //30 //4 or 8 cycles
  {"LD SP, imm16",3,12}, //31
  {"LD (HL-), A",1,8},   //32
  {"INC SP",1,8},        //33
  {"INC (HL)",1,4},      //34
  {"DEC (HL)",1,4},      //35
  {"LD (HL), imm8",2,12},//36
  {"SCF",1,4},           //37
  {"JR C, imm8",2,4},    //38 //4 or 8 cylces
  {"ADD HL,SP",1,8},     //39
  {"LD A, (HL-)",1,8},   //3A
  {"DEC SP",1,8},        //3B
  {"INC A",1,4},         //3C
  {"DEC A",1,4},         //3D
  {"LD A, imm8",2,8},    //3E
  {"CCF",1,1},           //3F
  {"LD B, B", 1, 4},     //40
  {"LD B, C", 1, 4},     //41
  {"LD B, D", 1, 4},     //42
  {"LD B, E", 1, 4},     //43
  {"LD B, H", 1, 8},     //44
  {"LD B, L", 1, 4},     //45
  {"LD B, (HL)", 1, 4},  //46
  {"LD B, A", 1, 4},     //47
  {"LD C, B", 1, 4},     //48
  {"LD C, C", 1, 4},     //49
  {"LD C, D", 1, 4},     //4a
  {"LD C, E", 1, 4},     //4b
  {"LD C, H", 1, 4},     //4c
  {"LD C, L", 1, 4},     //4d
  {"LD C, (HL)", 1, 8},  //4e
  {"LD C, A", 1, 4},     //4f
  {"LD D, B", 1, 4},     //50
  {"LD D, C", 1, 4},     //51
  {"LD D, D", 1, 4},     //52
  {"LD D, E", 1, 4},     //53
  {"LD D, H", 1, 4},     //54
  {"LD D, L", 1, 4},     //55
  {"LD D, (HL)", 1, 8},  //56
  {"LD D, A", 1, 4},     //57
  {"LD E, B", 1, 4},     //58
  {"LD E, C", 1, 4},     //59
  {"LD E, D", 1, 4},     //5a
  {"LD E, E", 1, 4},     //5b
  {"LD E, H", 1, 4},     //5c
  {"LD E, L", 1, 4},     //5d
  {"LD E, (HL)", 1, 8},  //5e
  {"LD E, A", 1, 4},     //5f
  {"LD H, B", 1, 4},     //60
  {"LD H, C", 1, 4},     //61
  {"LD H, D", 1, 4},     //62
  {"LD H, E", 1, 4},     //63
  {"LD H, H", 1, 4},     //64
  {"LD H, L", 1, 4},     //65
  {"LD H, (HL)", 1, 8},  //66
  {"LD H, A", 1, 4},     //67
  {"LD L, B", 1, 4},     //68
  {"LD L, C", 1, 4},     //69
  {"LD L, D", 1, 4},     //6a
  {"LD L, E", 1, 4},     //6b
  {"LD L, H", 1, 4},     //6c
  {"LD L, L", 1, 4},     //6d
  {"LD L, (HL)", 1, 8},  //6e
  {"LD L, A", 1, 4},     //6f
  {"LD H, B", 1, 4},     //70
  {"LD H, C", 1, 4},     //71
  {"LD H, D", 1, 4},     //72
  {"LD H, E", 1, 4},     //73
  {"LD H, H", 1, 4},     //74
  {"LD H, L", 1, 4},     //75
  {"LD H, (HL)", 1, 8},  //76
  {"LD H, A", 1, 4},     //77
  {"LD A, B", 1, 4},     //78
  {"LD A, C", 1, 4},     //79
  {"LD A, D", 1, 4},     //7a
  {"LD A, E", 1, 4},     //7b
  {"LD A, H", 1, 4},     //7c
  {"LD A, L", 1, 4},     //7d
  {"LD A, (HL)", 1, 8},  //7e
  {"LD A, A", 1, 4},     //7f
};
