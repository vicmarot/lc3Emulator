#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_MAX (1 << 16)
extern uint16_t memory[MEMORY_MAX];

#define MR_KBSR 0xFE00
#define MR_KBDR 0xFE02

void mem_write(uint16_t address, uint16_t val);
uint16_t mem_read(uint16_t address);
int read_image(const char* image_path);

#endif
