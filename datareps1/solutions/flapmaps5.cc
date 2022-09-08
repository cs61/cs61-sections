#include "../flapmap.hh"

bool has_sample(uintptr_t t) {
    auto it = flapmap.upper_bound(t);
    if (it == flapmap.begin()) {
        return false;
    } else {
        --it;
        return it->first <= t && t < it->first + it->second.duration;
    }
}

void print_flapmap() {
    for (auto it = flapmap.begin(); it != flapmap.end(); ++it) {
        fprintf(stderr, "[%zu, %zu): %zu\n", it->first, it->first + it->second.duration, it->second.flapcount);
    }
}


bool can_coalesce_up(flapmap_iter it) {
    assert(it != flapmap.end());
    // Check if next sample exists
    auto next = it;
    ++next;
    if (next == flapmap.end()) {
        return false;
    }
    return it->first + it->second.duration == next->first;
}

void coalesce_up(flapmap_iter it) {
    assert(can_coalesce_up(it));
    auto next = it;
    ++next;
    it->second.duration += next->second.duration;
    it->second.flapcount += next->second.flapcount;
    flapmap.erase(next);
}

bool can_coalesce_down(flapmap_iter it) {
    assert(it != flapmap.end());
    // Check if previous sample exists
    if (it == flapmap.begin()) {
        return false;
    }
    auto prev = it;
    --prev;
    return prev->first + prev->second.duration == it->first;
}


void add_sample(uintptr_t start, size_t duration, size_t flapcount) {
    // Strategy: first insert, then coalesce
    flapmap.insert({start, {start, duration, flapcount}});
    auto it = flapmap.find(start);
    while (can_coalesce_down(it)) {
        --it;
    }
    while (can_coalesce_up(it)) {
        coalesce_up(it);
    }
}



int main() {
    add_sample(0, 1, 2);
    add_sample(2, 1, 2);
    add_sample(4, 1, 2);
    add_sample(5, 1, 2); // should coalesce with [4, 5)
    print_flapmap();
    fprintf(stderr, "-\n");
    add_sample(1, 1, 2); // should coalesce with [0, 1) and [2, 3)
    add_sample(3, 1, 2); // should coalesce with [0, 3) and [4, 6)
    add_sample(6, 1, 2); // should coalesce with [0, 6)
    print_flapmap();
}
