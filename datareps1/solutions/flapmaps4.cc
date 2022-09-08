#include "../flapmap.hh"

void add_sample(uintptr_t start, size_t duration, size_t flapcount) {
    flapmap.insert({start, {start, duration, flapcount}});
}

void print_flapmap() {
    for (auto it = flapmap.begin(); it != flapmap.end(); ++it) {
        fprintf(stderr, "[%zu, %zu): %zu\n", it->first, it->first + it->second.duration, it->second.flapcount);
    }
}


bool has_sample(uintptr_t t) {
    auto it = flapmap.upper_bound(t);
    if (it == flapmap.begin()) {
        return false;
    } else {
        --it;
        return it->first <= t && t < it->first + it->second.duration;
    }
}



int main() {
    // empty flapmap tests
    assert(!has_sample(0));
    assert(!has_sample(-19348));
    assert(!has_sample(192132471));
    // single-sample tests
    add_sample(10, 10, 1);
    assert(!has_sample(0));
    assert(has_sample(10));
    assert(has_sample(15));
    assert(!has_sample(20));
    assert(!has_sample(25));
    // multi-sample tests
    add_sample(20, 10, 1);
    add_sample(40, 10, 1);
    assert(!has_sample(0));
    assert(has_sample(10));
    assert(has_sample(15));
    assert(has_sample(20));
    assert(has_sample(25));
    assert(!has_sample(30));
    assert(!has_sample(35));
    assert(has_sample(40));
    assert(has_sample(45));
    assert(!has_sample(50));
}
