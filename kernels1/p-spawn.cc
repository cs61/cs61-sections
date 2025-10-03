#include "u-lib.hh"

void process_main() {
    pid_t eve_pid = sys_spawn("eve");

    unsigned n = 0;
    while (true) {
        if (n % 1024 == 0) {
            console_printf(CS_WHITE "Hi, I'm Sheng! I started eve in %d. #%u\n",
                           eve_pid, n);
        }
        ++n;
        sys_yield();
    }
}
