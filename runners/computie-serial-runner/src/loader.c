 
#include <stdio.h>
#include <string.h>
#include "loader.h"

#define MESSAGE_SIZE    512

struct TestState current_initial;
struct TestState current_final;

extern int putchar_b(int);
extern int getchar_b(void);
extern void run_test(void);

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

void load_current_initial_state(const char *buffer) {
    uint16_t i = 0;
    uint8_t mem_length = 0;

    printf("Loading initial state\n");
    memcpy(&current_initial, buffer, 15 * 4);
    i += 15 * 4;

    current_initial.sr = *((uint16_t *) &buffer[i]);
    i += 2;
    // TODO load the memory data

    mem_length = buffer[i++];
    current_initial.instruction_len = mem_length;
    memcpy(&current_initial.instructions, &buffer[i], mem_length);
}

void run_loaded_test(void) {
    /*
    // TODO these are now loaded from the test message
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
    current_initial.sr = 0x2700;
    */

    current_initial.a_reg[7] = 0x190000;
    current_initial.usp = 0x190000;
    current_initial.pc = 0x180000;
    current_initial.data_len = 0;
    /*
    memcpy((char *) current_initial.instructions, "\xe9\x05\x00\x00", 4);
    */

    printf("Running test\n");
    load_memory(&current_initial);
    run_test();
    printf("Test complete\n");

    /*
    printf("Initial State:\n");
    print_state(&current_initial);

    printf("\nFinal State:\n");
    print_state(&current_final);
    */
}

void write_diff_of_final_state(const char *buffer) {
    printf("Saving final state\n");

    // TODO do it
}

// NOTE: without this, the following code will generate misaligned word accesses
#pragma GCC push_options
#pragma GCC optimize ("O0")
int serialize_diff_long(char *buffer, char type, uint32_t value) {
    buffer[0] = type;
    buffer[1] = (value >> 24) & 0xff;
    buffer[2] = (value >> 16) & 0xff;
    buffer[3] = (value >> 8) & 0xff;
    buffer[4] = value & 0xff;
    return 5;
}

int serialize_diff_word(char *buffer, char type, uint16_t value) {

    buffer[0] = type;
    buffer[1] = value >> 8;
    buffer[2] = value & 0xff;
    return 3;
}
#pragma GCC pop_options

void send_message(const char *buffer, uint16_t length) {
    putchar_b(length >> 8);
    putchar_b(length & 0xff);

    for (int i = 0; i < length; i++) {
        putchar_b(buffer[i]);
    }
}

uint16_t receive_message(char *buffer) {
    uint16_t length = 0;

    length = getchar_b();
    length <<= 8;
    length |= getchar_b();

    for (int i = 0; i < length; i++) {
        buffer[i] = getchar_b();
    }

    return length;
}

void send_test_response(void) {
    uint16_t length = 0;
    char buffer[MESSAGE_SIZE];

    memcpy(buffer, "\x03\x00", 2);
    length += 2;

    for (int i = 0; i < 8; i++) {
        if (current_initial.d_reg[i] != current_final.d_reg[i]) {
            length += serialize_diff_long(&buffer[length], i, current_final.d_reg[i]);
        }
    }

    for (int i = 0; i < 8; i++) {
        if (current_initial.a_reg[i] != current_final.a_reg[i]) {
            length += serialize_diff_long(&buffer[length], 8 + i, current_final.d_reg[i]);
        }
    }

    if (current_initial.sr != current_final.sr) {
        length += serialize_diff_word(&buffer[length], 16, current_final.sr);
    }

    send_message(buffer, length);
}

void process_message(const char *buffer, uint16_t length) {
    switch (buffer[0]) {
        case 2:
            load_current_initial_state(&buffer[2]);
            run_loaded_test();
            send_test_response();
            break;
        default:
            printf("unknown message: %x\n", buffer[0]);
            break;
    }
}

void handle_message(void) {
    uint16_t length;
    char buffer[MESSAGE_SIZE];

    length = receive_message(buffer);
    process_message(buffer, length);
}


