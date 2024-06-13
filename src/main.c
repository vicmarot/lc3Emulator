#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "utils.h"
#include "deviceMemory.h"
#include "operations.h"
#include "cpu.h"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j) {
        if (!read_image(argv[j])) {
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }

    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    reg[R_COND] = FL_ZRO;
    reg[R_PC] = PC_START;

    int running = 1;
    while (running) {
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op) {
            case OP_ADD:
            case OP_AND:
            case OP_NOT:
                addAndNotOperations(instr, op);
                break;

            case OP_LD:
            case OP_ST:
                ldStOperation(instr, op);
                break;

            case OP_LDR:
            case OP_STR:
                ldrStrOperation(instr, op);
                break;

            case OP_LDI:
            case OP_STI:
                ldiStiOperation(instr, op);
                break;

            case OP_LEA:
                leaOperation(instr);
                break;

            case OP_BR:
                brOperation(instr);
                break;

            case OP_JMP:
                jmpOperation(instr);
                break;

            case OP_JSR:
                jsrOperation(instr);
                break;

            case OP_TRAP:
                handle_trap(instr, &running);
                break;

            case OP_RES:
            case OP_RTI:
            default:
                abort();
                break;
        }
    }

    restore_input_buffering();
    return 0;
}
