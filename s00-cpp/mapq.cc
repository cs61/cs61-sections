#include <map>
#include "hexdump.hh"

int main() {
    std::map<int, int> m;

    m.insert({1, 2});
    assert(m[1] == ?);
    assert(m.count(1) == ?);
    assert(m.count(2) == ?);
    assert(m.size() == ?);

    int x = m[2];
    assert(x == ?);
    assert(m.size() == ?);

    m.insert({1, 3});
    assert(m[1] == ?);

    m.erase(1);
    assert(m.size() == ?);

    m.insert({1, 3});
    assert(m[1] == ?);
}
