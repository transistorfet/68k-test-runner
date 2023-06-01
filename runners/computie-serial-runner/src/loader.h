 
#ifndef LOADER_H
#define LOADER_H

#include <stdint.h>

#define MAX_DATA    32

struct TestState {
    uint32_t d_reg[8];
    uint32_t a_reg[8];
    uint32_t usp;
    uint32_t pc;
    uint16_t sr;
    uint16_t data_len;
    uint16_t data[MAX_DATA];
};

struct TestCase {
    const char *name;
    const uint16_t *data;
    struct TestState initial_state;
    struct TestState final_state;
};

void process_message(const char *buffer, uint16_t length);
void run_loaded_test();

#endif

