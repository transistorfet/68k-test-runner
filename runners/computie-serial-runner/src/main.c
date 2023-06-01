
#include <stdint.h>
#include <stdio.h>

#include "loader.h"
//#include "m68k-test-cases.h"

#define MESSAGE_SIZE    512

extern void init_tty();

void read_message() {
    uint8_t byte;
    uint16_t length = 0;
    char buffer[MESSAGE_SIZE];

    length = getchar();
    length <<= 8;
    length |= getchar();

    for (int i = 0; i < length; i++) {
        buffer[i] = getchar();
    }

    // TODO interpret message
}

int main() {
asm volatile("trapv");
    init_tty();

    char *name = "hey there";
    printf("This is a test: %s\n", name);

    run_loaded_test();

    while (1) {
        //read_message();
    }
}

