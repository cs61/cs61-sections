#include <unordered_set>
#include <string>
#include <cstdio>
#include <cassert>

int main() {
    // Set of strings
    std::unordered_set<std::string> m;

    // Insert
    m.insert("one");

    // Number of keys in map
    assert(m.size() == 1);
    assert(!m.empty());
    printf("m.size = %zu\n", m.size());

    // Test if key is in map
    size_t exists = m.count("one");
    assert(exists == 1);

    exists = m.count("two");
    assert(exists == 0);

    // Find matching element; returns `m.end()` if not found
    auto it0 = m.find("one");
    assert(it0 != m.end());
    // Iterator points to a key-value pair: `first` is the key, `second` the value
    assert(*it0 == "one");
    printf("m.find(\"one\") -> %s\n", it0->c_str());

    auto it1 = m.find("two");
    assert(it1 == m.end());

    // Remove key
    m.insert("two");
    assert(m.size() == 2);
    m.erase("two");
    assert(m.size() == 1);

    // Iterate in sorted order
    m.insert("two");
    m.insert("three");
    m.insert("four");
    m.insert("five");
    for (auto it = m.begin(); it != m.end(); ++it) {
        printf("Found %s\n", it->c_str());
    }

    printf("Done!\n");
}
