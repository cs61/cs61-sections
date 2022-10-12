#include "u-lib.hh"

void process_main() {
    console_printf(0x0F00, "Hello!\n");
    while (true) {
        sys_yield();
    }
}
