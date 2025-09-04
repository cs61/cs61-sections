#include "motelfriend.hh"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cerrno>


int main(int argc, char* argv[]) {
    const char* filename;
    if (argc == 2) {
        filename = argv[1];
    } else if (argc == 1) {
        filename = "-";
    } else {
        fprintf(stderr, "Too many arguments\n");
        exit(1);
    }

    FILE* cmdf;
    if (strcmp(filename, "-") != 0) {
        cmdf = fopen(filename, "rb");
        if (!cmdf) {
            fprintf(stderr, "%s: %s\n", filename, strerror(errno));
            exit(1);
        }
    } else {
        cmdf = stdin;
        filename = "<stdin>";
    }

    char buf[BUFSIZ];
    unsigned long line = 0, ntests = 0;
    while (fgets(buf, BUFSIZ, cmdf)) {
        ++line;
        const char* s = buf;
        while (*s != 0 && isspace((unsigned char) *s)) {
            ++s;
        }
        if (*s == 0 || *s == '#' || *s == ';') {
            // ignore blank lines and comments
            continue;
        }

        unsigned long room;
        char placeholder[2];
        if (sscanf(s, "check_in %lu", &room)) {
            if (check_in(room)) {
                ++ntests;
                continue;
            }
            fprintf(stderr, "%s:%lu: assertion failure at `check_in %lu`\n",
                    filename, line, room);
            exit(1);
        } else if (sscanf(s, "check_in_fail %lu", &room)) {
            if (!check_in(room)) {
                ++ntests;
                continue;
            }
            fprintf(stderr, "%s:%lu: assertion failure at `check_in_fail %lu`\n",
                    filename, line, room);
            exit(1);
        } else if (sscanf(s, "empty_room %lu", &room)) {
            unsigned long result = empty_room();
            if (result == room) {
                ++ntests;
                continue;
            }
            fprintf(stderr, "%s:%lu: assertion failure at `empty_room %lu` (got %lu)\n",
                    filename, line, room, result);
            exit(1);
        } else if (sscanf(s, "check_rep%1[\n\t ]", placeholder)) {
            if (check_rep()) {
                ++ntests;
                continue;
            }
            fprintf(stderr, "%s:%lu: assertion failure at `check_rep`\n",
                    filename, line);
            exit(1);
        } else {
            fprintf(stderr, "%s:%lu: bogus assertion\n", filename, line);
        }
    }

    if (ntests > 0) {
        fprintf(stderr, "%s: %lu tests succeeded!\n", filename, ntests);
    }
    exit(ntests > 0 ? 0 : 1);
}
