#include <cstdio>
#include <thread>

int main() {
    for (int i = 0; i != 3; ++i) {
        std::thread t(printf, "%d\n", i + 1);
        t.join();
    }
}
