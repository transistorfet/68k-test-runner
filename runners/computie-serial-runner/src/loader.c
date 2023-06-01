 
#include <stdio.h>
#include "loader.h"

struct TestState current_initial;
struct TestState current_final;

extern void run_test();

void process_message(const char *buffer, uint16_t length) {
    
}

void run_loaded_test() {
    current_initial.pc = 0x180000;
    current_initial.a_reg[7] = 0x190000;
    current_initial.usp = 0x190000;
    current_initial.sr = 0x2700;

    printf("Running test\n");
    run_test();
    printf("Test complete\n");

    extern uint32_t jump_to_address;
    extern uint32_t jump_back_address;
    printf("%08x %08x", jump_to_address, jump_back_address);
}

