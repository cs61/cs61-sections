#include <list>
#include <cstdio>
#include <cassert>

int main() {
    // Create a list containing specific elements
    std::list<int> l = { 1, 2, 3, 4 };

    (void) l.size();  // return number of elements
    assert(l.size() == 4);

    l.push_back(5);   // add element to the end
    assert(l.size() == 5);

    (void) l.back();  // return last element (must not be empty)
    assert(l.back() == 5);

    (void) l.front(); // return first element
    assert(l.front() == 1);

    // Lists also allow efficient front insertion.
    l.push_front(0);
    assert(l.size() == 6);
    assert(l.front() == 0);

    l.pop_back();     // remove last element (but do not return it)
    assert(l.size() == 5);

    bool e = l.empty(); // return true iff `size() == 0`
    assert(!e);

    // Print list contents
    printf("l: [");
    for (auto it = l.begin(); it != l.end(); ++it) {
        printf("%s%d", it != l.begin() ? ", " : "", *it);
    }
    printf("]\n");

    l.clear();        // erase all elements
    assert(l.empty());

    printf("Done!\n");
}
