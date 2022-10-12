#include "u-lib.hh"

void process_main() {
    char buf[200];
    size_t buflen = 0;
    size_t nreads = 0;

    while (true) {
        // Read a message
        while (memchr(buf, '\n', buflen) == NULL) {
            ++nreads;
            ssize_t r = sys_piperead(&buf[buflen], sizeof(buf) - buflen);
            if (r == 0) {
                panic("pipe closed for reading!\n");
            } else if (r > 0) {
                buflen += r;
            }
        }

        // Print the message that was read
        char* newline = (char*) memchr(buf, '\n', buflen);
        size_t messagelen = (newline + 1) - buf;
        console_printf(0x0E00, "%zu sys_piperead calls: read %.*s",
                       nreads, messagelen, buf);

        // Shift down rest of buffer
        memmove(buf, &buf[messagelen], buflen - messagelen);
        buflen -= messagelen;
    }
}
