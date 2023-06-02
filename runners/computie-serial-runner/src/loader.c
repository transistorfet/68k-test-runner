 
#include <stdio.h>
#include <string.h>
#include "loader.h"

struct TestState current_initial;
struct TestState current_final;

extern void run_test();

void process_message(const char *buffer, uint16_t length) {
    
}

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
    // d0: f38bcde6    a0: c6648978
    // d1: 39be6b6e    a1: 56681814
    // d2: a1f40cb9    a2: df03c6cd
    // d3: c7b0779f    a3: 7d6926d5
    // d4: 1ed71c75    a4: 869803ac
    // d5: b07e6d58    a5: 188aee2e
    // d6: f6d3a760    a6: dbba2485
    // d7: 5db61ce7   usp: 5c14a0c4
    // pc: 00000c00   ssp: 00000800
    // sr: 2707

    current_initial.pc = 0x180000;
    current_initial.d_reg[0] = 0xf38bcde6;
    current_initial.d_reg[1] = 0x39be6b6e;
    current_initial.d_reg[2] = 0xa1f40cb9;
    current_initial.d_reg[3] = 0xc7b0779f;
    current_initial.d_reg[4] = 0x1ed71c75;
    current_initial.d_reg[5] = 0xb07e6d58;
    current_initial.d_reg[6] = 0xf6d3a760;
    current_initial.d_reg[7] = 0x5db61ce7;

    current_initial.a_reg[0] = 0xc6648978;
    current_initial.a_reg[1] = 0x56681814;
    current_initial.a_reg[2] = 0xdf03c6cd;
    current_initial.a_reg[3] = 0x7d6926d5;
    current_initial.a_reg[4] = 0x869803ac;
    current_initial.a_reg[5] = 0xdbba2485;
    current_initial.a_reg[6] = 0xf38bcde6;

    current_initial.a_reg[7] = 0x190000;
    current_initial.usp = 0x190000;
    current_initial.sr = 0x2707;
    current_initial.data_len = 0;
    strcpy((char *) current_initial.instructions, "\x1E\x20\x00");

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


