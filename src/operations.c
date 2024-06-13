#include "operations.h"
#include "cpu.h"
#include "deviceMemory.h"
#include "utils.h"

void addAndNotOperations(uint16_t instr, uint16_t op) {
    uint16_t r0 = getValue(instr, 9, 3);
    uint16_t r1 = getValue(instr, 6, 3);
    uint16_t opTypeFlag = getValue(instr, 5, 1);
    uint16_t secondOperand = 0;

    if (op == OP_NOT) {
        reg[r0] = ~reg[r1];
    } else {
        if (opTypeFlag) {
            secondOperand = sign_extend(getValue(instr, 0, 5), 5);
        } else {
            secondOperand = reg[getValue(instr, 0, 3)];
        }

        if (op == OP_ADD) {
            reg[r0] = reg[r1] + secondOperand;
        } else {
            reg[r0] = reg[r1] & secondOperand;
        }
    }

    update_flags(r0);
}

void ldStOperation(uint16_t instr, uint16_t op) {
    uint16_t r0 = getValue(instr, 9, 3);
    uint16_t pcOffset = sign_extend(getValue(instr, 0, 9), 9);

    if (op == OP_LD) {
        reg[r0] = mem_read(reg[R_PC] + pcOffset);
        update_flags(r0);
    } else {
        mem_write(reg[R_PC] + pcOffset, reg[r0]);
    }
}

void ldrStrOperation(uint16_t instr, uint16_t op) {
    uint16_t r0 = getValue(instr, 9, 3);
    uint16_t baseR = getValue(instr, 6, 3);
    uint16_t offset = sign_extend(getValue(instr, 0, 6), 6);

    if (op == OP_LDR) {
        reg[r0] = mem_read(reg[baseR] + offset);
        update_flags(r0);
    } else {
        mem_write(reg[baseR] + offset, reg[r0]);
    }
}

void ldiStiOperation(uint16_t instr, uint16_t op) {
    uint16_t r0 = getValue(instr, 9, 3);
    uint16_t pcOffset = sign_extend(getValue(instr, 0, 9), 9);

    if (op == OP_LDI) {
        reg[r0] = mem_read(mem_read(reg[R_PC] + pcOffset));
        update_flags(r0);
    } else {
        mem_write(mem_read(reg[R_PC] + pcOffset), reg[r0]);
    }
}

void leaOperation(uint16_t instr) {
    uint16_t r0 = getValue(instr, 9, 3);
    uint16_t pcOffset = sign_extend(getValue(instr, 0, 9), 9);
    reg[r0] = reg[R_PC] + pcOffset;
    update_flags(r0);
}

void brOperation(uint16_t instr) {
    uint16_t pcOffset = sign_extend(getValue(instr, 0, 9), 9);
    uint16_t nzp = getValue(instr, 9, 3);

    if (nzp & reg[R_COND]) {
        reg[R_PC] += pcOffset;
    }
}

void jmpOperation(uint16_t instr) {
    uint16_t baseR = getValue(instr, 6, 3);
    reg[R_PC] = reg[baseR];
}

void jsrOperation(uint16_t instr) {
    uint16_t long_flag = getValue(instr, 11, 1);
    reg[R_R7] = reg[R_PC];

    if (long_flag) {
        uint16_t long_pc_offset = sign_extend(getValue(instr, 0, 11), 11);
        reg[R_PC] += long_pc_offset;  /* JSR */
    } else {
        uint16_t r1 = getValue(instr, 6, 3);
        reg[R_PC] = reg[r1]; /* JSRR */
    }
}

void handle_trap(uint16_t instr, int* running) {
    reg[R_R7] = reg[R_PC];
    switch (instr & 0xFF) {
        case 0x20: // GETC
            reg[R_R0] = (uint16_t)getchar();
            update_flags(R_R0);
            break;
        case 0x21: // OUT
            putc((char)reg[R_R0], stdout);
            fflush(stdout);
            break;
        case 0x22: // PUTS
            {
                uint16_t* c = memory + reg[R_R0];
                while (*c) {
                    putc((char)*c, stdout);
                    fflush(stdout);
                    ++c;
                }
            }
            break;
        case 0x23: // IN
            {
                printf("Enter a character: ");
                char c = getchar();
                putc(c, stdout);
                fflush(stdout);
                reg[R_R0] = (uint16_t)c;
                update_flags(R_R0);
            }
            break;
        case 0x24: // PUTSP
            {
                uint16_t* c = memory + reg[R_R0];
                while (*c) {
                    char char1 = (*c) & 0xFF;
                    putc(char1, stdout);
                    char char2 = (*c) >> 8;
                    if (char2) putc(char2, stdout);
                    ++c;
                }
                fflush(stdout);
            }
            break;
        case 0x25: // HALT
            puts("HALT");
            fflush(stdout);
            *running = 0;
            break;
    }
}