#include <vector>     // include declaration of `std::vector`
#include <cstdio>
#include <cassert>

int main() {
    // Create a vector containing specific elements
    std::vector<int> a = { 1, 2, 3, 4 };

    int e2 = a[2];    // get element
    (void) e2;
    assert(a[2] == 3);

    a[2] = 4;         // set element
    assert(a[2] == 4);

    (void) a.size();  // return number of elements
    assert(a.size() == 4);

    a.push_back(5);   // add element to the end
    assert(a.size() == 5);
    assert(a[4] == 5);

    (void) a.back();  // return last element (must not be empty)
    assert(a.back() == 5);

    a.pop_back();     // remove last element (but do not return it)
    assert(a.size() == 4);

    bool e = a.empty(); // return true iff `size() == 0`
    assert(!e);

    // Print vector contents
    printf("a: [");
    for (size_t i = 0; i != a.size(); ++i) {
        printf("%s%d", i ? ", " : "", a[i]);
    }
    printf("]\n");

    a.clear();        // erase all elements
    assert(a.empty());

    printf("Done!\n");
}
