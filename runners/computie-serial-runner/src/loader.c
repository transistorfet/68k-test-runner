 
#include <stdio.h>
#include <string.h>
#include "loader.h"

struct TestState current_initial;
struct TestState current_final;

extern void run_test();

void print_state(struct TestState *state) {
    for (int i = 0; i < 8; i++) {
        printf("D%d: %08x    A%d: %08x\n", i, state->d_reg[i], i, state->a_reg[i]);
    }
    printf("SR: %04x\n", state->sr);
    printf("PC: %04x\n", state->pc);
}

int new_memory_data(struct TestState *state, uint32_t address, uint32_t data) {
    if (state->data_len == MAX_DATA)
        return -1;
    state->data[state->data_len].address = address;
    state->data[state->data_len].data = data;
    state->data_len++;
    return 0;
}

void load_memory(struct TestState *state) {
    for (int i = 0; i < state->data_len; i++) {
        printf("loading %08x <- %08x\n", state->data[i].address, state->data[i].data);
        *((uint32_t *) state->data[i].address) = state->data[i].data;
    }
}

void run_loaded_test() {
    current_initial.pc = 0x180000;
    current_initial.d_reg[0] = 0xf38bcde6;
    current_initial.d_reg[1] = 0x39be6b6e;
    current_initial.d_reg[2] = 0xa1f40cb9;
    current_initial.d_reg[3] = 0xc7b0779f;
    current_initial.d_reg[4] = 0x1ed71c75;
    current_initial.d_reg[5] = 0x7db1033d;
    current_initial.d_reg[6] = 0x2b01d2e7;
    current_initial.d_reg[7] = 0x58862978;

    current_initial.a_reg[0] = 0xc6648978;
    current_initial.a_reg[1] = 0x56681814;
    current_initial.a_reg[2] = 0xdf03c6cd;
    current_initial.a_reg[3] = 0x7d6926d5;
    current_initial.a_reg[4] = 0x869803ac;
    current_initial.a_reg[5] = 0xdbba2485;
    current_initial.a_reg[6] = 0xf38bcde6;

    current_initial.a_reg[7] = 0x190000;
    current_initial.usp = 0x190000;
    current_initial.sr = 0x2700;
    current_initial.data_len = 0;
    memcpy((char *) current_initial.instructions, "\xe9\x05\x00\x00", 4);

    printf("Running test\n");
    load_memory(&current_initial);
    run_test();
    printf("Test complete\n");

    extern uint32_t jump_to_address;
    extern uint32_t jump_back_address;
    printf("%08x %08x\n", jump_to_address, jump_back_address);

    printf("Initial State:\n");
    print_state(&current_initial);

    printf("\nFinal State:\n");
    print_state(&current_final);
}

void process_message(const char *buffer, uint16_t length) {
    switch (buffer[0]) {
        case 2:
            
            break;
        default:
            printf("unknown message: %x\n", buffer[0]);
            berak;
    }
}


