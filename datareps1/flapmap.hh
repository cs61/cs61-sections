#include <map>
#include <cstdint>
#include <cstdio>
#include <cassert>

struct sample {
    uintptr_t start;
    size_t duration;
    size_t flapcount;
};

std::map<uintptr_t, sample> flapmap;
using flapmap_iter = std::map<uintptr_t, sample>::iterator;

void add_sample(uintptr_t start, size_t duration, size_t flapcount) {
    sample s  = {start, duration, flapcount};
    flapmap[start] = s;
    flapmap_iter it = flapmap.find(start);
    while (can_coalesce_down(it)) {
        --it;
    }

    while (can_coalesce_up(it)) {
        coalesce_up();
    }

}

bool has_sample(uintptr_t t) {
    if (flapmap.empty()) {
        return false;
    }
    flapmap_iter it = flapmap.upper_bound(t); //nearest start greater than t
    if (it != flapmap.begin()) {
        --it;
    }
    return (it->second.start <= t) && (it->second.start + it->second.duration > t);
}

bool can_coalesce_up(flapmap_iter it) {
    assert(it != flapmap.end());
    flapmap_iter next = it;
    ++next;
    if (next == flapmap.end()) {
        return false;
    }
    return it->second.start + it->second.duration == next->second.start; 
}

void coalesce_up(flapmap_iter it) {
    if (can_coalesce_up(it)) {
        flapmap_iter next = it;
        ++next;
        it->second.duration += next->second.duration;
        it->second.flapcount += next->second.flapcount;
        flapmap.erase(next);
    }
}

bool can_coalesce_down(flapmap_iter it) {
    assert(it != flapmap.end());
    
    if (it == flapmap.begin()) {
        return false;
    }
    flapmap_iter prev = it;
    --prev;

    return it->second.start == prev->second.start + prev->second.duration;
}

void print_flapmap() {
    for (flapmap_iter it = flapmap.begin(); it != flapmap.end(); ++it) {
        fprintf(stdout, "key %ld, start %ld, duration %ld, flapcount %ld\n", it->first, it->second.start, it->second.duration, it->second.flapcount);
    }
}