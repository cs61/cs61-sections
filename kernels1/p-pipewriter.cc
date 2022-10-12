#include "u-lib.hh"

const char* messages[] = {
    "Hello, friend!\n",
    "I am a plumber.\n",
    "I'm talking through a pipe.\n"
};

void process_main() {
    size_t nwrites = 0;

    while (true) {
        // First, write a message.
        const char* message = messages[rand(0, arraysize(messages) - 1)];
        size_t pos = 0;
        size_t len = strlen(message);
        while (pos < len) {
            ++nwrites;
            ssize_t w = sys_pipewrite(&message[pos], len - pos);
            if (w == 0) {
                panic("pipe closed for writing!\n");
            } else if (w > 0) {
                pos += w;
            }
        }

        // Print that message was written.
        console_printf(0x0F00, "%zu sys_pipewrite calls: wrote %s",
                       nwrites, message);

        // Wait 1-3 seconds.
        unsigned long wait_until = ticks + rand(HZ, 3 * HZ - 1);
        while (ticks < wait_until) {
            sys_yield();
        }
    }
}
