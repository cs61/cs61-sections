#include <cstdio>
#include <map>

std::map<uintptr_t, const char*> m;

void print_lower_bound(uintptr_t key) {
    auto it = m.lower_bound(key);
    if (it == m.end()) {
        fprintf(stderr, "lower_bound for %zu is at end\n", key);
    } else {
        fprintf(stderr, "lower_bound for %zu is at key %zu\n", key, it->first);
    }
}

int main() {
    m.insert({1, ""});
    m.insert({3, ""});
    m.insert({11, ""});
    print_lower_bound(0);
    print_lower_bound(1);
    print_lower_bound(2);
    print_lower_bound(4);
    print_lower_bound(10);
    print_lower_bound(11);
    print_lower_bound(12);
}

// ==> lower_bound for 0 is at key 1
//     lower_bound for 1 is at key 1
//     lower_bound for 2 is at key 3
//     lower_bound for 4 is at key 11
//     lower_bound for 10 is at key 11
//     lower_bound for 11 is at key 11
//     lower_bound for 12 is at end
