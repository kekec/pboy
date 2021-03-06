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

#define ADD_A_B 0x80
#define ADD_A_C 0x81
#define ADD_A_D 0x82
#define ADD_A_E 0x83
#define ADD_A_H 0x84
#define ADD_A_L 0x85
#define ADD_A_star_HL 0x86
#define ADD_A_A 0x87

#define ADC_A_B 0x88
#define ADC_A_C 0x89
#define ADC_A_D 0x8A
#define ADC_A_E 0x8B
#define ADC_A_H 0x8C
#define ADC_A_L 0x8D
#define ADC_A_star_HL 0x8E
#define ADC_A_A 0x8F

#define SUB_B 0x90
#define SUB_C 0x91
#define SUB_D 0x92
#define SUB_E 0x93
#define SUB_H 0x94
#define SUB_L 0x95
#define SUB_star_HL 0x96
#define SUB_A 0x97

#define SBC_B 0x98
#define SBC_C 0x99
#define SBC_D 0x9A
#define SBC_E 0x9B
#define SBC_H 0x9C
#define SBC_L 0x9D
#define SBC_star_HL 0x9E
#define SBC_A 0x9F

#define AND_B 0xA0
#define AND_C 0xA1
#define AND_D 0xA2
#define AND_E 0xA3
#define AND_H 0xA4
#define AND_L 0xA5
#define AND_star_HL 0xA6
#define AND_A 0xA7

#define XOR_B 0xA8
#define XOR_C 0xA9
#define XOR_D 0xAA
#define XOR_E 0xAB
#define XOR_H 0xAC
#define XOR_L 0xAD
#define XOR_star_HL 0xAE
#define XOR_A 0xAF

#define OR_B 0xB0
#define OR_C 0xB1
#define OR_D 0xB2
#define OR_E 0xB3
#define OR_H 0xB4
#define OR_L 0xB5
#define OR_star_HL 0xB6
#define OR_A 0xB7

#define CP_B 0xB8
#define CP_C 0xB9
#define CP_D 0xBA
#define CP_E 0xBB
#define CP_H 0xBC
#define CP_L 0xBD
#define CP_star_HL 0xBE
#define CP_A 0xBF

#define RET_NZ 0xC0
#define POP_BC  0xC1
#define JP_NZ_IMM16 0xC2
#define JP_IMM16 0xC3
#define CALL_NZ_IMM16 0xC4
#define PUSH_BC 0xC5
#define ADD_A_IMM8 0xC6
#define RST_0 0xC7
#define RET_Z 0xC8
#define RET 0xC9
#define JP_Z_IMM16 0xCA
#define CB_INST 0xCB
#define CALL_Z_IMM16 0xCC
#define CALL_IMM16 0xCD
#define ADC_A_IMM8 0xCE
#define RST_1 0xCF

#define RET_NC 0xD0
#define POP_DE  0xD1
#define JP_NC_IMM16 0xD2
#define CALL_NC_IMM16 0xD4
#define PUSH_DE 0xD5
#define SUB_IMM8 0xD6
#define RST_2 0xD7
#define RET_C 0xD8
#define RETI 0xD9
#define JP_C_IMM16 0xDA
#define CALL_C_IMM16 0xDC
#define SBC_A_IMM8 0xDE
#define RST_3 0xDF

#define LD_star_IMM8_A 0xE0
#define POP_HL  0xE1
#define LD_star_C_A 0xE2
#define PUSH_HL 0xE5
#define AND_IMM8 0xE6
#define RST_4 0xE7
#define ADD_SP_IMM8 0xE8
#define JP_HL 0xE9
#define LD_star_IMM16_A 0xEA
#define XOR_IMM8 0xEE
#define RST_5 0xEF

#define LD_A_star_IMM8 0xF0
#define POP_AF  0xF1
#define LD_A_star_C 0xF2
#define DI 0xF3
#define PUSH_AF 0xF5
#define OR_IMM8 0xF6
#define RST_6 0xF7
#define LD_HL_SP_plus_IMM8 0xF8
#define LD_SP_HL 0xF9
#define LD_A_star_IMM16 0xFA
#define EI 0xFB
#define CP_IMM8 0xFE
#define RST_7 0xFF

#define RLC_B 0x00
#define RLC_C 0x01
#define RLC_D 0x02
#define RLC_E 0x03
#define RLC_H 0x04
#define RLC_L 0x05
#define RLC_star_HL 0x06
#define RLC_A 0x07
#define RRC_B 0x08
#define RRC_C 0x09
#define RRC_D 0x0A
#define RRC_E 0x0B
#define RRC_H 0x0C
#define RRC_L 0x0D
#define RRC_star_HL 0x0E
#define RRC_A 0x0F

#define RL_B 0x10
#define RL_C 0x11
#define RL_D 0x12
#define RL_E 0x13
#define RL_H 0x14
#define RL_L 0x15
#define RL_star_HL 0x16
#define RL_A 0x17
#define RR_B 0x18
#define RR_C 0x19
#define RR_D 0x1A
#define RR_E 0x1B
#define RR_H 0x1C
#define RR_L 0x1D
#define RR_star_HL 0x1E
#define RR_A 0x1F

#define SLA_B 0x20
#define SLA_C 0x21
#define SLA_D 0x22
#define SLA_E 0x23
#define SLA_H 0x24
#define SLA_L 0x25
#define SLA_star_HL 0x26
#define SLA_A 0x27
#define SRA_B 0x28
#define SRA_C 0x29
#define SRA_D 0x2A
#define SRA_E 0x2B
#define SRA_H 0x2C
#define SRA_L 0x2D
#define SRA_star_HL 0x2E
#define SRA_A 0x2F

#define SWAP_B 0x30
#define SWAP_C 0x31
#define SWAP_D 0x32
#define SWAP_E 0x33
#define SWAP_H 0x34
#define SWAP_L 0x35
#define SWAP_star_HL 0x36
#define SWAP_A 0x37
#define SRL_B 0x38
#define SRL_C 0x39
#define SRL_D 0x3A
#define SRL_E 0x3B
#define SRL_H 0x3C
#define SRL_L 0x3D
#define SRL_star_HL 0x3E
#define SRL_A 0x3F

#define BIT_0_B 0x40
#define BIT_0_C 0x41
#define BIT_0_D 0x42
#define BIT_0_E 0x43
#define BIT_0_H 0x44
#define BIT_0_L 0x45
#define BIT_0_star_HL 0x46
#define BIT_0_A 0x47
#define BIT_1_B 0x48
#define BIT_1_C 0x49
#define BIT_1_D 0x4A
#define BIT_1_E 0x4B
#define BIT_1_H 0x4C
#define BIT_1_L 0x4D
#define BIT_1_star_HL 0x4E
#define BIT_1_A 0x4F

#define BIT_2_B 0x50
#define BIT_2_C 0x51
#define BIT_2_D 0x52
#define BIT_2_E 0x53
#define BIT_2_H 0x54
#define BIT_2_L 0x55
#define BIT_2_star_HL 0x56
#define BIT_2_A 0x57
#define BIT_3_B 0x58
#define BIT_3_C 0x59
#define BIT_3_D 0x5A
#define BIT_3_E 0x5B
#define BIT_3_H 0x5C
#define BIT_3_L 0x5D
#define BIT_3_star_HL 0x5E
#define BIT_3_A 0x5F

#define BIT_4_B 0x60
#define BIT_4_C 0x61
#define BIT_4_D 0x62
#define BIT_4_E 0x63
#define BIT_4_H 0x64
#define BIT_4_L 0x65
#define BIT_4_star_HL 0x66
#define BIT_4_A 0x67
#define BIT_5_B 0x68
#define BIT_5_C 0x69
#define BIT_5_D 0x6A
#define BIT_5_E 0x6B
#define BIT_5_H 0x6C
#define BIT_5_L 0x6D
#define BIT_5_star_HL 0x6E
#define BIT_5_A 0x6F

#define BIT_6_B 0x70
#define BIT_6_C 0x71
#define BIT_6_D 0x72
#define BIT_6_E 0x73
#define BIT_6_H 0x74
#define BIT_6_L 0x75
#define BIT_6_star_HL 0x76
#define BIT_6_A 0x77
#define BIT_7_B 0x78
#define BIT_7_C 0x79
#define BIT_7_D 0x7A
#define BIT_7_E 0x7B
#define BIT_7_H 0x7C
#define BIT_7_L 0x7D
#define BIT_7_star_HL 0x7E
#define BIT_7_A 0x7F

#define RES_0_B 0x80
#define RES_0_C 0x81
#define RES_0_D 0x82
#define RES_0_E 0x83
#define RES_0_H 0x84
#define RES_0_L 0x85
#define RES_0_star_HL 0x86
#define RES_0_A 0x87
#define RES_1_B 0x88
#define RES_1_C 0x89
#define RES_1_D 0x8A
#define RES_1_E 0x8B
#define RES_1_H 0x8C
#define RES_1_L 0x8D
#define RES_1_star_HL 0x8E
#define RES_1_A 0x8F

#define RES_2_B 0x90
#define RES_2_C 0x91
#define RES_2_D 0x92
#define RES_2_E 0x93
#define RES_2_H 0x94
#define RES_2_L 0x95
#define RES_2_star_HL 0x96
#define RES_2_A 0x97
#define RES_3_B 0x98
#define RES_3_C 0x99
#define RES_3_D 0x9A
#define RES_3_E 0x9B
#define RES_3_H 0x9C
#define RES_3_L 0x9D
#define RES_3_star_HL 0x9E
#define RES_3_A 0x9F

#define RES_4_B 0xA0
#define RES_4_C 0xA1
#define RES_4_D 0xA2
#define RES_4_E 0xA3
#define RES_4_H 0xA4
#define RES_4_L 0xA5
#define RES_4_star_HL 0xA6
#define RES_4_A 0xA7
#define RES_5_B 0xA8
#define RES_5_C 0xA9
#define RES_5_D 0xAA
#define RES_5_E 0xAB
#define RES_5_H 0xAC
#define RES_5_L 0xAD
#define RES_5_star_HL 0xAE
#define RES_5_A 0xAF

#define RES_6_B 0xB0
#define RES_6_C 0xB1
#define RES_6_D 0xB2
#define RES_6_E 0xB3
#define RES_6_H 0xB4
#define RES_6_L 0xB5
#define RES_6_star_HL 0xB6
#define RES_6_A 0xB7
#define RES_7_B 0xB8
#define RES_7_C 0xB9
#define RES_7_D 0xBA
#define RES_7_E 0xBB
#define RES_7_H 0xBC
#define RES_7_L 0xBD
#define RES_7_star_HL 0xBE
#define RES_7_A 0xBF

#define SET_0_B 0xC0
#define SET_0_C 0xC1
#define SET_0_D 0xC2
#define SET_0_E 0xC3
#define SET_0_H 0xC4
#define SET_0_L 0xC5
#define SET_0_star_HL 0xC6
#define SET_0_A 0xC7
#define SET_1_B 0xC8
#define SET_1_C 0xC9
#define SET_1_D 0xCA
#define SET_1_E 0xCB
#define SET_1_H 0xCC
#define SET_1_L 0xCD
#define SET_1_star_HL 0xCE
#define SET_1_A 0xCF

#define SET_2_B 0xD0
#define SET_2_C 0xD1
#define SET_2_D 0xD2
#define SET_2_E 0xD3
#define SET_2_H 0xD4
#define SET_2_L 0xD5
#define SET_2_star_HL 0xD6
#define SET_2_A 0xD7
#define SET_3_B 0xD8
#define SET_3_C 0xD9
#define SET_3_D 0xDA
#define SET_3_E 0xDB
#define SET_3_H 0xDC
#define SET_3_L 0xDD
#define SET_3_star_HL 0xDE
#define SET_3_A 0xDF

#define SET_4_B 0xE0
#define SET_4_C 0xE1
#define SET_4_D 0xE2
#define SET_4_E 0xE3
#define SET_4_H 0xE4
#define SET_4_L 0xE5
#define SET_4_star_HL 0xE6
#define SET_4_A 0xE7
#define SET_5_B 0xE8
#define SET_5_C 0xE9
#define SET_5_D 0xEA
#define SET_5_E 0xEB
#define SET_5_H 0xEC
#define SET_5_L 0xED
#define SET_5_star_HL 0xEE
#define SET_5_A 0xEF

#define SET_6_B 0xF0
#define SET_6_C 0xF1
#define SET_6_D 0xF2
#define SET_6_E 0xF3
#define SET_6_H 0xF4
#define SET_6_L 0xF5
#define SET_6_star_HL 0xF6
#define SET_6_A 0xF7
#define SET_7_B 0xF8
#define SET_7_C 0xF9
#define SET_7_D 0xFA
#define SET_7_E 0xFB
#define SET_7_H 0xFC
#define SET_7_L 0xFD
#define SET_7_star_HL 0xFE
#define SET_7_A 0xFF

struct instruction
{
  char * string;
  uint8_t len;
  uint8_t cycles_min;
  uint8_t cycles_max;
};

static struct instruction instructionsCB[] =
{ {"RLC B",2,8},           // 00
  {"RLC C",2,8},           // 01
  {"RLC D",2,8},           // 02
  {"RLC E",2,8},           // 03
  {"RLC H",2,8},           // 04
  {"RLC L",2,8},           // 05
  {"RLC (HL)",2,16},       // 06
  {"RLC A",2,8},           // 07
  {"RRC B",2,8},           // 08
  {"RRC C",2,8},           // 09
  {"RRC D",2,8},           // 0A
  {"RRC E",2,8},           // 0B
  {"RRC H",2,8},           // 0C
  {"RRC L",2,8},           // 0D
  {"RRC (HL)",2,16},       // 0E
  {"RRC A",2,8},           // 0F
  {"RL B",2,8},            // 10
  {"RL C",2,8},            // 11
  {"RL D",2,8},            // 12
  {"RL E",2,8},            // 13
  {"RL H",2,8},            // 14
  {"RL L",2,8},            // 15
  {"RL (HL)",2,16},        // 16
  {"RL A",2,8},            // 17
  {"RR B",2,8},            // 18
  {"RR C",2,8},            // 19
  {"RR D",2,8},            // 1A
  {"RR E",2,8},            // 1B
  {"RR H",2,8},            // 1C
  {"RR L",2,8},            // 1D
  {"RR (HL)",2,16},        // 1E
  {"RR A",2,8},            // 1F
  {"SLA B",2,8},           // 20
  {"SLA C",2,8},           // 21
  {"SLA D",2,8},           // 22
  {"SLA E",2,8},           // 23
  {"SLA H",2,8},           // 24
  {"SLA L",2,8},           // 25
  {"SLA (HL)",2,16},       // 26
  {"SLA A",2,8},           // 27
  {"SRA B",2,8},           // 28
  {"SRA C",2,8},           // 29
  {"SRA D",2,8},           // 2A
  {"SRA E",2,8},           // 2B
  {"SRA H",2,8},           // 2C
  {"SRA L",2,8},           // 2D
  {"SRA (HL)",2,16},       // 2E
  {"SRA A",2,8},           // 2F
  {"SWAP B",2,8},          // 30
  {"SWAP C",2,8},          // 31
  {"SWAP D",2,8},          // 32
  {"SWAP E",2,8},          // 33
  {"SWAP H",2,8},          // 34
  {"SWAP L",2,8},          // 35
  {"SWAP (HL)",2,16},      // 36
  {"SWAP A",2,8},          // 37
  {"SRL B",2,8},           // 38
  {"SRL C",2,8},           // 39
  {"SRL D",2,8},           // 3A
  {"SRL E",2,8},           // 3B
  {"SRL H",2,8},           // 3C
  {"SRL L",2,8},           // 3D
  {"SRL (HL)",2,16},       // 3E
  {"SRL A",2,8},           // 3F
  {"BIT 0, B",2,8},        // 40
  {"BIT 0, C",2,8},        // 41
  {"BIT 0, D",2,8},        // 42
  {"BIT 0, E",2,8},        // 43
  {"BIT 0, H",2,8},        // 44
  {"BIT 0, L",2,8},        // 45
  {"BIT 0, (HL)",2,16},    // 46
  {"BIT 0, A",2,8},        // 47
  {"BIT 1, B",2,8},        // 48
  {"BIT 1, C",2,8},        // 49
  {"BIT 1, D",2,8},        // 4A
  {"BIT 1, E",2,8},        // 4B
  {"BIT 1, H",2,8},        // 4C
  {"BIT 1, L",2,8},        // 4D
  {"BIT 1, (HL)",2,16},    // 4E
  {"BIT 1, A",2,8},        // 4F
  {"BIT 2, B",2,8},        // 50
  {"BIT 2, C",2,8},        // 51
  {"BIT 2, D",2,8},        // 52
  {"BIT 2, E",2,8},        // 53
  {"BIT 2, H",2,8},        // 54
  {"BIT 2, L",2,8},        // 55
  {"BIT 2, (HL)",2,16},    // 56
  {"BIT 2, A",2,8},        // 57
  {"BIT 3, B",2,8},        // 58
  {"BIT 3, C",2,8},        // 59
  {"BIT 3, D",2,8},        // 5A
  {"BIT 3, E",2,8},        // 5B
  {"BIT 3, H",2,8},        // 5C
  {"BIT 3, L",2,8},        // 5D
  {"BIT 3, (HL)",2,16},    // 5E
  {"BIT 3, A",2,8},        // 5F
  {"BIT 4, B",2,8},        // 60
  {"BIT 4, C",2,8},        // 61
  {"BIT 4, D",2,8},        // 62
  {"BIT 4, E",2,8},        // 63
  {"BIT 4, H",2,8},        // 64
  {"BIT 4, L",2,8},        // 65
  {"BIT 4, (HL)",2,16},    // 66
  {"BIT 4, A",2,8},        // 67
  {"BIT 5, B",2,8},        // 68
  {"BIT 5, C",2,8},        // 69
  {"BIT 5, D",2,8},        // 6A
  {"BIT 5, E",2,8},        // 6B
  {"BIT 5, H",2,8},        // 6C
  {"BIT 5, L",2,8},        // 6D
  {"BIT 5, (HL)",2,16},    // 6E
  {"BIT 5, A",2,8},        // 6F
  {"BIT 6, B",2,8},        // 70
  {"BIT 6, C",2,8},        // 71
  {"BIT 6, D",2,8},        // 72
  {"BIT 6, E",2,8},        // 73
  {"BIT 6, H",2,8},        // 74
  {"BIT 6, L",2,8},        // 75
  {"BIT 6, (HL)",2,16},    // 76
  {"BIT 6, A",2,8},        // 77
  {"BIT 7, B",2,8},        // 78
  {"BIT 7, C",2,8},        // 79
  {"BIT 7, D",2,8},        // 7A
  {"BIT 7, E",2,8},        // 7B
  {"BIT 7, H",2,8},        // 7C
  {"BIT 7, L",2,8},        // 7D
  {"BIT 7, (HL)",2,16},    // 7E
  {"BIT 7, A",2,8},        // 7F
  {"RES 0, B",2,8},        // 80
  {"RES 0, C",2,8},        // 81
  {"RES 0, D",2,8},        // 82
  {"RES 0, E",2,8},        // 83
  {"RES 0, H",2,8},        // 84
  {"RES 0, L",2,8},        // 85
  {"RES 0, (HL)",2,16},    // 86
  {"RES 0, A",2,8},        // 87
  {"RES 1, B",2,8},        // 88
  {"RES 1, C",2,8},        // 89
  {"RES 1, D",2,8},        // 8A
  {"RES 1, E",2,8},        // 8B
  {"RES 1, H",2,8},        // 8C
  {"RES 1, L",2,8},        // 8D
  {"RES 1, (HL)",2,16},    // 8E
  {"RES 1, A",2,8},        // 8F
  {"RES 2, B",2,8},        // 90
  {"RES 2, C",2,8},        // 91
  {"RES 2, D",2,8},        // 92
  {"RES 2, E",2,8},        // 93
  {"RES 2, H",2,8},        // 94
  {"RES 2, L",2,8},        // 95
  {"RES 2, (HL)",2,16},    // 96
  {"RES 2, A",2,8},        // 97
  {"RES 3, B",2,8},        // 98
  {"RES 3, C",2,8},        // 99
  {"RES 3, D",2,8},        // 9A
  {"RES 3, E",2,8},        // 9B
  {"RES 3, H",2,8},        // 9C
  {"RES 3, L",2,8},        // 9D
  {"RES 3, (HL)",2,16},    // 9E
  {"RES 3, A",2,8},        // 9F
  {"RES 4, B",2,8},        // A0
  {"RES 4, C",2,8},        // A1
  {"RES 4, D",2,8},        // A2
  {"RES 4, E",2,8},        // A3
  {"RES 4, H",2,8},        // A4
  {"RES 4, L",2,8},        // A5
  {"RES 4, (HL)",2,16},    // A6
  {"RES 4, A",2,8},        // A7
  {"RES 5, B",2,8},        // A8
  {"RES 5, C",2,8},        // A9
  {"RES 5, D",2,8},        // AA
  {"RES 5, E",2,8},        // AB
  {"RES 5, H",2,8},        // AC
  {"RES 5, L",2,8},        // AD
  {"RES 5, (HL)",2,16},    // AE
  {"RES 5, A",2,8},        // AF
  {"RES 6, B",2,8},        // B0
  {"RES 6, C",2,8},        // B1
  {"RES 6, D",2,8},        // B2
  {"RES 6, E",2,8},        // B3
  {"RES 6, H",2,8},        // B4
  {"RES 6, L",2,8},        // B5
  {"RES 6, (HL)",2,16},    // B6
  {"RES 6, A",2,8},        // B7
  {"RES 7, B",2,8},        // B8
  {"RES 7, C",2,8},        // B9
  {"RES 7, D",2,8},        // BA
  {"RES 7, E",2,8},        // BB
  {"RES 7, H",2,8},        // BC
  {"RES 7, L",2,8},        // BD
  {"RES 7, (HL)",2,16},    // BE
  {"RES 7, A",2,8},        // BF
  {"SET 0, B",2,8},        // C0
  {"SET 0, C",2,8},        // C1
  {"SET 0, D",2,8},        // C2
  {"SET 0, E",2,8},        // C3
  {"SET 0, H",2,8},        // C4
  {"SET 0, L",2,8},        // C5
  {"SET 0, (HL)",2,16},    // C6
  {"SET 0, A",2,8},        // C7
  {"SET 1, B",2,8},        // C8
  {"SET 1, C",2,8},        // C9
  {"SET 1, D",2,8},        // CA
  {"SET 1, E",2,8},        // CB
  {"SET 1, H",2,8},        // CC
  {"SET 1, L",2,8},        // CD
  {"SET 1, (HL)",2,16},    // CE
  {"SET 1, A",2,8},        // CF
  {"SET 2, B",2,8},        // D0
  {"SET 2, C",2,8},        // D1
  {"SET 2, D",2,8},        // D2
  {"SET 2, E",2,8},        // D3
  {"SET 2, H",2,8},        // D4
  {"SET 2, L",2,8},        // D5
  {"SET 2, (HL)",2,16},    // D6
  {"SET 2, A",2,8},        // D7
  {"SET 3, B",2,8},        // D8
  {"SET 3, C",2,8},        // D9
  {"SET 3, D",2,8},        // DA
  {"SET 3, E",2,8},        // DB
  {"SET 3, H",2,8},        // DC
  {"SET 3, L",2,8},        // DD
  {"SET 3, (HL)",2,16},    // DE
  {"SET 3, A",2,8},        // DF
  {"SET 4, B",2,8},        // E0
  {"SET 4, C",2,8},        // E1
  {"SET 4, D",2,8},        // E2
  {"SET 4, E",2,8},        // E3
  {"SET 4, H",2,8},        // E4
  {"SET 4, L",2,8},        // E5
  {"SET 4, (HL)",2,16},    // E6
  {"SET 4, A",2,8},        // E7
  {"SET 5, B",2,8},        // E8
  {"SET 5, C",2,8},        // E9
  {"SET 5, D",2,8},        // EA
  {"SET 5, E",2,8},        // EB
  {"SET 5, H",2,8},        // EC
  {"SET 5, L",2,8},        // ED
  {"SET 5, (HL)",2,16},    // EE
  {"SET 5, A",2,8},        // EF
  {"SET 6, B",2,8},        // F0
  {"SET 6, C",2,8},        // F1
  {"SET 6, D",2,8},        // F2
  {"SET 6, E",2,8},        // F3
  {"SET 6, H",2,8},        // F4
  {"SET 6, L",2,8},        // F5
  {"SET 6, (HL)",2,16},    // F6
  {"SET 6, A",2,8},        // F7
  {"SET 7, B",2,8},        // F8
  {"SET 7, C",2,8},        // F9
  {"SET 7, D",2,8},        // FA
  {"SET 7, E",2,8},        // FB
  {"SET 7, H",2,8},        // FC
  {"SET 7, L",2,8},        // FD
  {"SET 7, (HL)",2,16},    // FE
  {"SET 7, A",2,8},        // FF
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
  {"JR NZ, imm8",2,8,12},//20
  {"LD HL, imm16",3,12}, //21
  {"LD (HL+), A",1,8},   //22
  {"INC HL",1,8},        //23
  {"INC H",1,4},         //24
  {"DEC H",1,4},         //25
  {"LD H, imm8",2,8},    //26
  {"DAA",1,4},           //27
  {"JR Z, imm8",2,8,12}, //28
  {"ADD HL,HL",1,8},     //29
  {"LD_A_star_DE",1,4},  //2A
  {"DEC HL",1,8},        //2B
  {"INC L",1,4},         //2C
  {"DEC L",1,4},         //2D
  {"LD L",2,8},          //2E
  {"CPL",1,4},           //2F
  {"JR NZ, imm8",2,8,12},//30
  {"LD SP, imm16",3,12}, //31
  {"LD (HL-), A",1,8},   //32
  {"INC SP",1,8},        //33
  {"INC (HL)",1,4},      //34
  {"DEC (HL)",1,4},      //35
  {"LD (HL), imm8",2,12},//36
  {"SCF",1,4},           //37
  {"JR C, imm8",2,8,12}, //38
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
  {"ADD A, B", 1, 4},    //80
  {"ADD A, C", 1, 4},    //81
  {"ADD A, D", 1, 4},    //82
  {"ADD A, E", 1, 4},    //83
  {"ADD A, H", 1, 4},    //84
  {"ADD A, L", 1, 4},    //85
  {"ADD A, (HL)", 1, 8}, //86
  {"ADD A, A", 1, 4},    //87
  {"ADC A, B", 1, 4},    //88
  {"ADC A, C", 1, 4},    //89
  {"ADC A, D", 1, 4},    //8A
  {"ADC A, E", 1, 4},    //8B
  {"ADC A, H", 1, 4},    //8C
  {"ADC A, L", 1, 4},    //8D
  {"ADC A, (HL)", 1, 8}, //8E
  {"ADC A, A", 1, 4},    //8F
  {"SUB B", 1, 4},       //90
  {"SUB C", 1, 4},       //91
  {"SUB D", 1, 4},       //92
  {"SUB E", 1, 4},       //93
  {"SUB H", 1, 4},       //94
  {"SUB L", 1, 4},       //95
  {"SUB (HL)", 1, 8},    //96
  {"SUB A", 1, 4},       //97
  {"SBC B", 1, 4},       //98
  {"SBC C", 1, 4},       //99
  {"SBC D", 1, 4},       //9A
  {"SBC E", 1, 4},       //9B
  {"SBC H", 1, 4},       //9C
  {"SBC L", 1, 4},       //9D
  {"SBC (HL)", 1, 8},    //9E
  {"SBC A", 1, 4},       //9F
  {"AND B", 1, 4},       //A0
  {"AND C", 1, 4},       //A1
  {"AND D", 1, 4},       //A2
  {"AND E", 1, 4},       //A3
  {"AND H", 1, 4},       //A4
  {"AND L", 1, 4},       //A5
  {"AND (HL)", 1, 8},    //A6
  {"AND A", 1, 4},       //A7
  {"XOR B", 1, 4},       //A8
  {"XOR C", 1, 4},       //A9
  {"XOR D", 1, 4},       //AA
  {"XOR E", 1, 4},       //AB
  {"XOR H", 1, 4},       //AC
  {"XOR L", 1, 4},       //AD
  {"XOR (HL)", 1, 8},    //AE
  {"XOR A", 1, 4},       //AF
  {"OR B", 1, 4},        //B0
  {"OR C", 1, 4},        //B1
  {"OR D", 1, 4},        //B2
  {"OR E", 1, 4},        //B3
  {"OR H", 1, 4},        //B4
  {"OR L", 1, 4},        //B5
  {"OR (HL)", 1, 8},     //B6
  {"OR A", 1, 4},        //B7
  {"CP B", 1, 4},        //B8
  {"CP C", 1, 4},        //B9
  {"CP D", 1, 4},        //BA
  {"CP E", 1, 4},        //BB
  {"CP H", 1, 4},        //BC
  {"CP L", 1, 4},        //BD
  {"CP (HL)", 1, 8},     //BE
  {"CP A", 1, 4},        //BF
  {"RET NZ", 1, 8,20},   //C0
  {"POP BC", 1, 12},     //C1
  {"JP NZ, imm16",3,12,16},//C2
  {"JP imm16", 3, 16},   //C3
  {"CALL NZ, imm16",3,12,24},//C4
  {"PUSH BC", 1, 16},    //C5
  {"ADD A, imm8", 2, 8}, //C6
  {"RST_0", 1, 4},       //C7
  {"RET_Z", 1, 8, 20},   //C8
  {"RET", 1, 4},         //C9
  {"JP Z, imm16", 3, 12 ,16},//CA
  {"Illegal OP", 1, 4},  //CB
  {"CALL Z, imm16", 3, 12, 24}, //CC
  {"CALL imm16", 3, 24}, //CD
  {"ADC A, imm8", 2, 8}, //CE
  {"RST_1", 1, 16},      //CF
  {"RET NC", 1, 8, 20},  //D0
  {"POP DE", 1, 12},     //D1
  {"JP NC, imm16", 3, 12, 16},//D2
  {"Illegal OP", 1, 4},  //D3
  {"CALL NC, imm16", 3, 12, 24},//D4
  {"PUSH DE", 1, 16},    //D5
  {"SUB imm8", 2, 8},    //D6
  {"RST_2", 1, 16},      //D7
  {"RET_C", 1, 8, 20},   //D8
  {"RETI", 1, 4},        //D9
  {"JP C, imm16", 3, 12, 16},//DA
  {"Illegal OP", 1, 4},  //DB
  {"CALL C, imm16", 3, 12 ,24}, //DC
  {"Illegal OP", 1, 4},  //DD
  {"SBC A, imm8", 2, 8}, //DE
  {"RST_3", 1, 16},      //DF
  {"LD (a8), A", 2, 12}, //E0
  {"POP HL", 1, 12},     //E1
  {"LD (C), A", 1, 8},   //E2
  {"Illegal OP", 1, 4},  //E3
  {"Illegal OP", 1, 4},  //E4
  {"PUSH HL", 1, 16},    //E5
  {"AND imm8", 2, 8},    //E6
  {"RST_4", 1, 16},      //E7
  {"ADD SP, imm8", 2, 16},//E8 
  {"JP HL", 1, 4},       //E9
  {"LD (a16), A", 3, 16},//EA
  {"Illegal OP", 1, 4},  //EB
  {"Illegal OP", 1, 4},  //EB
  {"Illegal OP", 1, 4},  //EB
  {"XOR imm8", 2, 8},    //EE
  {"RST_5", 1, 16},      //FF
  {"LD A, (a8)", 2, 12}, //F0
  {"POP AF", 1, 12},     //F1
  {"LD A, (C)", 1, 8},   //F2
  {"DI", 1, 4},          //F3
  {"Illegal OP", 1, 4},  //F4
  {"PUSH AF", 1, 16},    //F5
  {"OR imm8", 2, 8},     //F6
  {"RST_6", 1, 16},      //F7
  {"LD HL, SP+imm8", 2, 12},//F8
  {"LD SP, HL", 1, 8},   //F9
  {"LD A, (imm16)", 3, 16},//FA
  {"EI", 1, 4},          //FB
  {"Illegal OP", 1, 4},  //FC
  {"Illegal OP", 1, 4},  //FD
  {"CP imm8", 2, 8},     //FE
  {"RST_7", 1, 16},      //FF
};
