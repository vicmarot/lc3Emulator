#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdint.h>

#define OP_BR 0
#define OP_ADD 1
#define OP_LD 2
#define OP_ST 3
#define OP_JSR 4
#define OP_AND 5
#define OP_LDR 6
#define OP_STR 7
#define OP_RTI 8
#define OP_NOT 9
#define OP_LDI 10
#define OP_STI 11
#define OP_JMP 12
#define OP_RES 13
#define OP_LEA 14
#define OP_TRAP 15

void addAndNotOperations(uint16_t instr, uint16_t op);
void ldStOperation(uint16_t instr, uint16_t op);
void ldrStrOperation(uint16_t instr, uint16_t op);
void ldiStiOperation(uint16_t instr, uint16_t op);
void leaOperation(uint16_t instr);
void brOperation(uint16_t instr);
void jmpOperation(uint16_t instr);
void jsrOperation(uint16_t instr);
void handle_trap(uint16_t instr, int* running);

#endif
