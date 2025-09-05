#include <vector>
#include "print_bytes.hh"

int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    assert(v.size() == ?);
    assert(v[3] == ?);

    v.push_back(6);

    assert(v.size() == ?);
    assert(v.back() == ?);

    v.erase(v.begin(), v.begin() + 1);

    assert(v.size() == ?);
    assert(v.back() == ?);
    assert(v[0] == ?);

    v.insert(v.begin() + 1, 10);
    assert(v.size() == ?);
    assert(v[0] == ?);
    assert(v[1] == ?);
}
