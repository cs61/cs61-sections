#include <map>
#include <string>
#include <cstdio>
#include <cassert>

int main() {
    // Map strings to integers
    std::map<std::string, int> m;

    // Insert without overwriting (leaves map unchanged if key present)
    m.insert({"one", 1});

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
    assert(it0->first == "one");
    assert(it0->second == 1);
    printf("m.find(\"one\") -> %d\n", it0->second);

    auto it1 = m.find("two");
    assert(it1 == m.end());

    // Array syntax inserts or modifies
    m["one"] = 61;               // Insert into map (with overwrite semantics)
    assert(m["one"] == 61);
    // But beware; array syntax inserts a default if not found!
    int two_value = m["two"];
    assert(two_value == 0);
    assert(m.size() == 2);
    assert(m.find("two") != m.end());

    // Remove key
    m.erase("two");
    assert(m.size() == 1);

    // Iterate in sorted order
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});
    m.insert({"five", 5});
    for (auto it = m.begin(); it != m.end(); ++it) {
        // `it->first` is the key, `it->second` the value
        // (`it->first.c_str()` transforms a C++ string to printf form)
        printf("Found %s -> %d\n", it->first.c_str(), it->second);
    }

    printf("Done!\n");
}
