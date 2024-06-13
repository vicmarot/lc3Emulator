#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define R_R0 0
#define R_R1 1
#define R_R2 2
#define R_R3 3
#define R_R4 4
#define R_R5 5
#define R_R6 6
#define R_R7 7
#define R_PC 8
#define R_COND 9
#define R_COUNT 10

#define FL_POS (1 << 0)
#define FL_ZRO (1 << 1)
#define FL_NEG (1 << 2)

#define PC_START 0x3000

extern uint16_t reg[R_COUNT];

void update_flags(uint16_t r);

#endif
