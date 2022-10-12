#include "u-lib.hh"

void process_main() {
    char buf[128];
    sys_getsysname(buf);
    console_printf(0x0F00, "This is %s.\n", buf);

    unsigned n = 0;
    while (true) {
        ++n;
        if (n % 1024 == 0) {
            console_printf(0x0E00, "Hi, I'm Eve! #%u\n", n);
        }
        sys_yield();
    }
}
