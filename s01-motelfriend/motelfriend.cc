#include "motelfriend.hh"
#include <map>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <climits>

bool check_in(unsigned long room) {
    return false;
}

unsigned long empty_room() {
    return 0;
}


// Extra functions for testing

bool check_map_size(size_t expected_size) {
    // Return true iff the size of your room map equals `expected_size`.
    // Your code here (for checking coalescing)
    (void) expected_size;
    return true;
}

bool check_rep() {
    return true;
}
