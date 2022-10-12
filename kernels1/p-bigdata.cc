#include "u-lib.hh"

alignas(4096) char big_data[8192];

void process_main() {
    strcpy(&big_data[4086], "CS 61 Is Awful\n");
    strcpy(&big_data[0], "mazing\n");

    //console_printf("@va %p: %s\n", &big_data[0], &big_data[0]);
    //console_printf("@va %p: %.10s\n", &big_data[4086], &big_data[4086]);
    //console_printf("@va %p: %s\n", &big_data[4096], &big_data[4096]);

    console_printf(0x3000, "%s", &big_data[4086]);
    while (true) {
        sys_yield();
    }
}
