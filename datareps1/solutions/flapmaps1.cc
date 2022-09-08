#include "../flapmap.hh"

void add_sample(uintptr_t start, size_t duration, size_t flapcount) {
    flapmap.insert({start, {start, duration, flapcount}});
}

void add_sample_long(uintptr_t start, size_t duration, size_t flapcount) {
    sample s = { .start = start, .duration = duration, .flapcount = flapcount };
    flapmap.insert({start, s});
}


void print_flapmap() {
    for (auto it = flapmap.begin(); it != flapmap.end(); ++it) {
        fprintf(stderr, "[%zu, %zu): %zu\n", it->first, it->first + it->second.duration, it->second.flapcount);
    }
}


int main() {
    // Should print nothing
    print_flapmap();
    fprintf(stderr, "\n");

    add_sample(10, 10, 1);
    add_sample(21, 2, 2);
    add_sample(23, 4, 1);
    // Should print three samples
    print_flapmap();
}
