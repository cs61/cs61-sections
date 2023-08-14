#include "flapmap.hh"

void add_sample(uintptr_t start, size_t duration, size_t flapcount) {
    // Placeholders to avoid compiler warnings. Replace them with your code.
    (void) start, (void) duration, (void) flapcount; 
}

bool has_sample(uintptr_t t) {
    // Placeholders to avoid compiler warnings. Replace them with your code.
    (void) t; 
	return false;
}

bool sample_overlaps(uintptr_t start, size_t duration) {
    // Placeholders to avoid compiler warnings. Replace them with your code.
    (void) start, (void) duration; 
	return false;
}

bool can_coalesce_up(flapmap_iter it) {
    // Placeholders to avoid compiler warnings. Replace them with your code.
    (void) it; 
	return false;
}

void coalesce_up(flapmap_iter it) {
    // Placeholders to avoid compiler warnings. Replace them with your code.
    (void) it; 
}

bool can_coalesce_down(flapmap_iter it) {
    // Placeholders to avoid compiler warnings. Replace them with your code.
    (void) it; 
	return false;
}

void print_flapmap() {
    for (auto it = flapmap.begin(); it != flapmap.end(); ++it) {
        fprintf(stderr, "[%zu, %zu): %zu\n", it->first, it->first + it->second.duration, it->second.flapcount);
    }
}


int main() {
	// Tests for add_sample

    // Should print nothing
    print_flapmap();
    fprintf(stderr, "\n");

    add_sample(1, 3, 1);
    add_sample(4, 3, 2);
    add_sample(8, 2, 1);
    // Should print three samples
    print_flapmap();

	// Add tests for other functions!

}