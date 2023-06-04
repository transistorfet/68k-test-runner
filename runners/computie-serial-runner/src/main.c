
#include <stdint.h>
#include <stdio.h>

#include "loader.h"
//#include "m68k-test-cases.h"

extern void init_tty(void);

int main() {
    init_tty();

    printf("68k Test Runner started\n");

    while (1) {
        printf("Waiting for test...\n");
        handle_message();
    }
}

