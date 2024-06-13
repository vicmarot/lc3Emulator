#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>
#include <signal.h>

void read_image_file(FILE* file);
uint16_t swap16(uint16_t x);
void disable_input_buffering();
void restore_input_buffering();
uint16_t check_key();
void handle_interrupt(int signal);
uint16_t sign_extend(uint16_t x, uint8_t bit_count);
uint16_t getValue(uint16_t instr, uint8_t position, uint8_t length);

#endif
